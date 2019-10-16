#include <Emulateur.hpp>

void		*Memory_controller_MBC5::read_ROM_RAM_regs(uint8_t *addr)
{
	if (addr < _emu.RAM)
		return (NULL);
	if (addr - _emu.RAM < 0x4000)
		return (addr);
	else if (addr - _emu.RAM  < 0x8000)
		return (void*)(rom_bank + (addr - _emu.RAM - 0x4000));
	else if (addr - _emu.RAM >= 0xa000 && addr - _emu.RAM  < 0xc000)
	{
		if (_ram_ext_work_enable)
			return (void*)(ram_ext_work_bank + (addr - _emu.RAM - 0xa000));
		return (NULL);
	}
	else return (NULL);
}

bool		Memory_controller_MBC5::write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr < _emu.RAM)
		return (false);

	if (addr - _emu.RAM < 0x2000)
		_ram_ext_work_enable = ((value & 0xf) == 0xa ? true : false);
	else if (addr - _emu.RAM < 0x3000)
	{
		_rom_bank_selected = value;
	}
	else if (addr - _emu.RAM < 0x4000)
	{
		_rom_bank_selected = value & 1;
	}
	else if (addr - _emu.RAM < 0x6000)
	{
		_ram_ext_work_bank_to_select = value & 0xf;
	}
	else
		return (false);
	rom_bank = (const uint8_t*)(_emu.ROM.c_str() + 0x4000 * _rom_bank_selected);
	ram_ext_work_bank = ram_ext_work_orig_ptr + _ram_ext_work_bank_to_select * 0x2000;
	return (true);
}

bool		Memory_controller_MBC5::write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size)
{
	if (addr - _emu.RAM  >= 0xA000 && addr - _emu.RAM  < 0xC000)
	{
		if (size == 2)
			*(uint16_t *)(ram_ext_work_bank + (addr - _emu.RAM - 0xA000)) = value;
		else
			*(uint8_t *)(ram_ext_work_bank + (addr - _emu.RAM - 0xA000)) = (uint8_t)value;
		return (true);
	}
	return (false);
}

Memory_controller_MBC5::Memory_controller_MBC5(Emulateur &emu, size_t ram_size, bool debug): Memory_controller(emu, ram_size, debug)
{
	init(ram_size);
}
