#include <Emulateur.hpp>

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
	regs.PC = 0x0100;
	// regs.PC = 0x0000;
	regs.IME = false;

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

Memory_controller 	&Emulateur::get_memory_controller() {
	if (_cartridge.type == CT_ROM)
		return (*new Memory_controller_MBC1(*this, _header.get_ram_size(), _debug));
	else if (_cartridge.type == CT_MBC1)
		return (*new Memory_controller_MBC1(*this, _header.get_ram_size(), _debug));
	else if (_cartridge.type == CT_MBC2)
		return (*new Memory_controller_MBC2(*this, MBC2_RAM_SIZE, _debug));
	else if (_cartridge.type == CT_MBC3)
		return (*new Memory_controller_MBC3(*this, _header.get_ram_size(), _debug));
	else if (_cartridge.type == CT_MBC5)
		return (*new Memory_controller_MBC5(*this, _header.get_ram_size(), _debug));
	else {
		printf("Cartridge [%s] not supported", _cartridge.to_str.c_str());
		exit(EXIT_FAILURE);
	}
}

void Emulateur::emu_init()
{
	_cycle = 0;
	regs.IME = true;
	memset(_pixels_map, (uint8_t)0xff, sizeof(_pixels_map));
	_input.p14 = 0xff;
	_input.p15 = 0xff;
	_halt_status = false;
	_stop_status = false;
	memcpy(_RAM, _ROM.c_str(), 0x8000);
	// memcpy(_RAM, _bios, 0x100);
	_frequency = 0x400000; // Need to change if it is a CGB
	init_registers();

	_lcd_cycle = 0;
	_interrupt_cycle = 0;
	_current_instr_cycle = 0;

	_test = 0;
	_tima_delay_interrupt = false;

	#ifdef __GNUC__
		_is_a_tty = isatty(0);
	#else
		_is_a_tty = _isatty(0);
	#endif
	_id_break = 0;
	_reset = false;
	_trace = 0;
}

