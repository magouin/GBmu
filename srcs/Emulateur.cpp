#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>

Emulateur::Emulateur()
{
}

Emulateur::Emulateur(std::string rom): _ram_regs({RAM_REGS}), _op203({OP203}), _opcode({OPCODE}), _ROM(rom)
{
	bzero(_RAM, sizeof(_RAM));
	_cycle = 0;
	_IME = true;
}

Emulateur::Emulateur(const Emulateur & cp)
{
	(void)cp;
}

Emulateur::~Emulateur()
{
}

Emulateur &	Emulateur::operator=(const Emulateur & cp)
{
	(void)cp;
	return (*this);
}



void	Emulateur::print_regs(void)
{
	int i;

	i = 0;
	printf("A: %02hhX  F: %02hhX  (AF: %04hX)\n", this->regs.af.af.A, this->regs.af.af.F, this->regs.af.AF);
	printf("B: %02hhX  C: %02hhX  (BC: %04hX)\n", this->regs.bc.bc.B, this->regs.bc.bc.C, this->regs.bc.BC);
	printf("D: %02hhX  E: %02hhX  (DE: %04hX)\n", this->regs.de.de.D, this->regs.de.de.E, this->regs.de.DE);
	printf("H: %02hhX  L: %02hhX  (HL: %04hX)\n", this->regs.hl.hl.H, this->regs.hl.hl.L, this->regs.hl.HL);
	printf("PC: %04hX  SP: %04X\n", this->regs.PC, this->regs.SP);
	printf("ROM: 01  RAM: 00  WRAM: %02X  VRAM: %02X\n", (_RAM[0xff70] & 7) ? (_RAM[0xff70] & 7) : 1, _RAM[0xff4f]);
	printf("F: [");
	this->regs.af.af.F & FLAG_Z ? printf("Z") : printf("-");
	this->regs.af.af.F & FLAG_N ? printf("N") : printf("-");
	this->regs.af.af.F & FLAG_H ? printf("H") : printf("-");
	this->regs.af.af.F & FLAG_CY ? printf("C") : printf("-");
	printf("]\n");


}

void	Emulateur::init_registers(void)
{
	this->regs.af.AF = 0x01B0; // Il faudra faire gaffe a A
	this->regs.bc.BC = 0x0013;
	this->regs.de.DE = 0x00d8;
	this->regs.hl.HL = 0x014d;

	// this->regs.af.AF = 0x1180; // cpu_instr
	// this->regs.bc.BC = 0x0000;
	// this->regs.de.DE = 0x0008;
	// this->regs.hl.HL = 0x007c;
	this->regs.SP = 0xfffe;


	this->_RAM[0xff00] = 0x00; // P1
	this->_RAM[0xff05] = 0x00; // TIMA
	this->_RAM[0xff06] = 0x00; // TMA 
	this->_RAM[0xff07] = 0x00; // TAC
	this->_RAM[0xff10] = 0x80; // NR10
	this->_RAM[0xff11] = 0xbf; // NR11
	this->_RAM[0xff12] = 0xf3; // NR12
	this->_RAM[0xff14] = 0xbf; // NR14
	this->_RAM[0xff16] = 0x3f; // NR21
	this->_RAM[0xff17] = 0x00; // NR22
	this->_RAM[0xff19] = 0xbf; // NR24
	this->_RAM[0xff1a] = 0x7f; // NR30
	this->_RAM[0xff1b] = 0xff; // NR31
	this->_RAM[0xff1c] = 0x9f; // NR32
	this->_RAM[0xff1e] = 0xbf; // NR33
	this->_RAM[0xff20] = 0xff; // NR41
	this->_RAM[0xff21] = 0x00; // NR42
	this->_RAM[0xff22] = 0x00; // NR43
	this->_RAM[0xff23] = 0xbf; // NR30
	this->_RAM[0xff24] = 0x77; // NR50
	this->_RAM[0xff25] = 0xf3; // NR51
	this->_RAM[0xff26] = 0xf1; // NR52
	this->_RAM[0xff40] = 0x91; // LCDC
	this->_RAM[0xff42] = 0x00; // SCY
	this->_RAM[0xff43] = 0x00; // SCX
	this->_RAM[0xff44] = 0x05; // LY
	this->_RAM[0xff45] = 0x00; // LYC
	this->_RAM[0xff47] = 0xfc; // BGP
	this->_RAM[0xff48] = 0xff; // OBPO
	this->_RAM[0xff49] = 0xff; // OBP1
	this->_RAM[0xff4a] = 0x00; // WY
	this->_RAM[0xff4b] = 0x00; // WX
	this->_RAM[0xffff] = 0x00; // IE
}

uint32_t	Emulateur::get_time_from_frequency(uint8_t	freq)
{
	const uint8_t				num_to_byte[4] = {10, 4, 6, 8};

	if (num_to_byte[freq] < 8)
		return ((_timer + (_RAM[0xFF04] << 8)) >> num_to_byte[freq]);
	return (_RAM[0xFF04] >> ((num_to_byte[freq]) - 8));
}

int			Emulateur::tima_thread(void *data)
{
	static bool			start = false;
	static uint32_t		last_time;
	uint32_t			tmp_time;
	const uint8_t		num_to_byte[4] = {10, 4, 6, 8};

	while (true)
	{
		if (start != _RAM[0xFF07])
		{
			start = !start;
			last_time = get_time_from_frequency(_RAM[0xFF07] & 0x3);
		}
		else if (start)
		{
			tmp_time = get_time_from_frequency(_RAM[0xFF07] & 0x3);
			if (tmp_time < last_time)
				tmp_time += -1u >> num_to_byte[_RAM[0xFF07] & 0x3];
			if (_RAM[0xFF05] + (uint8_t)(tmp_time - last_time) > 255)
			{
				_RAM[0xFF05] = _RAM[0xFF06];
				_RAM[0xFF0F] |= 2;
			}
			_RAM[0xFF05] += (uint8_t)(tmp_time - last_time);
		}
	}
	return (0);
}

int			Emulateur::timer_thread(void *data)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, tmp, time;
	uint32_t nsecond_per_tick;

	nsecond_per_tick = (1.0 / _frequency) * 1000 * 1000 * 1000;
	// printf("nsecond_per_tick = %d\n", nsecond_per_tick);
	start = std::chrono::high_resolution_clock::now();
	_timer = 0; 
	_timer_counter = 0; 
	_timer_status = true;
	while (true)
	{
		time = std::chrono::high_resolution_clock::now();
		while ((time - start).count() < nsecond_per_tick)
			time = std::chrono::high_resolution_clock::now();
		start = time;
		if (_timer_status == false)
		{
			// printf("Timer = %llx\n", _timer + _timer_counter * 256);
			while (_timer_status == false) ;
			start = std::chrono::high_resolution_clock::now();
		}
		_timer++;
		if (_timer == 256)
		{
			_timer = 0;
			_timer_counter++;
			_RAM[0xFF04]++;
		}
	}
}

uint8_t		Emulateur::bit_to_gray(uint8_t b)
{
	b = (_RAM[0xff47] >> (b * 2)) & 3;
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

void	Emulateur::print_tile(uint8_t *tile, int x, int y)
{
	int h, w;
	uint8_t p;

	h = 0;
	while (h < 8)
	{
		w = 0;
		while (w < 8)
		{
			p = bit_to_gray((((tile[h * 2] >> w) << 1) & 2) | ((tile[h * 2 + 1] >> w) & 1));
			// if ((p & 3) == 2)
			// {
			// 	printf("with w : %x -- tile[x] = %x et tile[x + 1] = %x\n", w, tile[h * 2], tile[h * 2 + 1]);
			// 	printf("(tile[h * 2] >> w << 1) = %x\n", (tile[h * 2] >> w << 1));
			// 	printf("(tile[h * 2 + 1] >> w) = %x\n", (tile[h * 2 + 1] >> w));
			// }
			set_pixel(graytopixel(p), x * 8 + (7 - w), y * 8 + h);
			w++;
		}
		h++;
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
		print_tile(_RAM + 0x8000 + (x * 16), (x % 20), x / 20);
		x++;
	}
}

void	Emulateur::print_bg()
{
	uint8_t	*b_code;
	uint8_t	*b_data;
	uint8_t	code;
	int		x, y;
	uint8_t	scx, scy;

	b_code = _RAM + ((_RAM[0xff40] & (1 << 3)) ? 0x9c00 : 0x9800);
	y = 0;
	scx = _RAM[0xff43] >> 3;
	scy = _RAM[0xff42] >> 3;
	// printf("SCX -> [%hhx] | SCY -> [%hhx]\n", scx, scy);
	while (y < 18)
	{
		x = 0;
		while (x < 20)
		{
			code = b_code[(y + scy) * 32 + (scx + x) % 32];
			b_data = _RAM + (_RAM[0xff40] & (1 << 4) ? 0x8000 : 0x8800);
			if (code >= 0x80)
			{
				b_data = _RAM + 0x8800;
				code -= 0x80;
			}
			print_tile(b_data + (code * 16), x, y);
			x++;
		}
		y++;
	}
}
void	Emulateur::interrupt_func(short addr, uint8_t iflag)
{
	_IME = false;
	_RAM[0xFF0F] &= ~iflag;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.af.AF;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.bc.BC;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.de.DE;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.hl.HL;
	this->regs.SP -= 2;
	*(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.PC;
	_idata.old_pc = this->regs.PC; 
	regs.PC = addr;
	_idata.routine = true; 
}

void	Emulateur::interrupt(void)
{
	if (!_IME)
		return ;
	if(_RAM[0xFF0F] & 16 && _RAM[0xFFFF] & 16)
		interrupt_func(0x0060, 16);
	else if(_RAM[0xFF0F] & 8 && _RAM[0xFFFF] & 8)
		interrupt_func(0x0058, 8);
	else if(_RAM[0xFF0F] & 4 && _RAM[0xFFFF] & 4)
		interrupt_func(0x0050, 4);
	else if(_RAM[0xFF0F] & 2 && _RAM[0xFFFF] & 2)
		interrupt_func(0x0048, 2);
	else if(_RAM[0xFF0F] & 1 && _RAM[0xFFFF] & 1)
		interrupt_func(0x0040, 1);
}

void	Emulateur::print_line(uint64_t ly, uint64_t start, const uint64_t line_time)
{
	
}

int		Emulateur::lcd_thread(void *data)
{
	uint64_t		start;
	uint64_t		ly;
	const uint64_t	line_time = 252;
	const uint64_t	scanline_time = 456;
	int x;

	x = 0;
	while (true)
	{
		start = _timer_counter * 256 + _timer;
		_RAM[0xff44] = 0;
		print_bg();
		// printf("\nDump %d\n", x);
		// dump_data_tiles();
		x++;
		// print_all_tiles();
		ly = 0;
		while (ly < 154)
		{
			if (ly < 144)
			{
				_RAM[0xff41] = (_RAM[0xff41] & ~(uint8_t)3) | 2;
				//print_line(ly);
				while (start + ly * scanline_time + line_time > _timer_counter * 256 + _timer) ;
				_RAM[0xff41] = (_RAM[0xff41] & ~(uint8_t)3) | 0;
			}
			else if (ly == 144)
			{
				_RAM[0xff41] = (_RAM[0xff41] & ~(uint8_t)3) | 1;
				_RAM[0xff0f] |= 1;
			}
			while (start + (ly + 1) * scanline_time > _timer_counter * 256 + _timer) ;
			_RAM[0xff44]++;
			ly++;
		}
		printf("ff47 = %x", _RAM[0xff47]);
		// printf("IPS = %f\n", 1.0 / (((_timer_counter * 256 + _timer) - start) * 238.0 / 1000.0 / 1000.0 / 1000.0));
	}
}


int		Emulateur::cpu_thread(void *data)
{
	const struct s_instruction_params	*instr;

	memcpy(_RAM, _ROM.c_str(), 0x8000);
	_frequency = 4194300; // Need to change if it is a CGB
	# ifdef DEBUG
		_frequency = 41943; // Need to change if it is a CGB
	# endif
	this->regs.PC = _begin;

	init_registers();
	this->_cycle = 0;

	while (true)
	{
		interrupt();
		// printf("_opcode[%d]\n", this->_RAM[this->regs.PC]);
		// printf("mnemonic = %s\n", _opcode[this->_RAM[this->regs.PC]].mnemonic.c_str());
		instr = &_opcode[this->_RAM[this->regs.PC]];
		# ifdef DEBUG
			char c[2];
			_timer_status = false;

			print_regs();
			if (!read(0, &c, 2)) // to change
				exit(0);
			_timer_status = true;
			// std::cout << instr->mnemonic << " -> ";
		# endif
		this->regs.PC += 1 + instr->nb_params * 1;
		instr->f();
		// if (this->_cycle + 1000000 < _timer + _timer_counter * 256)
		// 	printf("_cycle = %llu et _timer = %llu\n", this->_cycle, _timer + _timer_counter * 256);
			// std::cout << "J'ai du retard ??\n";
		while (this->_cycle * 4 > _timer + _timer_counter * 256) ;
		// std::cout << std::endl;
	}
}

int Emulateur::create_cpu_thread(void *ptr)
{
	Emulateur *p;

	p = (Emulateur*)ptr;
	try {
		return p->cpu_thread(NULL);
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
		exit(0);
	};
}

int Emulateur::create_lcd_thread(void *ptr)
{
	Emulateur *p;

	p = (Emulateur*)ptr;
	return p->lcd_thread(NULL);
}

int Emulateur::create_timer_thread(void *ptr)
{
	Emulateur *p;

	p = (Emulateur*)ptr;
	return p->timer_thread(NULL);
}

int Emulateur::create_tima_thread(void *ptr)
{
	Emulateur *p;

	p = (Emulateur*)ptr;
	return p->tima_thread(NULL);
}

// void	signal_handler(int signal)
// {
// 	SDL_Quit();
// }

// void	Emulateur::catch_signals(void)
// {
// 	signal(SIGABRT, signal_handler);
// 	signal(SIGFPE, signal_handler);
// 	signal(SIGILL, signal_handler);
// 	signal(SIGINT, signal_handler);
// 	signal(SIGSEGV, signal_handler);
// 	signal(SIGTERM, signal_handler);
// }

void	Emulateur::emu_start(uint32_t begin, uint32_t end)
{
	sdl_init();

	_begin = begin;
	_end = end;

	_cpu_thread = SDL_CreateThread(&Emulateur::create_cpu_thread, "cpu_thread", (void*)this);
	_lcd_thread = SDL_CreateThread(&Emulateur::create_lcd_thread, "lcd_thread", (void*)this);
	_timer_thread = SDL_CreateThread(&Emulateur::create_timer_thread, "timer_thread", (void *)this);
	_tima_thread = SDL_CreateThread(&Emulateur::create_tima_thread, "tima_thread", (void *)this);


	memset(_pixels_map, (uint8_t)0xff, sizeof(_pixels_map));
	_input.p14 = 0xff;
	_input.p15 = 0xff;
	while (true)
	{
		if (!update())
			break ;
		render();
	}
	SDL_Quit();
	exit(1);
}
