#include <Emulateur.hpp>
#include <debugger.hpp>
#include <opcode.hpp>
#include <op203.hpp>
#include <dmg_bios.hpp>

const uint8_t Emulateur::_bios[] = DMG_BIOS;

Emulateur::Emulateur(): gb_regs({INIT_GB_REGS}), _cartridge(_header.get_cartridge_type()), _MBC(get_memory_controller())
{
}

Emulateur::Emulateur(std::string file, std::string rom, bool debug): ROM(rom), save_name(file.substr(0, file.find_last_of('.')) + ".sav"), _op203({OP203}), _opcode({OPCODE}), _cv_instrs({CYCLE_VARIABLE_OPCODE}), _deb_cmd({DEB_CMD}), _header(rom, &cgb.on), _file_name(file), _step_by_step(debug), gb_regs({INIT_GB_REGS}), _debug(debug), _cartridge(_header.get_cartridge_type()), _MBC(get_memory_controller())
{
	sdl_init();
}

Emulateur::Emulateur(const Emulateur & cp): gb_regs({INIT_GB_REGS}), _cartridge(_header.get_cartridge_type()), _MBC(cp._MBC)
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

void	Emulateur::interrupt_func(short addr, uint8_t iflag)
{
	_halt_status = false;
	if (!regs.IME)
		return ;
	if (_interrupt_cycle == 0)
		_interrupt_cycle = 5;
	_interrupt_cycle--;
	if (_interrupt_cycle == 0)
	{
		_current_instr_cycle = 0;
		regs.IME = false;
		*(uint8_t *)&gb_regs.iflag = *(uint8_t *)&gb_regs.iflag & ~iflag;
		regs.SP -= 2;
		_MBC.mem_write(RAM + regs.SP, regs.PC, 2);
		regs.PC = addr;
		if (_step_by_step || check_breakpoint()) debug_mode();
		if (_trace) {_trace--; print_trace();}
	}
}

void	Emulateur::interrupt(void)
{
	if(gb_regs.iflag.vblank && gb_regs.ie.vblank) // V-Blank
		interrupt_func(0x0040, 1);
	else if(gb_regs.iflag.lcdc && gb_regs.ie.lcdc) // LCD STAT
		interrupt_func(0x0048, 2);
	else if(gb_regs.iflag.timer && gb_regs.ie.timer) // Timer
		interrupt_func(0x0050, 4);
	else if(gb_regs.iflag.serial && gb_regs.ie.serial) // Serial
		interrupt_func(0x0058, 8);
	else if(gb_regs.iflag.io && gb_regs.ie.io) // Joypad
		interrupt_func(0x0060, 16);
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
	const uint8_t			num_to_byte[4] = {8, 2, 4, 6};
	static uint64_t			nb_tick = 0;

	if (_tima_delay_interrupt)
	{
		_tima_delay_interrupt = false;
		gb_regs.tima = RAM[0xFF06];
		gb_regs.iflag.timer = true;
		return ;
	}
	if (nb_tick == 0)
		nb_tick = (1l << (num_to_byte[gb_regs.tac.clock_select]));
	nb_tick--;
	if (nb_tick == 0)
	{
		if (gb_regs.tima == 0xff)
			_tima_delay_interrupt = true;
		gb_regs.tima++;
	}
}

void	Emulateur::get_instr()
{
	const struct s_cv_instr	*cvi;

	_instr = &_opcode[_MBC.mem_read(RAM + regs.PC, 1)];
	if (_instr->opcode == 203)
		_instr = &_op203[_MBC.mem_read(RAM + regs.PC + 1, 1)];
	if (_debug && (_step_by_step || check_breakpoint())) debug_mode();
	if (_trace) {_trace--; print_trace();}
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

void Emulateur::exec_instr()
{
	if (_halt_status)
		return ;

	if (_current_instr_cycle == 0)
		get_instr();
	_current_instr_cycle--;
	if (_current_instr_cycle == 0)
	{
		if (!_instr->f)
		{
			printf("Bad instruction 0x%02x\n", _instr->opcode);
			exit(1);
		}
		if (_exec_current_instr)
			_instr->f();
		regs.F &= 0xf0;
		_exec_current_instr = true;
	}
}

int		Emulateur::main_thread()
{
	while (true)
	{
		if (_reset)
			emu_init();
		if (gb_regs.tac.on)
			update_tima();
		if (_interrupt_cycle == 0 && _halt_status == false)
			exec_instr();
		if (_current_instr_cycle == 0)
			interrupt();
		update_lcd();
		_cycle = (_cycle + 4) % 70224;
		if (_cycle % 256 == 0)
			gb_regs.div++;
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
	setvbuf(stdout, NULL, _IONBF, 0);
	emu_init();
	_main_thread = SDL_CreateThread(&Emulateur::create_main_thread, "main_thread", (void *)this);
	while (true)
		update();
	SDL_Quit();
	exit(1);
}
