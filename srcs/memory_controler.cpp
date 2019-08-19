#include <Emulateur.hpp>

// uint16_t		(*read)();


void			Emulateur::write_div(uint16_t value)
{
	_RAM[0xff04] = 0;
}

void			Emulateur::write_lcdc(uint16_t value)
{
	if ((_RAM[0xff40] & 128) && (!(value & 128)))
		_RAM[0xff44] = 0;
}

void			Emulateur::write_stat(uint16_t value)
{
	_RAM[0xff41] = (_RAM[0xff41] & 3) + (value & 120);
}

void			Emulateur::write_scy(uint16_t value)
{
	if (abs(value - _RAM[0xff42]) > 1)
		throw InvalidWrite((value));
	_RAM[0xff42] = value;
}

void			Emulateur::write_scx(uint16_t value)
{
	if (abs(value - _RAM[0xff43]) > 1)
		throw InvalidWrite((value));
	_RAM[0xff43] = value;
}

void			Emulateur::write_ly(uint16_t value)
{
	_RAM[0xff44] = value;
	if (_RAM[0xff44] == _RAM[0xff45])
		_RAM[0xff41] |= 4;
}

void			Emulateur::write_lyc(uint16_t value)
{
	_RAM[0xff45] = value;
	if (_RAM[0xff45] == _RAM[0xff44])
		_RAM[0xff41] |= 4;
}

void			Emulateur::write_dma(uint16_t value)
{
	uint64_t	t;

	t = _timer_counter * 256 + _timer;
	if (value < 0x80 || value > 0xdf)
		throw InvalidWrite((value));
	_RAM[0xff46] = value;
	while ((_RAM[0xff41] & 3) != 2) ;
	memcpy(_RAM + 0xfe00, _RAM + value * 256, 40 * 4);
	while (_timer_counter * 256 + _timer < t + 160) ;
}

uint8_t			Emulateur::read_p1()
{
	uint8_t value;

	// printf("_RAM[0xff00] = %hhx\n", _RAM[0xff00]);
	value = ~0x30 | _RAM[0xff00];
	// printf("value = %hhx\n", value);
	if (!(_RAM[0xff00] & 0x10))
		value &= (-1u << 4) | _input.p14;
	if (!(_RAM[0xff00] & 0x20))
		value &= (-1u << 4) | _input.p15;
	_RAM[0xff00] = value;
	return (value);
}

bool		Emulateur::is_cpu_regs(void *addr)
{
	if (addr >= &regs && addr < &regs + sizeof(regs))
		return (true);
	return (false);
}

uint16_t	Emulateur::mem_read(void *addr, int8_t size)
{
	uint16_t ram_addr;

	if (is_cpu_regs(addr))
		;
	else if (addr >= _RAM && addr <= _RAM + 0xffff)
	{
		ram_addr = (uint16_t)((uint8_t *)addr - _RAM);
		// if ((ram_addr >= 0xe000 && ram_addr < 0xfe00))
			// || (ram_addr >= 0xfea0 && ram_addr < 0xff00)
			// || (ram_addr >= 0xff00 && ram_addr < 0xff80 && !(_ram_regs[ram_addr - 0xff00].right & RD)))
		//	throw InvalidRead((ram_addr));
		if (ram_addr >= 0xff00 && ram_addr < 0xff80 && _ram_regs[ram_addr - 0xff00].read)
			return ((this->*_ram_regs[ram_addr - 0xff00].read)());
	}
	else
		throw InvalidRead(((uint64_t)addr));
	if (size == 2)
		return (*(uint16_t *)addr);
	else
		return (*(uint8_t *)addr);
}

void		Emulateur::mem_write_signed(void *addr, int16_t value, int8_t size)
{
	uint16_t ram_addr;

	if (is_cpu_regs(addr))
		;
	else if (addr >= _RAM && addr <= _RAM + 0xffff)
	{
		ram_addr = (uint16_t)((uint8_t *)addr - _RAM);
		if ((ram_addr >= 0x0000 && ram_addr < 0x0150))
		//	|| (ram_addr >= 0xe000 && ram_addr < 0xfe00))
			// || (ram_addr >= 0xfea0 && ram_addr < 0xff00)
			// || (ram_addr >= 0xff00 && ram_addr < 0xff80 && !(_ram_regs[ram_addr - 0xff00].right & WR)))
			throw InvalidWrite((ram_addr));
		if (ram_addr >= 0xff00 && ram_addr < 0xff80 && _ram_regs[ram_addr - 0xff00].write)
		{
			printf("Signed non géré sur un registre de la ram dans mem_write_signed\n");
			throw InvalidWrite((ram_addr));
			return ;
		}
	}
	else
		throw InvalidWrite(((uint64_t)addr));
	if (size == 2)
		*(uint16_t *)addr = value;
	else
		*(uint8_t *)addr = (int8_t)value;
}

void		Emulateur::mem_write(void *addr, uint16_t value, int8_t size)
{
	uint16_t ram_addr;

	if (is_cpu_regs(addr))
		;
	else if (addr >= _RAM && addr <= _RAM + 0xffff)
	{
		ram_addr = (uint16_t)((uint8_t *)addr - _RAM);
		if ((ram_addr >= 0x0000 && ram_addr < 0x0150))
		//	|| (ram_addr >= 0xe000 && ram_addr < 0xfe00))
			// || (ram_addr >= 0xfea0 && ram_addr < 0xff00)
			// || (ram_addr >= 0xff00 && ram_addr < 0xff80 && !(_ram_regs[ram_addr - 0xff00].right & WR)))
			throw InvalidWrite((ram_addr));
		if (ram_addr >= 0xff00 && ram_addr < 0xff80 && _ram_regs[ram_addr - 0xff00].write)
		{
			(this->*_ram_regs[ram_addr - 0xff00].write)(value);
			return ;
		}
	}
	else
		throw InvalidWrite(((uint64_t)addr));
	if (size == 2)
		*(uint16_t *)addr = value;
	else
		*(uint8_t *)addr = (uint8_t)value;
}
