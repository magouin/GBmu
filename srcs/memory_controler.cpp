#include <Emulateur.hpp>

void			Emulateur::write_div(uint8_t value)
{
	_RAM[REG_DIV] = 0;
}

void			Emulateur::write_lcdc(uint8_t value)
{
	if ((_RAM[REG_LCDC] & 0x80) && (!(value & 0x80)))
		_RAM[REG_LY] = 0;
	_RAM[REG_LCDC] = value;}

void			Emulateur::write_stat(uint8_t value)
{
	_RAM[REG_STAT] = (_RAM[REG_STAT] & 3) | (value & 120);
}

void			Emulateur::write_scy(uint8_t value)
{
	_RAM[REG_SCY] = value;
}

void			Emulateur::write_scx(uint8_t value)
{
	_RAM[REG_SCX] = value;
}

void			Emulateur::write_ly(uint8_t value)
{
	_RAM[REG_LY] = value;
	if (_RAM[REG_LY] == _RAM[REG_LYC])
	{
		_RAM[REG_STAT] |= 4;
		if (_RAM[REG_STAT] & (1 << 6))
				_RAM[REG_IF] |= (1 << 1);
	}
	else
		_RAM[REG_STAT] &= ~4;
	// printf("Writing value %x in ly\n", value);
}

void			Emulateur::write_lyc(uint8_t value)
{
	_RAM[REG_LYC] = value;
	if (_RAM[REG_LY] == _RAM[REG_LYC])
	{
		_RAM[REG_STAT] |= 4;
		if (_RAM[REG_STAT] & (1 << 6))
				_RAM[REG_IF] |= (1 << 1);
	}
	else
		_RAM[REG_STAT] &= ~4;
}

void			Emulateur::write_dma(uint8_t value)
{
	// uint64_t	t;

	// t = _timer_counter * 256 + _timer;

	if (value < 0x80 || value > 0xdf)
	{
		printf("SHOULDNT HAPPEN 2 [%hhx]\n", value);
		throw InvalidWrite((value));
	}
	_RAM[0xff46] = value;
	// if ((_RAM[REG_STAT] & 3) != 2)
	// 	return ;
	memcpy(_RAM + 0xfe00, _RAM + value * 256, 40 * 4);
}

void			Emulateur::write_tac(uint8_t value)
{
	_RAM[REG_TAC] = value;
}

void			Emulateur::read_p1()
{
	uint8_t value;

	value = _RAM[REG_P1] | 0xf;
	if (!(value & 0x10))
		value &= 0xf0 | _input.p14;
	if (!(value & 0x20))
		value &= 0xf0 | _input.p15;
	_RAM[REG_P1] = value;
}

void		*Emulateur::read_ROM_RAM_regs(uint8_t *addr)
{
	if (addr < _RAM)
		return (NULL);
	if (addr - _RAM < 0x4000)
		return (addr);
	else if (addr - _RAM  < 0x8000)
		return (void*)(_rom_bank + (addr - _RAM - 0x4000));
	else if (addr - _RAM >= 0xa000 && addr - _RAM  < 0xc000)
	{
		if (regs.RAM_ENABLE)
			return (void*)(_ram_bank + (addr - _RAM - 0xa000));
		return (NULL);
	}
	else return (NULL);
}

bool		Emulateur::write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	uint8_t id;

	if (addr < _RAM)
		return (false);

	if (addr - _RAM < 0x2000)
		regs.RAM_ENABLE = ((value & 0xf) == 0xa ? true : false);
	else if (addr - _RAM < 0x4000)
	{
		if (value < 1 || value > 0x1f)
			printf("ERROR: This value should be between 1 and 1f\n");
		else
			regs.ROM_BANK = value;
	}
	else if (addr - _RAM < 0x6000)
	{
		if (value > 3)
			printf("ERROR: This value should be between 0 and 3\n");
		else
			regs.ROM_RAM_BANK = value;
	}
	else if (addr - _RAM  < 0x8000)
	{
		if (value > 1)
			printf("ERROR: This value should be between 0 and 1\n");
		else
			regs.ROM_RAM_SELECT = value;
	}
	else
		return (false);

	if (regs.ROM_RAM_SELECT == 0)
	{
		id = regs.ROM_BANK + (regs.ROM_RAM_BANK << 5);
		_rom_bank = (const uint8_t*)(_ROM.c_str() + 0x4000 * id);
		_ram_bank = _external_ram;
	}
	else if (regs.ROM_RAM_SELECT == 1)
	{
		id = regs.ROM_BANK;
		_rom_bank = (const uint8_t*)(_ROM.c_str() + 0x4000 * id);
		_ram_bank = _external_ram + regs.ROM_RAM_BANK * 0x2000;
	}
	return (true);
}

bool		Emulateur::write_RAM_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr - _RAM  >= 0xA000 && addr - _RAM  < 0xC000)
	{
		if (size == 2)
			*(uint16_t *)(_ram_bank + (addr - _RAM - 0xA000)) = value;
		else
			*(uint8_t *)(_ram_bank + (addr - _RAM - 0xA000)) = (uint8_t)value;
		return (true);
	}
	return (false);
}

void		*Emulateur::cpu_regs(void *addr)
{
	if (addr >= &regs && addr < &regs + sizeof(regs))
		return (addr);
	return (NULL);
}

void		*Emulateur::read_gb_regs(uint8_t *addr)
{
	if (addr < _RAM + 0xff00 || addr > _RAM + 0xff7f)
		return (NULL);
	if (_ram_regs[addr - 0xff00 - _RAM].read)
		(this->*_ram_regs[addr - 0xff00 - _RAM].read)();
	else return (NULL);
	return (addr);
}

void		*Emulateur::write_gb_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr < _RAM + 0xff00 || addr > _RAM + 0xff7f)
		return (NULL);
	if (_ram_regs[addr - 0xff00 - _RAM].write)
		(this->*_ram_regs[addr - 0xff00 - _RAM].write)(value);
	else return (NULL);
	return (addr);
}

void		*Emulateur::gb_mem(void *addr)
{
	if (addr < _RAM || addr > _RAM + 0xffff)
		return (NULL);
	return (addr);
}

uint16_t	Emulateur::mem_read(void *addr, int8_t size)
{
	void	*read_addr;

	if ((read_addr = read_ROM_RAM_regs((uint8_t*)addr))) ;
	else if ((read_addr = cpu_regs(addr))) ;
	else if ((read_addr = read_gb_regs((uint8_t*)addr))) ;
	else if ((read_addr = gb_mem(addr))) ;
	else throw InvalidRead((uint8_t *)addr - _RAM);

	if (size == 2)
		return (*(uint16_t *)read_addr);
	else
		return (*(uint8_t *)read_addr);
}

void		Emulateur::mem_write(void *addr, uint16_t value, int8_t size)
{
	void	*write_addr;

	if ((write_addr = cpu_regs(addr))) ;
	else if (write_ROM_regs((uint8_t*)addr, value, size))
		return ;
	else if (write_RAM_regs((uint8_t*)addr, value, size))
		return ;
	else if (write_gb_regs((uint8_t *)addr, value, size))
		return ;
	else if ((write_addr = gb_mem(addr))) ;
	else throw InvalidWrite((uint8_t *)addr - _RAM);

	if (size == 2)
		*(uint16_t *)addr = value;
	else
		*(uint8_t *)addr = (uint8_t)value;
}
