#include <Emulateur.hpp>

uint8_t		*Memory_controller_MBC1::read_ROM_RAM_regs(uint8_t *addr)
{
	if (addr < _emu.RAM)
		return (NULL);
	if (addr - _emu.RAM < 0x4000)
		return (addr);
	else if (addr - _emu.RAM  < 0x8000)
		return const_cast<uint8_t *>(rom_bank + (addr - _emu.RAM - 0x4000));
	else if (addr - _emu.RAM >= 0xa000 && addr - _emu.RAM  < 0xc000)
		if (_ram_ext_work_enable)
			return (ram_ext_work_bank + (addr - _emu.RAM - 0xa000));
	return (NULL);
}

bool		Memory_controller_MBC1::write_ROM_regs(uint8_t *addr, uint8_t value)
{
	uint8_t id;

	if (addr < _emu.RAM)
		return (false);

	if (addr - _emu.RAM < 0x2000)
		_ram_ext_work_enable = ((value & 0xf) == 0xa ? true : false);
	else if (addr - _emu.RAM < 0x4000)
	{
		if (!value)
			value = 1;
		_rom_bank_selected = value & 0x1f;
	}
	else if (addr - _emu.RAM < 0x6000)
	{
		_rom_ram_bank = value & 3;
	}
	else if (addr - _emu.RAM  < 0x8000)
	{
		_rom_ram_select = value & 1;
	}
	else
		return (false);

	if (_rom_ram_select == 0)
	{
		id = _rom_bank_selected + (_rom_ram_bank << 5);
		rom_bank = (_emu.ROM + 0x4000 * id);
		ram_ext_work_bank = ram_ext_work_orig_ptr;
	}
	else if (_rom_ram_select == 1)
	{
		id = _rom_bank_selected;
		rom_bank = (_emu.ROM + 0x4000 * id);
		ram_ext_work_bank = ram_ext_work_orig_ptr + _rom_ram_bank * 0x2000;
	}
	return (true);
}

bool		Memory_controller_MBC1::write_RAM_regs(uint8_t *addr, uint8_t value)
{
	if (addr - _emu.RAM  >= 0xA000 && addr - _emu.RAM  < 0xC000)
	{
		*(uint8_t *)(ram_ext_work_bank + (addr - _emu.RAM - 0xA000)) = (uint8_t)value;
		return (true);
	}
	return (false);
}

Memory_controller_MBC1::Memory_controller_MBC1(Emulateur &emu, size_t ram_size, bool debug): Memory_controller(emu, ram_size, debug)
{
	init(ram_size);
	_rom_ram_bank = 0;
	_rom_ram_select = 0;
}
