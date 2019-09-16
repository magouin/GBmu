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
	// memcpy(_RAM, _bios, 0x100);
	_frequency = 4194300; // Need to change if it is a CGB
	init_registers();

	_timer = 0; 
	_timer_counter = 0; 
	_timer_status = true;

	_lcd_cycle = 0;
	_interrupt_cycle = 0;

	_test = 0;
	_tima_delay_interrupt = false;

	_isatty = isatty(0);
	_id_break = 0;
}
