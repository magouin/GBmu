#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>


uint8_t		Emulateur::bit_to_gray(uint8_t b, enum e_tile_type t)
{
	uint16_t pal;

	if (t == BG)
		pal = 0xff47;
	else
		pal = 0xff48; // or 0xff49
	b = (_RAM[pal] >> (b * 2)) & 3;
	if (b == 0)
		return (COLOR_DMG_00);
	if (b == 2)
		return (COLOR_DMG_01);
	if (b == 1)
		return (COLOR_DMG_10);
	return (COLOR_DMG_11);
}

uint32_t	graytopixel(uint8_t g)
{
	return ((((((0xff << 8) | g) << 8) | g) << 8) | g);
}

void	Emulateur::print_tile(uint8_t *tile, int x, int y, bool h_flip, bool v_flip, uint8_t size, enum e_tile_type t)
{
	int h, w;
	uint8_t p;

	h = 0;
	while (h < size)
	{
		w = 0;
		while (w < 8)
		{
			p = bit_to_gray((((tile[h * 2] >> w) << 1) & 2) | ((tile[h * 2 + 1] >> w) & 1), t);
			if (t != OBJ || p != 0xff)
				set_pixel(graytopixel(p), x + (v_flip ? w : (7 - w)), y + (h_flip ? ((size - 1) - h) : h));
			w++;
		}
		h++;
	}
}

void	Emulateur::print_tile_line(uint8_t *tile, int x, int y, int h, bool flip, enum e_tile_type t)
{
	int		w;
	uint8_t	p;

	w = 0;
	while (w < 8)
	{
		p = bit_to_gray((((tile[h * 2] >> w) << 1) & 2) | ((tile[h * 2 + 1] >> w) & 1), t);
		if (t != OBJ || p != 0xff)
			set_pixel(graytopixel(p), x + (flip ? w : (7 - w)), y + h);
		w++;
	}
}

void	Emulateur::dump_data_tiles()
{
	int x;
	uint32_t a;

	x = 0;
	while (x < 0x800)
	{
		a = 0x8000 + x;
		printf("%x: %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", a, _RAM[a + 0], _RAM[a + 1], _RAM[a + 2], _RAM[a + 3], _RAM[a + 4], _RAM[a + 5], _RAM[a + 6], _RAM[a + 7], _RAM[a + 8], _RAM[a + 9], _RAM[a + 10], _RAM[a + 11], _RAM[a + 12], _RAM[a + 13], _RAM[a + 14], _RAM[a + 15]);
		x += 16;
	}
}

void	Emulateur::print_all_tiles()
{
	int x;

	x = 0;
	while (x < 256)
	{
		print_tile(_RAM + 0x8000 + (x * 16), (x % 20) * 8, (x / 20) * 8, false, false, 8, BG);
		x++;
	}
}

void	Emulateur::print_bg()
{
	uint8_t	*b_code;
	uint8_t	*b_data;
	uint8_t	*data;
	uint8_t	code;
	int		x, y;
	uint8_t	scx, scy;

	b_code = _RAM + ((_RAM[REG_LCDC] & (1 << 3)) ? 0x9c00 : 0x9800);
	b_data = _RAM + (_RAM[REG_LCDC] & (1 << 4) ? 0x8000 : 0x8800);
	y = 0;
	scx = _RAM[0xff43] >> 3;
	scy = _RAM[0xff42] >> 3;
	while (y < 18)
	{
		x = 0;
		while (x < 20)
		{
			code = b_code[(y + scy) * 32 + (scx + x) % 32];
			data = b_data + (code * 16);
			if (data >= _RAM + 0x9800)
				data -= 0x1000;
			print_tile(data, x * 8, y * 8, false, false, 8, BG);
			x++;
		}
		y++;
	}
}

void	Emulateur::print_obj_line(struct s_oam_obj	*obj, uint64_t ly)
{
	uint8_t	*tile;
	uint8_t	h;

	obj->chrcode &= (_RAM[REG_LCDC] & 4 ? ~1 : ~0);
	tile = _RAM + 0x8000 + (obj->chrcode * 0x10);
	h = (ly - (obj->y - 16));
	if (obj->h_flip)
		h = ((_RAM[REG_LCDC] & 4 ? 15 : 7) - h);
	print_tile_line(tile, obj->x - 8, obj->y - 16, h, obj->v_flip, OBJ);
}

void	Emulateur::print_line(uint64_t ly, uint64_t start, struct s_oam_obj **objs)
{
	struct s_oam_obj	*obj_to_print[10];
	uint8_t				height;
	int					x;
	int					nb_print;
	const uint64_t		scanline_time = 456;

	nb_print = 0;
	x = 0;
	height = (_RAM[REG_LCDC] & 4) ? 16 : 8;
	while (x < 40)
	{
		if (ly >= objs[x]->y - 16 &&
			ly < objs[x]->y - 16 + height)
		{
			obj_to_print[nb_print] = objs[x];
			nb_print++;
		}
		x++;
	}
	while (start + ly * scanline_time + 80 > _timer_counter * 256 + _timer) ;
	_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 3;
	x = nb_print - 1;
	while (x >= 0)
	{
		print_obj_line(obj_to_print[x], ly);
		x--;
	}

}

void	Emulateur::sort_objs(struct s_oam_obj **objs)
{
	int					x;
	int					y;
	struct s_oam_obj	*obj;
	bool				used[40] = {false};
	bool				init;

	y = 0;
	obj = (struct s_oam_obj *)(_RAM + 0xfe00);
	while (y < 40)
	{
		x = 0;
		init = false;
		while (x < 40)
		{
			if (!used[x] && !init)
			{
				init = true;
				objs[y] = &obj[x];
				used[x] = true;
			}
			else if (!used[x] && objs[y]->x > obj[x].x)
			{
				used[x] = true;
				used[(uint32_t)((uint8_t *)objs[y] - (uint8_t *)_RAM - 0xfe00) / 4] = false;
				objs[y] = &obj[x];
			}
			x++;
		}
		y++;
	}
}

void	Emulateur::print_obj(struct s_oam_obj *obj)
{
	uint8_t	*tile;

	obj->chrcode &= (_RAM[REG_LCDC] & 4 ? ~1 : ~0);
	tile = _RAM + 0x8000 + (obj->chrcode * 0x10);
	print_tile(tile, obj->x - 8, obj->y - 16, obj->h_flip, obj->v_flip, (_RAM[REG_LCDC] & 4 ? 16 : 8), OBJ);
}

void	Emulateur::print_objs(struct s_oam_obj	**objs)
{
	int x;

	x = 0;
	while (x < 40)
	{
		print_obj(objs[x]);
		x++;
	}
}

void	Emulateur::update_lcd()
{
	uint32_t	frame_cycle;
	uint64_t		line_cycle;
	uint8_t		ly;
	struct s_oam_obj	*objs[40];


	if (!(_RAM[REG_LCDC] & 0x80))
	{
		_lcd_missed_cycles += 4;
		return ;
	}

	frame_cycle = (_cycle - _lcd_missed_cycles) % 70224;
	line_cycle = frame_cycle % 456;
	ly = frame_cycle / 456;

	// printf("_cycle : %d, frame_cycle: %d, line_cycle: %d, ly: %d\n", _cycle, frame_cycle, line_cycle, ly);

	if (frame_cycle == 0)
	{
		// printf("New frame !\n");
		render();
		sort_objs(objs);
		if (_RAM[REG_LCDC] & 1)
			print_bg();
		if (_RAM[REG_LCDC] & 2)
			print_objs(objs);
	}
	if (line_cycle == 452)
	{
		mem_write(&_RAM[REG_LY], (ly + 1) % 154, 1);
	}
	if (ly < 144)
	{
		if (line_cycle == 0)
		{
			// printf("Mode 2\n");
			_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 2;
			if (_RAM[REG_STAT] & (1 << 5))
					_RAM[REG_IF] |= (1 << 1);
		}
		else if (line_cycle == 172)
		{
			// printf("Mode 3\n");
			_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 3;
		}
		else if (line_cycle == 252)
		{
			// printf("Mode 0\n");
			_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 0;
			if (_RAM[REG_STAT] & (1 << 3))
				_RAM[REG_IF] |= (1 << 1);
		}
		// else if (line_cycle > 252)
		// {
			// printf(	"line_cycle: %d\n", line_cycle);
		// }
	}
	if (ly  == 143 && line_cycle == 452)
	{
		// printf("Mode 1\n");
		_RAM[REG_STAT] = (_RAM[REG_STAT] & ~(uint8_t)3) | 1;
		if (_RAM[REG_STAT] & (1 << 4))
			_RAM[REG_IF] |= (1 << 1);
		_RAM[REG_IF] |= 1;
	}
}
