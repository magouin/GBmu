#include <Emulateur.hpp>

void			Memory_controller::write_div(uint8_t value)
{
	_emu._RAM[REG_DIV] = 0;
}

void			Memory_controller::write_lcdc(uint8_t value)
{
	if (!(_emu._RAM[REG_LCDC] & (1 << 5)) && (value & (1 << 5)))
		printf("Windowing on flag activated : %x %x\n", _emu._RAM[REG_WX], _emu._RAM[REG_WY]);
	if ((_emu._RAM[REG_LCDC] & 0x80) && (!(value & 0x80)))
		_emu._RAM[REG_LY] = 0;
	_emu._RAM[REG_LCDC] = value;
}

void			Memory_controller::write_stat(uint8_t value)
{
	_emu._RAM[REG_STAT] = (_emu._RAM[REG_STAT] & 3) | (value & 120);
}

void			Memory_controller::write_scy(uint8_t value)
{
	_emu._RAM[REG_SCY] = value;
}

void			Memory_controller::write_scx(uint8_t value)
{
	_emu._RAM[REG_SCX] = value;
}

void			Memory_controller::write_ly(uint8_t value)
{
	_emu._RAM[REG_LY] = value;
	if (_emu._RAM[REG_LY] == _emu._RAM[REG_LYC])
	{
		_emu._RAM[REG_STAT] |= 4;
		if (_emu._RAM[REG_STAT] & (1 << 6))
				_emu._RAM[REG_IF] |= (1 << 1);
	}
	else
		_emu._RAM[REG_STAT] &= ~4;
	// printf("Writing value %x in ly\n", value);
}

void			Memory_controller::write_lyc(uint8_t value)
{
	_emu._RAM[REG_LYC] = value;
	if (_emu._RAM[REG_LY] == _emu._RAM[REG_LYC])
	{
		_emu._RAM[REG_STAT] |= 4;
		if (_emu._RAM[REG_STAT] & (1 << 6))
				_emu._RAM[REG_IF] |= (1 << 1);
	}
	else
		_emu._RAM[REG_STAT] &= ~4;
}

void			Memory_controller::write_dma(uint8_t value)
{
	// uint64_t	t;

	// t = _timer_counter * 256 + _timer;

	if (value < 0x80 || value > 0xdf)
	{
		printf("SHOULDNT HAPPEN 2 [%hhx]\n", value);
		// throw InvalidWrite((value));
	}
	_emu._RAM[0xff46] = value;
	// if ((_emu._RAM[REG_STAT] & 3) != 2)
	// 	return ;
	if (value < 0xa0 || value >= 0xc0)
		memcpy(_emu._RAM + 0xfe00, _emu._RAM + value * 256, 40 * 4);
	else
		memcpy(_emu._RAM + 0xfe00, _emu._ram_bank + (value - 0xa0) * 256, 40 * 4);
}

void			Memory_controller::write_tac(uint8_t value)
{
	_emu._RAM[REG_TAC] = value;
}

void			Memory_controller::read_p1()
{
	uint8_t value;

	value = _emu._RAM[REG_P1] | 0xf;
	if (!(value & 0x10))
		value &= 0xf0 | _emu._input.p14;
	if (!(value & 0x20))
		value &= 0xf0 | _emu._input.p15;
	_emu._RAM[REG_P1] = value;
}

void		*Memory_controller::cpu_regs(void *addr)
{
	if (addr >= &_emu.regs && addr < &_emu.regs + sizeof(_emu.regs))
		return (addr);
	return (NULL);
}

void		*Memory_controller::read_gb_regs(uint8_t *addr)
{
	if (addr < _emu._RAM + 0xff00 || addr > _emu._RAM + 0xff7f)
		return (NULL);
	if (_ram_regs[addr - 0xff00 - _emu._RAM].read)
		(this->*_ram_regs[addr - 0xff00 - _emu._RAM].read)();
	else return (NULL);
	return (addr);
}

void		*Memory_controller::write_gb_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr < _emu._RAM + 0xff00 || addr > _emu._RAM + 0xff7f)
		return (NULL);
	if (_ram_regs[addr - 0xff00 - _emu._RAM].write)
		(this->*_ram_regs[addr - 0xff00 - _emu._RAM].write)(value);
	else return (NULL);
	return (addr);
}

void		*Memory_controller::gb_mem(void *addr)
{
	if (addr < _emu._RAM || addr > _emu._RAM + 0xffff)
		return (NULL);
	return (addr);
}

uint16_t	Memory_controller::mem_read(void *addr, int8_t size)
{
	void	*read_addr = NULL;

	_emu.check_watchpoint((uint8_t *)addr, RD, size);
	if ((read_addr = read_ROM_RAM_regs((uint8_t*)addr))) ;
	else if ((read_addr = cpu_regs(addr))) ;
	else if ((read_addr = read_gb_regs((uint8_t*)addr))) ;
	else if ((read_addr = gb_mem(addr))) ;
	else {
		printf("GBmu: warning: Invalid read at 0x%hx", (uint16_t)((uint8_t *)addr - _emu._RAM));
		return (0);
	}
	if (size == 2)
		return (*(uint16_t *)read_addr);
	else
		return (*(uint8_t *)read_addr);
}

void		Memory_controller::mem_write(void *addr, uint16_t value, int8_t size)
{
	void	*write_addr;

	_emu.check_watchpoint((uint8_t *)addr, WR, size);
	if ((write_addr = cpu_regs(addr))) ;
	else if (write_ROM_regs((uint8_t*)addr, value, size))
		return ;
	else if (write_RAM_regs((uint8_t*)addr, value, size))
		return ;
	else if (write_gb_regs((uint8_t *)addr, value, size))
		return ;
	else if ((write_addr = gb_mem(addr))) ;
	else {
		printf("GBmu: warning: Invalid write at 0x%hx", (uint16_t)((uint8_t *)addr - _emu._RAM));
		return ;
	} 

	if (size == 2)
		*(uint16_t *)addr = value;
	else
		*(uint8_t *)addr = (uint8_t)value;
}

void	Memory_controller::save()
{
	ofstream fs;

	fs.open(_emu._save_name, ios::out | ios::binary);
	if (fs.is_open()) {
		fs.write((char *)_emu._external_ram, _ram_size);
		fs.close();
	}
	if (_ram_size > 0)
		delete _emu._external_ram;
}

void	Memory_controller::init(size_t ram_size) {
	_ram_size = ram_size;
	_emu._external_ram = (_ram_size > 0) ? new uint8_t[_ram_size] : _emu._RAM + 0xa000;

	std::ifstream fs;
	fs.open (_emu._save_name, std::fstream::in | ios::binary);
	if (fs.is_open())
	{
		fs.read((char *)_emu._external_ram, _ram_size);
		fs.close();
	}
}


Memory_controller::Memory_controller(Emulateur &emu, size_t ram_size): _emu(emu), _ram_regs({RAM_REGS})
{
}

Memory_controller::~Memory_controller() {
}

Memory_controller &	Memory_controller::operator=(const Memory_controller & cp) {
	(void)cp;
	return (*this);
}