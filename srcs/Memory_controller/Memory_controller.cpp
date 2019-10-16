#include <Emulateur.hpp>

void			Memory_controller::write_div(uint8_t value)
{
	_emu.RAM[REG_DIV] = 0;
}

void			Memory_controller::write_lcdc(uint8_t value)
{
	if (!(_emu.RAM[REG_LCDC] & (1 << 5)) && (value & (1 << 5)))
		printf("Windowing on flag activated : %x %x\n", _emu.RAM[REG_WX], _emu.RAM[REG_WY]);
	if ((_emu.RAM[REG_LCDC] & 0x80) && (!(value & 0x80)))
		_emu.RAM[REG_LY] = 0;
	_emu.RAM[REG_LCDC] = value;
}

void			Memory_controller::write_stat(uint8_t value)
{
	_emu.RAM[REG_STAT] = (_emu.RAM[REG_STAT] & 3) | (value & 120);
}

void			Memory_controller::write_scy(uint8_t value)
{
	_emu.RAM[REG_SCY] = value;
}

void			Memory_controller::write_scx(uint8_t value)
{
	_emu.RAM[REG_SCX] = value;
}

void			Memory_controller::write_ly(uint8_t value)
{
	_emu.RAM[REG_LY] = value;
	if (_emu.RAM[REG_LY] == _emu.RAM[REG_LYC])
	{
		_emu.RAM[REG_STAT] |= 4;
		if (_emu.RAM[REG_STAT] & (1 << 6))
				_emu.RAM[REG_IF] |= (1 << 1);
	}
	else
		_emu.RAM[REG_STAT] &= ~4;
	// printf("Writing value %x in ly\n", value);
}

void			Memory_controller::write_lyc(uint8_t value)
{
	_emu.RAM[REG_LYC] = value;
	if (_emu.RAM[REG_LY] == _emu.RAM[REG_LYC])
	{
		_emu.RAM[REG_STAT] |= 4;
		if (_emu.RAM[REG_STAT] & (1 << 6))
				_emu.RAM[REG_IF] |= (1 << 1);
	}
	else
		_emu.RAM[REG_STAT] &= ~4;
}

void			Memory_controller::write_dma(uint8_t value)
{
	if (_emu.cgb.on) {
		_emu.RAM[0xff46] = value;
		if (value >= 0x80 && value < 0xa0)
			memcpy(_emu.RAM + 0xfe00, (_ram_video_bank1_selected ? (_ram_video_bank1 + (value - 0x80) * 256) : (_emu.RAM + value * 256)), 40 * 4);
		else if (value >= 0xa0 && value < 0xc0)
			memcpy(_emu.RAM + 0xfe00, ram_ext_work_bank + (value - 0xa0) * 256, 40 * 4);
		else if (_ram_work_bank_selected > 1 && value >= 0xd0 && value < 0xe0)
			memcpy(_emu.RAM + 0xfe00, _ram_work_bank + (_ram_work_bank_selected - 2) * 0x1000 + (value - 0xd0) * 256, 40 * 4);
		else
			memcpy(_emu.RAM + 0xfe00, _emu.RAM + value * 256, 40 * 4);
	}
	else {
		if (value < 0x80 || value > 0xdf)
			return ;
		_emu.RAM[0xff46] = value;
		if (value < 0xa0 || value >= 0xc0)
			memcpy(_emu.RAM + 0xfe00, _emu.RAM + value * 256, 40 * 4);
		else
			memcpy(_emu.RAM + 0xfe00, ram_ext_work_bank + (value - 0xa0) * 256, 40 * 4);
	}
}

void			Memory_controller::write_tac(uint8_t value)
{
	_emu.RAM[REG_TAC] = value;
}

void			Memory_controller::write_key1(uint8_t value)
{
	if (value & 1)
	{
		_emu.RAM[REG_P1] = 0x30;
		_emu.RAM[REG_IE] = 0x00;
		_emu.RAM[REG_KEY1] = 0x01;
	}
}

void			Memory_controller::write_svbk(uint8_t value)
{
	if (_emu.cgb.on) {
		if (!(value & 0x7)) value++;
		_ram_work_bank_selected = value & 0x7;
	}
	else
		_emu.RAM[REG_SVBK] = value;
}

void			Memory_controller::read_p1()
{
	uint8_t value;

	_emu.gb_regs.p1.out = 0xf;
	value = _emu.RAM[REG_P1] | 0xf;
	if (!(value & 0x10))
		value &= 0xf0 | _emu.input.p14;
	if (!(value & 0x20))
		value &= 0xf0 | _emu.input.p15;
	_emu.RAM[REG_P1] = value;
}

void		*Memory_controller::cpu_regs(void *addr)
{
	if (addr >= &_emu.regs && addr < &_emu.regs + sizeof(_emu.regs))
		return (addr);
	return (NULL);
}

void		*Memory_controller::read_gb_regs(uint8_t *addr)
{
	if (addr == _emu.RAM + 0xff00) {
		read_p1();
		return (addr);
	}
	return (NULL);
}

void		*Memory_controller::write_gb_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr < _emu.RAM + 0xff00 || addr > _emu.RAM + 0xff7f)
		return (NULL);
	if (_ram_regs[addr - 0xff00 - _emu.RAM].write)
		(this->*_ram_regs[addr - 0xff00 - _emu.RAM].write)(value);
	else return (NULL);
	return (addr);
}

void		*Memory_controller::gb_mem(void *addr)
{
	if (addr < _emu.RAM || addr > _emu.RAM + 0xffff)
		return (NULL);
	return (addr);
}

void		*Memory_controller::write_ram_work_bank(uint8_t *addr, uint16_t value, int8_t size)
{
	if (addr < _emu.RAM + 0xd000 || addr > _emu.RAM + 0xdfff)
		return (NULL);
	if (_ram_work_bank_selected == 1)
		return (NULL);
	uint16_t offset = (_ram_work_bank_selected - 2) * 0x1000;
	if (size == 1)
		*(uint8_t *)(_ram_work_bank + offset) = (uint8_t)value;
	else
		*(uint16_t *)(_ram_work_bank + offset) = value;
	return (_ram_work_bank + offset);
}

void		*Memory_controller::read_ram_work_bank(uint8_t *addr)
{
	if (addr < _emu.RAM + 0xd000 || addr > _emu.RAM + 0xdfff)
		return (NULL);
	if (_ram_work_bank_selected == 1)
		return (NULL);
	return (_ram_work_bank + (_ram_work_bank_selected - 2) * 0x1000);
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
		else if (_emu.cgb.on && (read_addr = read_ram_work_bank((uint8_t*)addr))) ;
		else if ((read_addr = gb_mem(addr))) ;
		else {
			printf("GBmu: warning: Invalid read at 0x%hx", (uint16_t)((uint8_t *)addr - _emu.RAM));
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
		else if (_emu.cgb.on && write_ram_work_bank((uint8_t *)addr, value, size))
			return ;
		else if ((write_addr = gb_mem(addr))) ;
		else {
			printf("GBmu: warning: Invalid write at 0x%hx", (uint16_t)((uint8_t *)addr - _emu.RAM));
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

	fs.open(_emu.save_name, ios::out | ios::binary);
	if (fs.is_open()) {
		fs.write((char *)ram_ext_work_orig_ptr, _ram_size);
		fs.close();
	}
	if (_ram_size > 0)
		delete ram_ext_work_orig_ptr;
	if (_emu.cgb.on)
		delete _ram_work_bank;
}

void	Memory_controller::init(size_t ram_size) {
	_ram_size = ram_size;
	rom_bank = (const uint8_t*)(_emu.ROM.c_str() + 0x4000);
	ram_ext_work_orig_ptr = (_ram_size > 0) ? new uint8_t[_ram_size] : _emu.RAM + 0xa000;
	ram_ext_work_bank = ram_ext_work_orig_ptr;
	if (_emu.cgb.on) {
		_ram_work_bank = new uint8_t[0x6000];
		_ram_work_bank_selected = 1;
	}
	std::ifstream fs;
	fs.open (_emu.save_name, std::fstream::in | ios::binary);
	if (fs.is_open())
	{
		fs.read((char *)ram_ext_work_orig_ptr, _ram_size);
		fs.close();
	}
	_ram_ext_work_enable = false;
	_rom_bank_selected = 1;
}

void	Memory_controller::new_dma(uint16_t video_offset, uint16_t src_offset, uint16_t len)
{
	uint8_t *video_real_addr;

	if (video_offset < 0x8000 || video_offset > 0xa000 || src_offset >= 0x8000 || src_offset < 0xa000 || src_offset >= 0xe000)
		return ;
	if (video_offset + len >= 0xa000)
		len = 0xa000 - video_offset;

	if (_ram_video_bank1_selected == 1)
		video_real_addr = _ram_video_bank1 + (video_offset - 0x8000);
	else
		video_real_addr = _emu.RAM + video_offset;

	uint16_t tmp;
	while (len > 0) {
		tmp = 0x1000 - len % 0x1000;
		if (src_offset < 0x4000)
			memcpy(video_real_addr, _emu.RAM + src_offset, tmp);
		if (src_offset < 0x8000)
			memcpy(video_real_addr, rom_bank + (src_offset - 0x4000), tmp);
		else if (src_offset >= 0xa000 && src_offset < 0xc000) {
			if (0xa000 + _ram_size > src_offset || !_ram_ext_work_enable)
				memcpy(video_real_addr, _emu.RAM + src_offset, tmp);
			else {
				if ((src_offset + tmp) > (0xa000 + _ram_size))
					len -= (src_offset + tmp) - (0xa000 + _ram_size);
				memcpy(video_real_addr, ram_ext_work_bank + (src_offset - 0x4000), tmp);
			}
		}
		else if (src_offset < 0xd000)
			memcpy(video_real_addr, _emu.RAM + src_offset, tmp);
		else if (src_offset < 0xe000) {
			if (_ram_work_bank_selected == 1)
				memcpy(video_real_addr, _emu.RAM + src_offset, tmp);
			else
				memcpy(video_real_addr, _ram_work_bank + (_ram_work_bank_selected - 2) * 0x1000, tmp);
		}
		else
			return ;
		src_offset += tmp;
		len -= tmp;
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
