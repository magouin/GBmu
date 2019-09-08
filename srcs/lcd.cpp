#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>


uint32_t		Emulateur::bit_to_gray(uint8_t b, uint16_t pal_addr)
{
	if (b == 0 && pal_addr != 0xff47)
		return (2);
	b = (_RAM[pal_addr] >> ((b & 3) * 2)) & 3;
	if (b == 0)
		return (COLOR_DMG_00);
	if (b == 1)
		return (COLOR_DMG_01);
	if (b == 2)
		return (COLOR_DMG_10);
	return (COLOR_DMG_11);
}
void	Emulateur::print_tile_line(uint8_t *tile, int x, int y, bool h_flip, bool v_flip, uint8_t size, uint16_t pal_addr, int h)
{
	int w;
	uint32_t p;
	uint16_t cx, cy;

	w = 0;
	while (w < 8)
	{
		p = bit_to_gray((((tile[h * 2 + 1] >> (7 - w)) << 1) & 2) | ((tile[h * 2] >> (7 - w)) & 1), pal_addr);
		cx = x + (v_flip ? (7 - w) : w);
		cy = y + (h_flip ? ((size - 1) - h) : h);
		if (p != 2)
		 // && (!(_RAM[REG_LCDC] & (1 << 5)) || (cx + 7 >= _RAM[REG_WX] && cy >= _RAM[REG_WY])))
			set_pixel(p, cx, cy);
		w++;
	}
}

void	Emulateur::print_bg_line(int y)
{
	uint8_t	*b_code;
	uint8_t	*b_data;
	uint8_t	*data;
	uint8_t	code;
	uint32_t	cy;
	uint8_t		x;
	uint8_t	scx;
	uint8_t	scy;
	uint32_t	id_line;
	uint32_t	offset_line;

	b_code = _RAM + ((_RAM[REG_LCDC] & (1 << 3)) ? 0x9c00 : 0x9800);
	b_data = _RAM + (_RAM[REG_LCDC] & (1 << 4) ? 0x8000 : 0x9000);
	scx = _RAM[0xff43];
	scy = _RAM[0xff42];
	cy = (scy + y) % 256;


	// pour 15, 15
	// 
	x = 0;
	// printf("last param = %x et ly = %d et scy = %d et cy = %d\n", y - (cy * 8 - (scy & 7)), y, scy, cy);
	// if (y - (cy / 32 * 8 - (_RAM[0xff42] & 7)) >= 8)
		// exit(0);
	while (x < 21)
	{
		id_line = cy / 8;
		offset_line = cy % 8; 
		// printf("id_line : %d and offset_line = %d\n", id_line, offset_line);

		code = b_code[(id_line * 32) + (((scx >> 3) + x) % 32)];
		data = b_data + (code * 16);
		if (data >= _RAM + 0x9800)
			data -= 0x1000;
		print_tile_line(data, x * 8 - (_RAM[0xff43] & 7), y - offset_line, false, false, 8, 0xff47, offset_line);
		x++;
	}
}


// void	Emulateur::print_tile(uint8_t *tile, int x, int y, bool h_flip, bool v_flip, uint8_t size, uint16_t pal_addr)
// {
// 	int h, w;
// 	uint32_t p;
// 	uint16_t cx, cy;

// 	h = 0;
// 	while (h < size)
// 	{
// 		w = 0;
// 		while (w < 8)
// 		{
// 			p = bit_to_gray((((tile[h * 2 + 1] >> (7 - w)) << 1) & 2) | ((tile[h * 2] >> (7 - w)) & 1), pal_addr);
// 			cx = x + (v_flip ? (7 - w) : w);
// 			cy = y + (h_flip ? ((size - 1) - h) : h);
// 			if (p != 2 && (!(_RAM[REG_LCDC] & (1 << 5)) || (cx + 7 >= _RAM[REG_WX] && cy >= _RAM[REG_WY])))
// 				set_pixel(p, cx, cy);
// 			w++;
// 		}
// 		h++;
// 	}
// }

// void	Emulateur::print_bg()
// {
// 	uint8_t	*b_code;
// 	uint8_t	*b_data;
// 	uint8_t	*data;
// 	uint8_t	code;
// 	int		x, y;
// 	uint8_t	scx = 0, scy = 0;

// 	b_code = _RAM + ((_RAM[REG_LCDC] & (1 << 3)) ? 0x9c00 : 0x9800);
// 	b_data = _RAM + (_RAM[REG_LCDC] & (1 << 4) ? 0x8000 : 0x9000);
// 	y = 0;
// 	scx = _RAM[0xff43] >> 3;
// 	scy = _RAM[0xff42] >> 3;
// 	while (y < 19)
// 	{
// 		x = 0;
// 		while (x < 21)
// 		{
// 			if ((y + scy) * 32 + (scx + x) % 32 >= 0xa000)
// 			{
// 				x++;
// 				continue ;
// 			}
// 			code = b_code[(y + scy) * 32 + (scx + x) % 32];
// 			data = b_data + (code * 16);
// 			if (data >= _RAM + 0x9800)
// 				data -= 0x1000;
// 			print_tile(data, (x - 1) * 8 + (7 - (_RAM[0xff43] % 8)) + 1, (y - 1) * 8 + (7 - (_RAM[0xff42] % 8)) + 1, false, false, 8, 0xff47);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	Emulateur::sort_objs(struct s_oam_obj **out)
{
	int					i_in;
	int					i_out;
	struct s_oam_obj	*in;
	bool				used[40] = {false};
	bool				initialized;

	i_out = 0;
	in = (struct s_oam_obj *)(_RAM + 0xfe00);
	while (i_out < 40)
	{
		i_in = 0;
		initialized = false;
		while (i_in < 40)
		{
			if (!used[i_in] && !initialized)
			{
				initialized = true;
				out[i_out] = &in[i_in];
				used[i_in] = true;
			}
			else if (!used[i_in] && out[i_out]->x > in[i_in].x)
			{
				used[i_in] = true;
				used[((uint8_t *)out[i_out] - (uint8_t *)_RAM - 0xfe00) / 4] = false;
				out[i_out] = &in[i_in];
			}
			i_in++;
		}
		i_out++;
	}
}

void	Emulateur::print_obj_line(struct s_oam_obj *obj, int off)
{
	uint8_t	*tile;

	obj->chrcode &= (_RAM[REG_LCDC] & 4 ? ~1 : ~0);
	tile = _RAM + 0x8000 + (obj->chrcode * 0x10);
	print_tile_line(tile, obj->x - 8, obj->y - 16, obj->h_flip, obj->v_flip, (_RAM[REG_LCDC] & 4 ? 16 : 8), 0xff48 + obj->mono_pal, off);
}

void	Emulateur::print_objs_line(struct s_oam_obj **objs, int y)
{
	int x;

	x = 39;
	while (x >= 0)
	{
		if (objs[x]->y - 16 <= y && (objs[x]->y - 16 + ((_RAM[REG_LCDC] & (1 << 2)) ? 16 : 8) > y))
			print_obj_line(objs[x], y + 16 - objs[x]->y);
		x--;
	}
}

void	Emulateur::update_lcd()
{
	uint64_t				line_cycle;
	uint8_t					ly;
	static struct s_oam_obj	*objs[40];
	static bool				init = false;

	if (!(_RAM[REG_LCDC] & 0x80))
	{
		_lcd_cycle = 0;
		return ;
	}
	line_cycle = _lcd_cycle % 456;
	ly = _lcd_cycle / 456;
	if (line_cycle == 0)
		mem_write(&_RAM[REG_LY], ly % 154, 1);
	if (!init)
	{
		init = true;
		sort_objs(objs);
	}
	if (ly < 144)
	{
		if (line_cycle == 0)
		{
			_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 2;
			if (_RAM[REG_STAT] & (1 << 5))
					_RAM[REG_IF] |= (1 << 1);
		}
		else if (line_cycle == 172)
		{
			_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 3;
		}
		else if (line_cycle == 252)
		{
			print_bg_line(ly);
			if (_RAM[REG_LCDC] & 2)
				print_objs_line(objs, ly);
			_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 0;
			if (_RAM[REG_STAT] & (1 << 3))
				_RAM[REG_IF] |= (1 << 1);
		}
	}
	if (ly == 144 && line_cycle == 0)
	{
		render();
		sort_objs(objs);
		_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 1;
		if (_RAM[REG_STAT] & (1 << 4))
			_RAM[REG_IF] |= (1 << 1);
		_RAM[REG_IF] |= 1;
	}
	_lcd_cycle = (_lcd_cycle + 4) % 70224;
}
