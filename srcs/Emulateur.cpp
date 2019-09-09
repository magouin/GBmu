#include <Emulateur.hpp>
#include <ram_regs.hpp>
#include <opcode.hpp>
#include <op203.hpp>

Emulateur::Emulateur()
{
}

Emulateur::Emulateur(std::string file, std::string rom, bool debug): _ram_regs({RAM_REGS}), _op203({OP203}), _opcode({OPCODE}), _cv_instrs({CYCLE_VARIABLE_OPCODE}), _header(rom), _ROM(rom), _file_name(file), _debug(debug)
{
	std::cout << file << std::endl;
	std::cout << file.find_last_of('.') << std::endl;
	_save_name = file.substr(0, file.find_last_of('.')) + ".sav";
	// std::cout << _save_file << std::endl;
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
	printf("ROM: %02x  RAM: %02x  WRAM: %02X  VRAM: %02X\n", (uint8_t)(((uint8_t *)_rom_bank - (uint8_t *)_ROM.c_str()) / 0x4000), (uint8_t)(((uint8_t *)_ram_bank - (uint8_t *)_external_ram) / 0x2000), (_RAM[0xff70] & 7) ? (_RAM[0xff70] & 7) : 1, _RAM[0xff4f]);
	printf("F: [");
	this->regs.F & FLAG_Z ? printf("Z") : printf("-");
	this->regs.F & FLAG_N ? printf("N") : printf("-");
	this->regs.F & FLAG_H ? printf("H") : printf("-");
	this->regs.F & FLAG_CY ? printf("C") : printf("-");
	printf("]\n");
	if (regs.PC == 0xD821)
		printf("INSTR = %s ||| A = %hhx ||| B = %hhx\n", _opcode[_RAM[regs.PC - 1]].mnemonic.c_str(), regs.A, regs.B);
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
	_RAM[REG_SCY] = 0x00; // SCY
	_RAM[REG_SCX] = 0x00; // SCX

	_RAM[REG_LY] = 0x00; // LY

	_RAM[REG_LYC] = 0x00; // LYC
	_RAM[0xff47] = 0xfc; // BGP
	_RAM[0xff48] = 0xff; // OBPO
	_RAM[0xff49] = 0xff; // OBP1
	_RAM[REG_WY] = 0x00; // WY
	_RAM[REG_WX] = 0x00; // WX
	_RAM[REG_IE] = 0x00; // IE
}

void Emulateur::emu_init()
{
	std::ifstream fs;

	_external_ram = (_header.get_ram_size() > 0) ? new uint8_t[_header.get_ram_size()] : _RAM + 0xa000;
	fs.open (_save_name, std::fstream::in | ios::binary);
	if (fs.is_open())
	{
		fs.read((char *)_external_ram, _header.get_ram_size());
		fs.close();
	}
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
	init_registers();

	_timer = 0; 
	_timer_counter = 0; 
	_timer_status = true;

	_lcd_cycle = 0;
	_interrupt_cycle = 0;

	_start_time = std::chrono::system_clock::now();
}


void	Emulateur::interrupt_func(short addr, uint8_t iflag)
{
	// printf("Interruption %d\n", iflag);
	if (_interrupt_cycle == 0)
		_interrupt_cycle = 5;
	_interrupt_cycle--;
	if (_interrupt_cycle == 0)
	{
		_current_instr_cycle = 0;
		regs.IME = false;
		_RAM[REG_IF] &= ~iflag;
		regs.SP -= 2;
		*(uint16_t *)(_RAM + regs.SP) = regs.PC;
		regs.PC = addr;
		if (_debug)
			debug_mode();
	}
}

void	Emulateur::interrupt(void)
{
	if (!regs.IME)
	{
		// printf("Leaving _halt_status because ime disabled\n");
		_halt_status = false;
		return ;
	}
	if(_RAM[REG_IF] & 1 && _RAM[REG_IE] & 1) // V-Blank
		interrupt_func(0x0040, 1);
	else if(_RAM[REG_IF] & 2 && _RAM[REG_IE] & 2) // LCD STAT
		interrupt_func(0x0048, 2);
	else if(_RAM[REG_IF] & 4 && _RAM[REG_IE] & 4) // Timer
		interrupt_func(0x0050, 4);
	else if(_RAM[REG_IF] & 8 && _RAM[REG_IE] & 8) // Serial
		interrupt_func(0x0058, 8);
	else if(_RAM[REG_IF] & 16 && _RAM[REG_IE] & 16) // Joypad
		interrupt_func(0x0060, 16);
	else
		return ;
	// if (_halt_status == true)
	// 	printf("Leaving _halt_status\n");
	_halt_status = false;
}

const struct s_cv_instr *Emulateur::get_cv_infos(uint8_t opcode) const
{
	size_t					i;
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

void	Emulateur::update_tima()
{
	const uint8_t			num_to_byte[4] = {10, 4, 6, 8};
	static uint64_t			nb_tick = 0;
	// static uint64_t			last_cycle = 0;

	// if (last_cycle == 0)
	// 	last_cycle = _cycle;
	if (_RAM[REG_TAC] & 0x4)
	{
		if (nb_tick == 0)
			nb_tick = (1 << (num_to_byte[_RAM[REG_TAC] & 0x3]));
		// nb_tick -= (_cycle - last_cycle);
		nb_tick -= 4;
		// last_cycle = _cycle;
		if (nb_tick == 0)
		{
			if (_RAM[REG_TIMA] != 0xff)
				_RAM[REG_TIMA]++;
			else
			{	
				_RAM[REG_TIMA] = _RAM[0xFF06];
				_RAM[REG_IF] |= 4;
			}
		}
	}
}

void	Emulateur::get_instr()
{
	const struct s_cv_instr	*cvi;

	_instr = &_opcode[mem_read(_RAM + regs.PC, 1)];
	if (_instr->opcode == 203)
		_instr = &_op203[mem_read(_RAM + regs.PC + 1, 1)];
	regs.PC += 1 + _instr->nb_params;
	if (_instr->cycle_nb == 0)
	{
		cvi = get_cv_infos(_instr->opcode);
		if (!check_rules(cvi->condition))
		{
			_current_instr_cycle = cvi->cycle_false;
			_exec_current_instr = false;
		}
		else
			_current_instr_cycle = cvi->cycle_true;
	}
	else
		_current_instr_cycle = _instr->cycle_nb;
}

void	Emulateur::debug_mode()
{
	char c[11];

	print_regs();
	if (!read(0, &c, 2)) // to change
		exit(0);
	// read(0, c, 11);
	// printf(" 0x%02hhX\n", _RAM[REG_LY]);
}


void Emulateur::exec_instr()
{
	if (_halt_status)
		return ;

	if (_current_instr_cycle == 0)
		get_instr();
	_current_instr_cycle--;
	if (_current_instr_cycle == 0)
	{
		// if (regs.PC == 0xC441)
			// printf("mnemonic = \"%s\", nb_param = %d\n", _instr->mnemonic.c_str(), _instr->nb_params);
		// if (regs.PC == 0xC06A)
		// 	printf("PC = %x\n", regs.PC);
		if (!_instr->f)
		{
			printf("Bad instruction 0x%02x\n", _instr->opcode);
			exit(1);
		}
		if (_exec_current_instr)
			_instr->f();
		regs.F &= 0xf0;
		if (_debug)
			debug_mode();
		_exec_current_instr = true;
	}
}

void	Emulateur::cadence()
{
	auto now = std::chrono::system_clock::now();

	if (_cycle * (1.0 / _frequency) * 1000.0 * 1000.0 > (now - _start_time).count())
		SDL_Delay(1);
}

int		Emulateur::main_thread()
{
	if (_debug)
		print_regs();
	_lcd_cycle = 12;
	while (true)
	{
		if (_interrupt_cycle == 0 && _halt_status == false)
			exec_instr();
		update_tima();
		if (_current_instr_cycle == 0)
			interrupt();
		update_lcd();
		_cycle += 4;
		cadence();
		if (_cycle % 256 == 0)
			_RAM[REG_DIV]++;
	}
}

int Emulateur::create_main_thread(void *ptr)
{
	Emulateur *p;

	p = (Emulateur*)ptr;
	return p->main_thread();
}

void	Emulateur::emu_start()
{
	emu_init();
	setvbuf(stdout, NULL, _IONBF, 0);
	_main_thread = SDL_CreateThread(&Emulateur::create_main_thread, "main_thread", (void *)this);
	while (true)
		update();
	SDL_Quit();
	exit(1);
}
