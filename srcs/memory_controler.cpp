#include <Emulateur.hpp>

// uint16_t		(*read)();
void			Emulateur::write_stat(uint16_t value)
{
	_RAM[0xFF41] = (_RAM[0xFF41] & 3) + (value & 120);
}

void			Emulateur::write_div(uint16_t value)
{
	_RAM[0xFF04] = 0;
}

void			Emulateur::write_scy(uint16_t value)
{
	if (abs(value - _RAM[0xFF42]) > 1)
		throw InvalidWrite();
	_RAM[0xFF42] = value;
}

void			Emulateur::write_scx(uint16_t value)
{
	if (abs(value - _RAM[0xFF43]) > 1)
		throw InvalidWrite();
	_RAM[0xFF43] = value;
}

uint16_t	Emulateur::mem_read(void *addr, int8_t size)
{
	uint16_t ram_addr;

	if (is_cpu_regs(addr))
		;
	else if (addr >= _RAM && addr <= _RAM + 0xffff)
	{
		ram_addr = (uint16_t)((uint8_t *)addr - _RAM);
		if ((ram_addr >= 0xe000 && ram_addr < 0xfe00)
			|| (ram_addr >= 0xfea0 && ram_addr < 0xff00)
			|| (ram_addr >= 0xff00 && ram_addr < 0xff80 && !(_ram_regs[ram_addr - 0xff00].right & RD)))
			throw InvalidRead();
	}
	else
		throw InvalidRead();
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
		if ((ram_addr >= 0x0100 && ram_addr < 0x8000)
			|| (ram_addr >= 0xe000 && ram_addr < 0xfe00)
			|| (ram_addr >= 0xfea0 && ram_addr < 0xff00)
			|| (ram_addr >= 0xff00 && ram_addr < 0xff80 && !(_ram_regs[ram_addr - 0xff00].right & WR)))
			throw InvalidWrite();
	}
	else
		throw InvalidWrite();
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
		if ((ram_addr >= 0x0100 && ram_addr < 0x8000)
			|| (ram_addr >= 0xe000 && ram_addr < 0xfe00)
			|| (ram_addr >= 0xfea0 && ram_addr < 0xff00)
			|| (ram_addr >= 0xff00 && ram_addr < 0xff80 && !(_ram_regs[ram_addr - 0xff00].right & WR)))
			throw InvalidWrite();
	}
	else
		throw InvalidWrite();
	if (size == 2)
		*(uint16_t *)addr = value;
	else
		*(uint8_t *)addr = (uint8_t)value;
}