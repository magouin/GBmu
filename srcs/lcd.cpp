#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>


uint32_t		Emulateur::bit_to_gray(uint8_t b, uint16_t *pal_addr)
{
	if (b == 0 && pal_addr != reinterpret_cast<uint16_t *>(RAM + 0xff47))
		return (0);
	b = (*pal_addr >> ((b & 3) * 2)) & 3;
	if (b == 0)
		return (COLOR_DMG_00);
	if (b == 1)
		return (COLOR_DMG_01);
	if (b == 2)
		return (COLOR_DMG_10);
	return (COLOR_DMG_11);
}

uint32_t		Emulateur::bit_to_color(uint8_t b, uint16_t *pal_addr)
{
	uint16_t color;
	uint32_t rez;
	uint64_t tmp = reinterpret_cast<uint8_t *>(pal_addr) - _MBC.pal_col_obj;

	if (b == 0 && tmp < 64 && tmp >= 0)
		return (0);
	color = pal_addr[b];
	rez = (0xff << 24) | ((color & 0x1f) << 3) | ((color & 0x3e0) << 6) | ((color & 0x7c00) << 9);
	return (rez);
}

bool		Emulateur::check_prio(int x, int y)
{
	return(_screen_prio[x + y * 160]);
}


void	Emulateur::print_bg_tile_line(const uint8_t *tile, const struct s_bg_atrb &bg, int x, int y, int h)
{
	int w;
	uint32_t p;
	uint16_t cx, cy;
	uint16_t *pal_addr;
	uint8_t		bits;
	uint32_t	(Emulateur::*bit_conv)(uint8_t , uint16_t *);

	if (cgb.on)
	{
		pal_addr = reinterpret_cast<uint16_t *>(_MBC.pal_col_bg + bg.pal_nb * 8);
		bit_conv = &Emulateur::bit_to_color;
		h = bg.vflip ? (7 - h) : h;
	}
	else
	{
		pal_addr = reinterpret_cast<uint16_t *>(RAM + 0xff47);
		bit_conv = &Emulateur::bit_to_gray;
	}
	w = 0;
	while (w < 8)
	{
		bits = (((tile[h * 2 + 1] >> (7 - w)) << 1) & 2) | ((tile[h * 2] >> (7 - w)) & 1);
		p = (this->*bit_conv)(bits, pal_addr);
		cx = x + (cgb.on && bg.hflip ? (7 - w) : w);
		cy = y + (cgb.on && bg.vflip ? (7 - h) : h);
		set_pixel(p, cx, cy, bits);
		w++;
	}
}

void	Emulateur::print_obj_tile_line(const uint8_t *tile, struct s_oam_obj &obj, uint8_t size, int off)
{
	int			w;
	int			h;
	uint32_t	p;
	uint16_t	cx, cy;
	uint16_t	*pal_addr;
	uint8_t		bits;
	uint32_t	(Emulateur::*bit_conv)(uint8_t , uint16_t *);

	if (cgb.on)
	{
		bit_conv = &Emulateur::bit_to_color;
		pal_addr = reinterpret_cast<uint16_t *>(_MBC.pal_col_obj + obj.color_pal * 8);
	}
	else
	{
		bit_conv = &Emulateur::bit_to_gray;
		pal_addr = reinterpret_cast<uint16_t *>(RAM + 0xff48 + obj.mono_pal);
	}
	w = 0;
	h = obj.v_flip ? (size - 1 - off) : off;
	while (w < 8)
	{
		bits = (((tile[h * 2 + 1] >> (7 - w)) << 1) & 2) | ((tile[h * 2] >> (7 - w)) & 1);
		p = (this->*bit_conv)(bits, pal_addr);
		cx = obj.x - 8 + (obj.h_flip ? (7 - w) : w);
		cy = obj.y - 16 + off;
		if (bits && (obj.prio == 0 || !check_prio(cx, cy)))
			set_pixel(p, cx, cy, true);
		w++;
	}
}

void	Emulateur::print_bg_line(int y)
{
	const uint8_t			*b_code;
	const uint8_t			*b_data;
	const uint8_t			*data;
	uint8_t					code;
	uint32_t				cy;
	uint8_t					x;
	uint32_t				id_line;
	uint32_t				offset_line;
	uint32_t				index;
	struct s_bg_atrb		atrb;

	b_code = RAM + (gb_regs.lcdc.bg_code_addr ? 0x9c00 : 0x9800);
	b_data = RAM + (gb_regs.lcdc.bg_data_addr ? 0x8000 : 0x9000);
	cy = (RAM[REG_SCY] + y) % 256;
	x = 0;
	while (x < 21)
	{
		id_line = cy / 8;
		offset_line = cy % 8;
		index = (id_line * 32) + (((RAM[REG_SCX] >> 3) + x) % 32);
		code = b_code[index];
		data = b_data + (code * 16);
		if (data >= RAM + 0x9800)
			data -= 0x1000;
		if (cgb.on)
		{
			atrb = _MBC.get_bg_atrb(gb_regs.lcdc.bg_code_addr, index);
			if (atrb.bank_nb)
				data = _MBC.get_ram_video_bank1() + (data - RAM - 0x8000);
		}
		print_bg_tile_line(data, atrb, x * 8 - (RAM[REG_SCX] & 7), y - offset_line, offset_line);
		x++;
	}
}

void	Emulateur::print_window_line(int y)
{
	const uint8_t		*b_code;
	const uint8_t		*b_data;
	const uint8_t		*data;
	uint8_t				code;
	uint8_t				x;
	uint8_t				off;
	uint32_t			index;
	struct s_bg_atrb	atrb;

	b_code = RAM + (gb_regs.lcdc.window_code_addr ? 0x9c00 : 0x9800);
	b_data = RAM + (gb_regs.lcdc.bg_data_addr ? 0x8000 : 0x9000);
	x = 0;
	off = (y - RAM[REG_WY]) & 7;
	while (x * 8 + RAM[REG_WX] - 7 < 160)
	{
		index = (((y - RAM[REG_WY]) >> 3) * 32) + x;
		code = b_code[index];
		data = b_data + (code * 16);
		if (data >= RAM + 0x9800)
			data -= 0x1000;
		if (cgb.on)
		{
			atrb = _MBC.get_bg_atrb(gb_regs.lcdc.window_code_addr, index);
			if (atrb.bank_nb)
				data = _MBC.get_ram_video_bank1() + (data - RAM - 0x8000);
		}
		print_bg_tile_line(data, atrb, x * 8 + RAM[REG_WX] - 7, y - ((y - RAM[REG_WY]) & 7), (y - RAM[REG_WY]) & 7);
		x++;
	}
}

void	Emulateur::print_obj_line(struct s_oam_obj &obj, int off, int size)
{
	const uint8_t	*tile;

	obj.chrcode &= (gb_regs.lcdc.obj_size ? ~1 : ~0);
	if (cgb.on && obj.char_bank)
		tile = _MBC.get_ram_video_bank1() + (obj.chrcode * 0x10);
	else
		tile = RAM + 0x8000 + (obj.chrcode * 0x10);
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
			print_obj_line(obj[x], y + 16 - obj[x].y, max);
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
			if (gb_regs.lcdc.window && ly >= RAM[REG_WY])
				print_window_line(ly);
			else
				print_bg_line(ly);
			if (gb_regs.lcdc.obj_display)
				print_objs_line(ly);
		}
		gb_regs.stat.mode = 0;
		if (gb_regs.stat.imode0)
			gb_regs.iflag.lcdc = true;
		if (cgb.on) {
			uint8_t hdma5 = _MBC.mem_read(RAM + REG_HDMA5, 1);
			if (!(hdma5 & 0x80)) {
				printf("H Blank DMA\n");
				_MBC.new_dma(dst_dma, src_dma, 16);
				RAM[REG_HDMA5]--;
				dst_dma += 16;
				src_dma += 16;
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
	static bool				increment_lcd_cycle = true;

	if (!gb_regs.lcdc.on)
		return ;
	if (cgb.on && cgb.mode_double_speed)
	{
		increment_lcd_cycle = !increment_lcd_cycle;
		if (!increment_lcd_cycle)
			return ;
	}
	line_cycle = lcd_cycle % 456;
	ly = lcd_cycle / 456;
	if (line_cycle == 0)
		_MBC.inc_ly(ly);
	print = !(img % (_frequency >> (22 + (cgb.on && (gb_regs.key1 & 0x80)))));
	if (ly < 144 && gb_regs.lcdc.on)
		line_round(line_cycle, ly, print);
	else
		vblank_round(line_cycle, ly, print);
	if (lcd_cycle + 4 == 70224)
		img = (img + 1) % 6;
	lcd_cycle = (lcd_cycle + 4) % 70224;
}
