#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>


uint32_t		Emulateur::bit_to_gray(uint8_t b, uint16_t pal_addr)
{
	if (b == 0 && pal_addr != 0xff47)
		return (0);
	b = (RAM[pal_addr] >> ((b & 3) * 2)) & 3;
	if (b == 0)
		return (COLOR_DMG_00);
	if (b == 1)
		return (COLOR_DMG_01);
	if (b == 2)
		return (COLOR_DMG_10);
	return (COLOR_DMG_11);
}

uint8_t		Emulateur::gray_to_bit(uint32_t grey, uint16_t pal_addr)
{
	int			i;
	int			b;
	uint32_t	color;

	if (pal_addr != 0xff47)
		return (-1);
	i = 0;
	while (i < 4)
	{
		b = (RAM[pal_addr] >> ((i & 3) * 2)) & 3;
		if (b == 0) color = COLOR_DMG_00;
		else if (b == 1) color = COLOR_DMG_01;
		else if (b == 2) color = COLOR_DMG_10;
		else color = COLOR_DMG_11;
		if (grey == color)
			return (i);
		i++;
	}
	return (-1);
}

void	Emulateur::print_bg_tile_line(uint8_t *tile, int x, int y, int h)
{
	int w;
	uint32_t p;
	uint16_t cx, cy;

	w = 0;
	while (w < 8)
	{
		p = bit_to_gray((((tile[h * 2 + 1] >> (7 - w)) << 1) & 2) | ((tile[h * 2] >> (7 - w)) & 1), 0xff47);
		cx = x + w;
		cy = y + h;
		set_pixel(p, cx, cy);
		w++;
	}
}

void	Emulateur::print_obj_tile_line(uint8_t *tile, struct s_oam_obj *obj, uint8_t size, int off)
{
	int w;
	int h;
	uint32_t p;
	uint16_t cx, cy;
	uint16_t	pal_addr;

	pal_addr = 0xff48 + obj->mono_pal;
	w = 0;
	h = obj->v_flip ? (size - 1 - off) : off;
	while (w < 8)
	{
		p = bit_to_gray((((tile[h * 2 + 1] >> (7 - w)) << 1) & 2) | ((tile[h * 2] >> (7 - w)) & 1), pal_addr);
		cx = obj->x - 8 + (obj->h_flip ? (7 - w) : w);
		cy = obj->y - 16 + off;
		if (p != 0 && (obj->prio == 0 || search_bg_pix(cx, cy) == 0))
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
	uint32_t	id_line;
	uint32_t	offset_line;

	b_code = RAM + (gb_regs.lcdc.bg_code_addr ? 0x9c00 : 0x9800);
	b_data = RAM + (gb_regs.lcdc.bg_data_addr ? 0x8000 : 0x9000);
	cy = (RAM[REG_SCY] + y) % 256;
	x = 0;
	while (x < 21)
	{
		id_line = cy / 8;
		offset_line = cy % 8;
		code = b_code[(id_line * 32) + (((RAM[REG_SCX] >> 3) + x) % 32)];
		data = b_data + (code * 16);
		if (data >= RAM + 0x9800)
			data -= 0x1000;
		print_bg_tile_line(data, x * 8 - (RAM[REG_SCX] & 7), y - offset_line, offset_line);
		x++;
	}
}

void	Emulateur::print_window_line(int y)
{
	uint8_t	*b_code;
	uint8_t	*b_data;
	uint8_t	*data;
	uint8_t	code;
	uint8_t		x;

	b_code = RAM + (gb_regs.lcdc.window_code_addr ? 0x9c00 : 0x9800);
	b_data = RAM + (gb_regs.lcdc.bg_data_addr ? 0x8000 : 0x9000);
	x = 0;
	while (x < 21)
	{
		code = b_code[(((y - RAM[REG_WY]) / 8) * 32) + x];
		data = b_data + (code * 16);
		if (data >= RAM + 0x9800)
			data -= 0x1000;
		print_bg_tile_line(data, x * 8 + RAM[REG_WX] - 7, RAM[REG_WY] + ((y - RAM[REG_WY]) & ~7), (y - RAM[REG_WY]) & 7);
		x++;
	}
}

uint8_t	Emulateur::search_bg_pix(int x, int y)
{
	uint32_t	color;

	if (x < 0 || x >= GB_WINDOW_SIZE_X || y < 0 || y >= GB_WINDOW_SIZE_Y)
		return (0);
	color = _pixels_map[x + y * GB_WINDOW_SIZE_X];
	return (gray_to_bit(color, 0xff47));
}


void	Emulateur::sort_objs(struct s_oam_obj **out)
{
	int					i_in;
	int					i_out;
	int					i_tmp;
	struct s_oam_obj	*in;
	bool				used[40] = {false};
	bool				initialized;

	i_out = 0;
	in = (struct s_oam_obj *)(RAM + 0xfe00);
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
				i_tmp = i_in;
			}
			else if (!used[i_in] && out[i_out]->x > in[i_in].x)
			{
				used[i_in] = true;
				used[i_tmp] = false;
				i_tmp = i_in;
				out[i_out] = &in[i_in];
			}
			i_in++;
		}
		i_out++;
	}
}

void	Emulateur::print_obj_line(struct s_oam_obj *obj, int off, int size)
{
	uint8_t	*tile;

	obj->chrcode &= (gb_regs.lcdc.obj_size ? ~1 : ~0);
	tile = RAM + 0x8000 + (obj->chrcode * 0x10);
	print_obj_tile_line(tile, obj, size, off);
}

void	Emulateur::print_objs_line(int y)
{
	int x;
	int max;
	int nb;
	struct s_oam_obj *obj;

	x = 39;
	nb = 0;
	max = (gb_regs.lcdc.obj_size ? 16 : 8);
	obj = (struct s_oam_obj *)(RAM + 0xfe00);
	while (x >= 0)
	{
		if (y >= obj[x].y - 16 && y < (obj[x].y - 16 + max))
		{
			print_obj_line(&obj[x], y + 16 - obj[x].y, max);
			nb++;
		}
		if (nb == 10)
			return ;
		x--;
	}
}

void	Emulateur::line_round(uint64_t line_cycle, uint8_t ly, bool print)
{
	if (line_cycle == 0)
	{
		gb_regs.stat.mode = 2;
		if (gb_regs.stat.imode2)
				gb_regs.iflag.lcdc = true;
	}
	else if (line_cycle == 172)
		gb_regs.stat.mode = 3;
	else if (line_cycle == 252)
	{
		if (print) {
			print_bg_line(ly);
			if (gb_regs.lcdc.window && ly >= RAM[REG_WY])
				print_window_line(ly);
			if (gb_regs.lcdc.obj_display)
				print_objs_line(ly);
		}
		gb_regs.stat.mode = 0;
		if (gb_regs.stat.imode0)
			gb_regs.iflag.lcdc = true;
		if (cgb.on) {
			uint8_t hdma5 = _MBC.mem_read(RAM + REG_HDMA5, 1);
			if (hdma5 & 0x80) {
				uint8_t hdma1 = _MBC.mem_read(RAM + REG_HDMA1, 1);
				uint8_t hdma3 = _MBC.mem_read(RAM + REG_HDMA3, 1);
				// memcpy()
			}
		}
	}
}

void	Emulateur::vblank_round(uint64_t line_cycle, uint8_t ly, bool print)
{
	if (ly == 144 && line_cycle == 0)
	{
		if (print)
			render();
		gb_regs.stat.mode = 1;
		if (gb_regs.stat.imode1)
			gb_regs.iflag.lcdc = true;
		gb_regs.iflag.vblank = true;
	}
}

void	Emulateur::update_lcd()
{
	uint64_t				line_cycle;
	uint8_t					ly;
	static uint8_t			img = 0;
	bool					print;

	if (!gb_regs.lcdc.on)
	{
		_lcd_cycle = 0;
		return ;
	}
	line_cycle = _lcd_cycle % 456;
	ly = _lcd_cycle / 456;
	if (line_cycle == 0)
		_MBC.mem_write(&RAM[REG_LY], ly % 154, 1);
	print = !(img % (_frequency >> 22));
	if (ly < 144)
		line_round(line_cycle, ly, print);
	else
		vblank_round(line_cycle, ly, print);
	if (_lcd_cycle + 4 == 70224)
		img = (img + 1) % 6;
	_lcd_cycle = (_lcd_cycle + 4) % 70224;
}
