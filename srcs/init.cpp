#include <Emulateur.hpp>

#ifdef __GNUC__
# define ISATTY isatty
#endif

#ifdef _MSC_VER
# include <io.h>
# define ISATTY _isatty
#endif

void	Emulateur::init_registers(void)
{
	if (cgb.on)
	{
		regs.BC = 0x0000;
		regs.DE = 0x0008;
		regs.HL = 0x007c;
		regs.AF = 0x1180;
	}
	else
	{
		regs.BC = 0x0013;
		regs.DE = 0x00d8;
		regs.HL = 0x014d;
		regs.AF = 0x01B0;
	}

	// regs.AF = 0x1180; // cpu_instr
	// regs.BC = 0x0000;
	// regs.DE = 0x0008;
	// regs.HL = 0x007c;
	regs.SP = 0xfffe;
	regs.PC = 0x0000;
	// regs.PC = 0x0000;
	regs.IME = false;

	gb_regs.div = 0x00; // TIMA
	RAM[0xff40] = 0x91; // LCDC
	RAM[REG_SCY] = 0x00; // SCY
	RAM[REG_SCX] = 0x00; // SCX

	RAM[REG_LY] = 0x00; // LY

	RAM[REG_LYC] = 0x00; // LYC
	RAM[0xff47] = 0xfc; // BGP
	RAM[0xff48] = 0xff; // OBPO
	RAM[0xff49] = 0xff; // OBP1
	RAM[REG_WY] = 0x00; // WY
	RAM[REG_WX] = 0x00; // WX
	RAM[REG_KEY1] = 0x7e;
	RAM[REG_SVBK] = 0xf9;
	RAM[REG_HDMA5] = 0x0;
	RAM[0xff0f] = 0xE0;
	gb_regs.tac.on = 0;
	gb_regs.tac.clock_select = 0;
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
	// printf("cgb on -> %s (0x%hhx)\n", cgb.on ? "true" : "false", _header.cgb_supp_code);
	cgb.bios = true;
	if (cgb.on) {
		cgb.mode_double_speed = false;
	}
	_screen_prio = vector<bool>(GB_WINDOW_SIZE_X * GB_WINDOW_SIZE_Y, false);
	_bg_prio = vector<bool>(GB_WINDOW_SIZE_X * GB_WINDOW_SIZE_Y, false);
	_cycle = 0;
	regs.IME = true;
	memset(_pixels_map, (uint8_t)0xff, sizeof(_pixels_map));
	input.p14 = 0xff;
	input.p15 = 0xff;
	_halt_status = false;
	_stop_status = false;
	memset(RAM, 0xff, 0x10000);
	memset(RAM + 0xff00, 0x00, 0x80);
	if (cgb.on) {
		memcpy(RAM, CGB_BIOS, 0x900);
		// memcpy(RAM + 0x100, CGB_BIOS, 0x900);
	}
	else
	{
		// memcpy(RAM + 0x100, DMG_BIOS, 0x100);
		memcpy(RAM, DMG_BIOS, 0x100);
	}
	memcpy(RAM + 0x100, ROM + 0x100, 0x100);
	for (int x = 0; x < 0x2000; x++)
		RAM[0xc000 + x] = (x & 8) ^ ((x >> 8) & 8) ? 0x00 : 0xff;
	// memset(RAM + 0xC000, 0x00, 0x2000);
	// memcpy(RAM, _dmg_bios, 0x100);
	_frequency = 0x400000; // Need to change if it is a CGB
	init_registers();
	gb_regs.vbk.bank = 0;
	lcd_cycle = 0;
	_interrupt_cycle = 0;

	_test = 0;
	_tima_delay_interrupt = false;

	_is_a_tty = ISATTY(0);
	_id_break = 0;
	_reset = false;
	_trace = 0;
	_transition = 0;
}

