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
	if (_emu.cgb.on) {
		_emu._RAM[0xff46] = value;
		if (value >= 0x80 && value < 0xa0)
			memcpy(_emu._RAM + 0xfe00, (_video_ram_bank ? (_video_external_ram + (value - 0x80) * 256) : (_emu._RAM + value * 256)), 40 * 4);
		else if (value >= 0xa0 && value < 0xc0)
			memcpy(_emu._RAM + 0xfe00, ram_bank + (value - 0xa0) * 256, 40 * 4);
		else if (_working_ram_bank > 1 && value >= 0xd0 && value < 0xe0)
			memcpy(_emu._RAM + 0xfe00, _working_ram + (_working_ram_bank - 2) * 0x1000 + (value - 0xd0) * 256, 40 * 4);
		else
			memcpy(_emu._RAM + 0xfe00, _emu._RAM + value * 256, 40 * 4);
	}
	else {
		if (value < 0x80 || value > 0xdf)
			return ;
		_emu._RAM[0xff46] = value;
		if (value < 0xa0 || value >= 0xc0)
			memcpy(_emu._RAM + 0xfe00, _emu._RAM + value * 256, 40 * 4);
		else
			memcpy(_emu._RAM + 0xfe00, ram_bank + (value - 0xa0) * 256, 40 * 4);
	}
}

void			Memory_controller::write_tac(uint8_t value)
{
	_emu._RAM[REG_TAC] = value;
}

void			Memory_controller::write_key1(uint8_t value)
{
	if (value & 1)
	{
		_emu._RAM[REG_P1] = 0x30;
		_emu._RAM[REG_IE] = 0x00;
		_emu._RAM[REG_KEY1] = 0x01;
	}
}

void			Memory_controller::write_svbk(uint8_t value)
{
	if (_emu.cgb.on) {
		if (!(value & 0x7)) value++;
		_working_ram_bank = value & 0x7;
	}
	else
		_emu._RAM[REG_SVBK] = value;
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
	if (addr == _emu._RAM + 0xff00) {
		read_p1();
		return (addr);
	}
	return (NULL);
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

void		*Memory_controller::write_working_ram(uint8_t *addr, uint16_t value, int8_t size)
{
	if (addr < _emu._RAM + 0xd000 || addr > _emu._RAM + 0xdfff)
		return (NULL);
	if (_working_ram_bank == 1)
		return (NULL);
	uint16_t offset = (_working_ram_bank - 2) * 0x1000;
	if (size == 1)
		*(uint8_t *)(_working_ram + offset) = (uint8_t)value;
	else
		*(uint16_t *)(_working_ram + offset) = value;
	return (_working_ram + offset);
}

void		*Memory_controller::read_working_ram(uint8_t *addr)
{
	if (addr < _emu._RAM + 0xd000 || addr > _emu._RAM + 0xdfff)
		return (NULL);
	if (_working_ram_bank == 1)
		return (NULL);
	return (_working_ram + (_working_ram_bank - 2) * 0x1000);
}

uint16_t	Memory_controller::mem_read(void *addr, int8_t size)
{
	void	*read_addr = NULL;

	if ((read_addr = read_ROM_RAM_regs((uint8_t*)addr))) ;
	else {
		if (_debug)
			_emu.check_watchpoint((uint8_t *)addr, RD, size);
		if ((read_addr = cpu_regs(addr))) ;
		else if ((read_addr = read_gb_regs((uint8_t*)addr))) ;
		else if (_emu.cgb.on && (read_addr = read_working_ram((uint8_t*)addr))) ;
		else if ((read_addr = gb_mem(addr))) ;
		else {
			printf("GBmu: warning: Invalid read at 0x%hx", (uint16_t)((uint8_t *)addr - _emu._RAM));
			return (0);
		}
	}
	if (size == 2)
		return (*(uint16_t *)read_addr);
	else
		return (*(uint8_t *)read_addr);
}

void		Memory_controller::mem_write(void *addr, uint16_t value, int8_t size)
{
	void	*write_addr;

	if ((write_addr = cpu_regs(addr))) ;
	else {
		if (_debug)
			_emu.check_watchpoint((uint8_t *)addr, WR, size);
		if (write_ROM_regs((uint8_t*)addr, value, size))
			return ;
		else if (write_RAM_regs((uint8_t*)addr, value, size))
			return ;
		else if (write_gb_regs((uint8_t *)addr, value, size))
			return ;
		else if (_emu.cgb.on && write_working_ram((uint8_t *)addr, value, size))
			return ;
		else if ((write_addr = gb_mem(addr))) ;
		else {
			printf("GBmu: warning: Invalid write at 0x%hx", (uint16_t)((uint8_t *)addr - _emu._RAM));
			return ;
		} 
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
		fs.write((char *)external_ram, _ram_size);
		fs.close();
	}
	if (_ram_size > 0)
		delete external_ram;
	if (_emu.cgb.on)
		delete _working_ram;
}

void	Memory_controller::init(size_t ram_size) {
	_ram_size = ram_size;
	rom_bank = (const uint8_t*)(_emu._ROM.c_str() + 0x4000);
	external_ram = (_ram_size > 0) ? new uint8_t[_ram_size] : _emu._RAM + 0xa000;
	ram_bank = external_ram;
	if (_emu.cgb.on) {
		_working_ram = new uint8_t[0x6000];
		_working_ram_bank = 1;
	}
	std::ifstream fs;
	fs.open (_emu._save_name, std::fstream::in | ios::binary);
	if (fs.is_open())
	{
		fs.read((char *)external_ram, _ram_size);
		fs.close();
	}
	_RAM_ENABLE = false;
	_ROM_BANK = 1;
}

void	Memory_controller::new_dma(uint16_t video_offset, uint16_t src_offset, uint16_t len)
{
	uint8_t *video_real_addr;

	if (video_offset < 0x8000 || video_offset > 0xa000 || src_offset >= 0x8000 || src_offset < 0xa000 || src_offset >= 0xe000)
		return ;
	if (video_offset + len >= 0xa000)
		len = 0xa000 - video_offset;

	if (_video_ram_bank == 1)
		video_real_addr = _video_external_ram + (video_offset - 0x8000);
	else
		video_real_addr = _emu._RAM + video_offset;

	while (len > 0) {
		if (src_offset < 0x4000)
			memcpy(video_real_addr, _emu._RAM + src_offset, (len %= 0x1000));
		if (src_offset < 0x8000)
			memcpy(video_real_addr, rom_bank + (src_offset - 0x4000), (len %= 0x1000));
		else if (src_offset >= 0xa000 && src_offset < 0xc000) {
			if (0xa000 + _ram_size > src_offset) {
				memcpy(video_real_addr, _emu._RAM + src_offset, (len %= 0x1000));
			}
			else
				memcpy(video_real_addr, rom_bank + (src_offset - 0x4000), (len %= 0x1000));
		}
	}
}

Memory_controller::Memory_controller(Emulateur &emu, size_t ram_size, bool debug): _emu(emu), _ram_regs({RAM_REGS}), _debug(debug)
{
}

Memory_controller::~Memory_controller() {
}

Memory_controller &	Memory_controller::operator=(const Memory_controller & cp) {
	(void)cp;
	return (*this);
}
