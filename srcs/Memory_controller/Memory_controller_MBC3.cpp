#include <Emulateur.hpp>

void		*Memory_controller_MBC3::read_ROM_RAM_regs(uint8_t *addr)
{
	if (addr < _emu._RAM)
		return (NULL);
	if (addr - _emu._RAM < 0x4000)
		return (addr);
	else if (addr - _emu._RAM  < 0x8000)
		return (void*)(rom_bank + (addr - _emu._RAM - 0x4000));
	else if (addr - _emu._RAM >= 0xa000 && addr - _emu._RAM  < 0xc000)
	{
		if (_RAM_ENABLE)
			return (void*)(ram_bank + (addr - _emu._RAM - 0xa000));
		return (NULL);
	}
	else return (NULL);
}

bool		Memory_controller_MBC3::write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	uint8_t id;

	if (addr < _emu._RAM)
		return (false);

	if (addr - _emu._RAM < 0x2000)
		_RAM_ENABLE = ((value & 0xf) == 0xa ? true : false);
	else if (addr - _emu._RAM < 0x4000)
	{
		if (value < 1 || value > 0x1f) ;
			// printf("ERROR: This value should be between 1 and 1f\n");
		else
			_ROM_BANK = value;
	}
	else if (addr - _emu._RAM < 0x6000)
	{
		if (value > 3)
			printf("ERROR: This value should be between 0 and 3\n");
		else
			_ROM_RAM_BANK = value;
	}
	else if (addr - _emu._RAM  < 0x8000)
	{
		if (value > 1)
			printf("ERROR: This value should be between 0 and 1\n");
		else
			_ROM_RAM_SELECT = value;
	}
	else
		return (false);

	if (_ROM_RAM_SELECT == 0)
	{
		id = _ROM_BANK + (_ROM_RAM_BANK << 5);
		rom_bank = (const uint8_t*)(_emu._ROM.c_str() + 0x4000 * id);
		ram_bank = external_ram;
	}
	else if (_ROM_RAM_SELECT == 1)
	{
		id = _ROM_BANK;
		rom_bank = (const uint8_t*)(_emu._ROM.c_str() + 0x4000 * id);
		ram_bank = external_ram + _ROM_RAM_BANK * 0x2000;
	}
	return (true);
}

bool		Memory_controller_MBC3::write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size)
{
	if (addr - _emu._RAM  >= 0xA000 && addr - _emu._RAM  < 0xC000)
	{
		if (size == 2)
			*(uint16_t *)(ram_bank + (addr - _emu._RAM - 0xA000)) = value;
		else
			*(uint8_t *)(ram_bank + (addr - _emu._RAM - 0xA000)) = (uint8_t)value;
		return (true);
	}
	return (false);
}

Memory_controller_MBC3::Memory_controller_MBC3(Emulateur &emu, size_t ram_size): Memory_controller(emu, ram_size)
{
	init(ram_size);
	_ROM_RAM_BANK = 0;
	_ROM_RAM_SELECT = 0;
}