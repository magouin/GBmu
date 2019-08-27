#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>

Emulateur::Emulateur()
{
}

Emulateur::Emulateur(std::string rom): _ram_regs({RAM_REGS}), _op203({OP203}), _opcode({OPCODE}), _cv_instrs({CYCLE_VARIABLE_OPCODE}), _header(rom), _ROM(rom)
{
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
	printf("A: %02hhX  F: %02hhX  (AF: %04hX)\n", this->regs.A, this->regs.F, this->regs.AF);
	printf("B: %02hhX  C: %02hhX  (BC: %04hX)\n", this->regs.B, this->regs.C, this->regs.BC);
	printf("D: %02hhX  E: %02hhX  (DE: %04hX)\n", this->regs.D, this->regs.E, this->regs.DE);
	printf("H: %02hhX  L: %02hhX  (HL: %04hX)\n", this->regs.H, this->regs.L, this->regs.HL);
	printf("PC: %04hX  SP: %04X\n", this->regs.PC, this->regs.SP);
	printf("ROM: 01  RAM: 00  WRAM: %02X  VRAM: %02X\n", (_RAM[0xff70] & 7) ? (_RAM[0xff70] & 7) : 1, _RAM[0xff4f]);
	printf("F: [");
	this->regs.F & FLAG_Z ? printf("Z") : printf("-");
	this->regs.F & FLAG_N ? printf("N") : printf("-");
	this->regs.F & FLAG_H ? printf("H") : printf("-");
	this->regs.F & FLAG_CY ? printf("C") : printf("-");
	printf("]\n");


}

void	Emulateur::init_registers(void)
{
	regs.AF = 0x01B0; // Il faudra faire gaffe a A
	regs.BC = 0x0013;
	regs.DE = 0x00d8;	
	regs.HL = 0x014d;

	// regs.AF = 0x1180; // cpu_instr
	// regs.BC = 0x0000;
	// regs.DE = 0x0008;
	// regs.HL = 0x007c;
	regs.SP = 0xfffe;
	regs.PC = 0x100;
	regs.IME = false;
	regs.RAM_ENABLE = false;
	regs.ROM_BANK = 1;
	regs.ROM_RAM_BANK = 0;
	regs.ROM_RAM_SELECT = 0;


	_RAM[REG_P1] = 0x00; // P1
	_RAM[REG_DIV] = 0x00; // TIMA
	_RAM[0xff06] = 0x00; // TMA 
	_RAM[REG_TAC] = 0x00; // TAC
	_RAM[0xff10] = 0x80; // NR10
	_RAM[0xff11] = 0xbf; // NR11
	_RAM[0xff12] = 0xf3; // NR12
	_RAM[0xff14] = 0xbf; // NR14
	_RAM[0xff16] = 0x3f; // NR21
	_RAM[0xff17] = 0x00; // NR22
	_RAM[0xff19] = 0xbf; // NR24
	_RAM[0xff1a] = 0x7f; // NR30
	_RAM[0xff1b] = 0xff; // NR31
	_RAM[0xff1c] = 0x9f; // NR32
	_RAM[0xff1e] = 0xbf; // NR33
	_RAM[0xff20] = 0xff; // NR41
	_RAM[0xff21] = 0x00; // NR42
	_RAM[0xff22] = 0x00; // NR43
	_RAM[0xff23] = 0xbf; // NR30
	_RAM[0xff24] = 0x77; // NR50
	_RAM[0xff25] = 0xf3; // NR51
	_RAM[0xff26] = 0xf1; // NR52
	_RAM[REG_LCDC] = 0x91; // LCDC
	_RAM[0xff42] = 0x00; // SCY
	_RAM[0xff43] = 0x00; // SCX
	_RAM[REG_LY] = 0x05; // LY
	_RAM[REG_LYC] = 0x00; // LYC
	_RAM[0xff47] = 0xfc; // BGP
	_RAM[0xff48] = 0xff; // OBPO
	_RAM[0xff49] = 0xff; // OBP1
	_RAM[0xff4a] = 0x00; // WY
	_RAM[0xff4b] = 0x00; // WX
	_RAM[REG_IE] = 0x00; // IE
}

// bool	Emulateur::get_time_from_frequency(uint8_t	freq)
// {
// 	const uint8_t	num_to_byte[4] = {10, 4, 6, 8};

// 	if (freq == 0)
// 		return (_RAM[REG_DIV] >> 1);
// 	return ((_timer + (_RAM[REG_DIV] << 8)) >> num_to_byte[freq]);
// }

int			Emulateur::tima_thread(void *data)
{
	static uint32_t	last_time;
	uint32_t		tmp_time;
	const uint8_t	num_to_byte[4] = {10, 4, 6, 8};
	uint64_t		start;
	uint8_t			nb_tick;

	while (_RAM[REG_TAC] & 0x4)
	{
		start = _timer_counter * 256 + _timer;
		nb_tick = (1 << num_to_byte[_RAM[REG_TAC] & 0x3]);
		while ((_timer_counter * 256 + _timer - start) < nb_tick) ;
		if (_RAM[REG_TIMA] == 0xff)
		{
			_RAM[REG_TIMA] = _RAM[0xFF06];
			_RAM[REG_IF] |= 2;
		}
		else
			_RAM[REG_TIMA]++;
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
	while (true)
	{
		if (_stop_status)
			continue ;
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
			_RAM[REG_DIV]++;
		}
	}
}

void	Emulateur::interrupt_func(short addr, uint8_t iflag)
{
	regs.IME = false;
	_RAM[REG_IF] &= ~iflag;
	this->regs.SP -= 2;
	*(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.PC;
	regs.PC = addr;
}

void	Emulateur::interrupt(void)
{
	if (!regs.IME)
	{
		// printf("Leaving _halt_status because ime disabled\n");
		_halt_status = false;
		return ;
	}
	if(_RAM[REG_IF] & 16 && _RAM[REG_IE] & 16) // Joypad
		interrupt_func(0x0060, 16);
	else if(_RAM[REG_IF] & 8 && _RAM[REG_IE] & 8) // Serial
		interrupt_func(0x0058, 8);
	else if(_RAM[REG_IF] & 4 && _RAM[REG_IE] & 4) // Timer
		interrupt_func(0x0050, 4);
	else if(_RAM[REG_IF] & 2 && _RAM[REG_IE] & 2) // LCD STAT
		interrupt_func(0x0048, 2);
	else if(_RAM[REG_IF] & 1 && _RAM[REG_IE] & 1) // V-Blank
		interrupt_func(0x0040, 1);
	else
		return ;
	// if (_halt_status == true)
	// 	printf("Leaving _halt_status\n");
	_halt_status = false;
}

int		Emulateur::cpu_thread(void *data)
{
	const struct s_instr_params	*instr;

	while (true)
	{
		interrupt();
		if (_halt_status)
			continue ;
		// printf("_opcode[%d]\n", this->_RAM[this->regs.PC]);
		// printf("mnemonic = %s, PC = %hx\n", _opcode[this->_RAM[this->regs.PC]].mnemonic.c_str(), regs.PC);
		instr = &_opcode[mem_read(_RAM + regs.PC, 1)];
		# ifdef DEBUG
			char c[2];
			_timer_status = false;

			print_regs();
			if (!read(0, &c, 2)) // to change
				exit(0);
			_timer_status = true;
		# endif
		this->regs.PC += 1 + instr->nb_params * 1;
		instr->f();
		while (this->_cycle * 4 > _timer + _timer_counter * 256) ;
	}
}

int Emulateur::create_cpu_thread(void *ptr)
{
	Emulateur *p;

	p = (Emulateur*)ptr;
		return p->cpu_thread(NULL);
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

void Emulateur::emu_init()
{
	bzero(_RAM, sizeof(_RAM));
	printf("allocated %zu RAM\n", _header.get_ram_size());
	_external_ram = (_header.get_ram_size() > 0) ? new uint8_t[_header.get_ram_size()] : _RAM + 0xa000;
	_rom_bank = (const uint8_t*)(_ROM.c_str() + 0x4000);
	_ram_bank = _external_ram;

	_cycle = 0;
	regs.IME = true;
	memset(_pixels_map, (uint8_t)0xff, sizeof(_pixels_map));
	_input.p14 = 0xff;
	_input.p15 = 0xff;
	_halt_status = false;
	_stop_status = false;
	sdl_init();
	memcpy(_RAM, _ROM.c_str(), 0x8000);
	_frequency = 4194300; // Need to change if it is a CGB
	# ifdef DEBUG
		_frequency = 41943; // Need to change if it is a CGB
	# endif
	init_registers();

	_timer = 0; 
	_timer_counter = 0; 
	_timer_status = true;
}

const struct s_cv_instr *Emulateur::get_cv_infos(uint8_t opcode) const
{
	size_t										i;
	const struct s_cv_instr	*ret;

	i = 0;
	while (i < _cv_instrs.size())
	{
		ret = &_cv_instrs[i];
		if (ret->opcode == opcode)
			return (ret);
		i++;
	}
	printf("ERROR : instr info not found c'est pas normal du tout -- opcode : 0x%X\n", opcode);
	return (NULL);
}

void Emulateur::exec_instr()
{
	const struct s_instr_params			*instr;
	const struct s_cv_instr	*cvi;

	if (_halt_status)
		return ;
	instr = &_opcode[mem_read(_RAM + regs.PC, 1)];
	// # ifdef DEBUG
	// 	char c[2];
	// 	_timer_status = false;

	// 	print_regs();
	// 	if (!read(0, &c, 2)) // to change
	// 		exit(0);
	// 	_timer_status = true;
	// # endif

	if (_current_instr_cycle == 0)
	{
		if (instr->cycle_nb == 0)
		{
			if (instr->opcode == 203)
			{
				instr = &_opcode[mem_read(_RAM + regs.PC + 1, 1)];
				_current_instr_cycle = instr->cycle_nb;
			}
			else
			{
				cvi = get_cv_infos(instr->opcode);
				if (!check_rules(cvi->condition))
				{
					_current_instr_cycle = cvi->cycle_false;
					_exec_current_instr = false;
				}
				else
					_current_instr_cycle = cvi->cycle_true;
			}
		}
		else
			_current_instr_cycle = instr->cycle_nb;
	}
	_current_instr_cycle--;
	if (_current_instr_cycle == 0)
	{
		regs.PC += 1 + instr->nb_params * 1;
		if (_exec_current_instr)
			instr->f();
		_exec_current_instr = true;
	}
}

void	Emulateur::emu_start()
{
	emu_init();

	// _cpu_thread = SDL_CreateThread(&Emulateur::create_cpu_thread, "cpu_thread", (void*)this);
	// _lcd_thread = SDL_CreateThread(&Emulateur::create_lcd_thread, "lcd_thread", (void*)this);
	// _timer_thread = SDL_CreateThread(&Emulateur::create_timer_thread, "timer_thread", (void *)this);
	// _tima_thread = SDL_CreateThread(&Emulateur::create_tima_thread, "tima_thread", (void *)this);

	while (true)
	{
		// update_timer();
		// update_lcd();
		// interrupt();
		exec_instr();
		_cycle += 4;
	}
	update();
	SDL_Quit();
	exit(1);
}
