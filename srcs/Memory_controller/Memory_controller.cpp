#include <Emulateur.hpp>

void			Memory_controller::write_div(uint8_t value)
{
	(void)value;
	_emu.gb_regs.div = 0;
}

void			Memory_controller::write_lcdc(uint8_t value)
{
	struct s_lcdc l;

	l = *(struct s_lcdc *)&value;
	if (_emu.gb_regs.lcdc.on && !l.on)
	{
		_emu.RAM[REG_LY] = 0;
		_emu.lcd_cycle = 0;
	}
	_emu.gb_regs.lcdc = l;
}

void			Memory_controller::write_stat(uint8_t value)
{
	uint8_t mode;

	// _emu.RAM[REG_STAT] = (_emu.RAM[REG_STAT] & 3) | (value & 120);
	mode = _emu.gb_regs.stat.mode;
	_emu.gb_regs.stat = *(struct s_stat *)&value;
	_emu.gb_regs.stat.mode = mode;
}

void			Memory_controller::write_scy(uint8_t value)
{
	(void)value;
	_emu.RAM[REG_SCY] = value;
}

void			Memory_controller::write_scx(uint8_t value)
{
	(void)value;
	_emu.RAM[REG_SCX] = value;
}

void			Memory_controller::write_ly(uint8_t value)
{
	(void)value;
	_emu.RAM[REG_LY] = 0;
	_emu.lcd_cycle = 0;
	if (_emu.RAM[REG_LY] == _emu.RAM[REG_LYC])
	{
		_emu.gb_regs.stat.match_ly = true;
		if (_emu.gb_regs.stat.imatch_ly)
				_emu.gb_regs.iflag.lcdc = true;
	}
	else
		_emu.gb_regs.stat.match_ly = false;
}

void			Memory_controller::inc_ly(uint8_t ly)
{
	_emu.RAM[REG_LY] = ly;
	if (_emu.RAM[REG_LY] == _emu.RAM[REG_LYC])
	{
		_emu.gb_regs.stat.match_ly = true;
		if (_emu.gb_regs.stat.imatch_ly)
				_emu.gb_regs.iflag.lcdc = true;
	}
	else
		_emu.gb_regs.stat.match_ly = false;
}

void			Memory_controller::write_lyc(uint8_t value)
{
	_emu.RAM[REG_LYC] = value;
	if (_emu.RAM[REG_LY] == _emu.RAM[REG_LYC])
	{
		_emu.gb_regs.stat.match_ly = true;
		if (_emu.gb_regs.stat.imatch_ly)
				_emu.gb_regs.iflag.lcdc = true;
	}
	else
		_emu.gb_regs.stat.match_ly = false;
}

void			Memory_controller::write_dma(uint8_t value)
{
	if (_emu.cgb.on) {
		_emu.RAM[0xff46] = value;
		if (value >= 0x80 && value < 0xa0)
			memcpy(_emu.RAM + 0xfe00, (_emu.gb_regs.vbk.bank ? (_ram_video_bank1 + (value - 0x80) * 256) : (_emu.RAM + value * 256)), 40 * 4);
		else if (value >= 0xa0 && value < 0xc0)
			memcpy(_emu.RAM + 0xfe00, ram_ext_work_bank + (value - 0xa0) * 256, 40 * 4);
		else if (ram_work_bank_selected > 1 && value >= 0xd0 && value < 0xe0)
			memcpy(_emu.RAM + 0xfe00, _ram_work_bank + (ram_work_bank_selected - 2) * 0x1000 + (value - 0xd0) * 256, 40 * 4);
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

void			Memory_controller::write_hdma5(uint8_t value)
{
	if (_emu.cgb.on) {
		if (_emu.gb_regs.hdma5 & 0x80) {
			if (!(value & 0x80)){
				new_dma(_emu.gb_regs.hdma3 << 8 | (_emu.gb_regs.hdma4 & 0xf0), _emu.gb_regs.hdma1 << 8 | (_emu.gb_regs.hdma2 & 0xf0), (value + 1) * 16);
				_emu.gb_regs.hdma5 = 0xFF;
			}
			else {
				_emu.src_dma = (_emu.gb_regs.hdma1 << 8) | (_emu.gb_regs.hdma2 & 0xf0);
				_emu.dst_dma = (((_emu.gb_regs.hdma3 & 0x1f) << 8) | (_emu.gb_regs.hdma4 & 0xf0));
				_emu.gb_regs.hdma5 = (value & 0x7f);
			}
		}
		else if (_emu.gb_regs.hdma5 & 0x80 && !(value & 0x80))
			_emu.gb_regs.hdma5 = 0xFF;
	}
}

void			Memory_controller::write_tac(uint8_t value)
{
	_emu.gb_regs.tac = *(struct s_tac *)&value;
}

void			Memory_controller::write_key1(uint8_t value)
{
	_emu.RAM[REG_KEY1] = (_emu.RAM[REG_KEY1] & 0x80) | 0x7e | (value & 1);
}

void			Memory_controller::write_vbk(uint8_t value)
{
	_emu.gb_regs.vbk.unused = 127;
	_emu.gb_regs.vbk.bank = value & 1;
}

void			Memory_controller::write_svbk(uint8_t value)
{
	if (_emu.cgb.on) {
		value = (value & 7) ? value : (value | 1);
		_emu.RAM[REG_SVBK] = (_emu.RAM[REG_SVBK] & ~7) | (value & 7);
		if (!(value & 0x7))
			value++;
		ram_work_bank_selected = value & 0x7;
	}
	else
		_emu.RAM[REG_SVBK] = value;
}

void			Memory_controller::write_bcpd(uint8_t value)
{
	if (_emu.cgb.on) {
		_emu.gb_regs.bcpd = value;
		pal_col_bg[_emu.gb_regs.bcps.pal_addr] = _emu.gb_regs.bcpd;
		if (_emu.gb_regs.bcps.inc)
			_emu.gb_regs.bcps.pal_addr++;
	}
}

void			Memory_controller::write_ocpd(uint8_t value)
{
	if (_emu.cgb.on) {
		_emu.gb_regs.ocpd = value;
		pal_col_obj[_emu.gb_regs.ocps.pal_addr] = _emu.gb_regs.ocpd;
		if (_emu.gb_regs.ocps.inc)
			_emu.gb_regs.ocps.pal_addr++;
	}
}

void			Memory_controller::write_n52(uint8_t value)
{
	(void)value;
	_emu.RAM[0xff26] = 0;
}

void			Memory_controller::read_p1()
{
	_emu.gb_regs.p1.out = 0xf;
	if ((*reinterpret_cast<uint8_t*>(&_emu.gb_regs.p1) >> 4) & P15)
		_emu.gb_regs.p1.out &= _emu.input.p14;
	if ((*reinterpret_cast<uint8_t*>(&_emu.gb_regs.p1) >> 4) & P14)
		_emu.gb_regs.p1.out &= _emu.input.p15;
	_emu.gb_regs.p1.unused = -1;
}

void			Memory_controller::read_bcpd()
{
	if (_emu.cgb.on) {
		printf("Read on BCPD\n");
		_emu.gb_regs.bcpd = pal_col_bg[_emu.gb_regs.bcps.pal_addr];
	}
}

void			Memory_controller::read_ocpd()
{
	if (_emu.cgb.on) {
		printf("Read on OCPD\n");
		_emu.gb_regs.ocpd = pal_col_obj[_emu.gb_regs.ocps.pal_addr];
	}
}

void			Memory_controller::read_vbk()
{
}

void			Memory_controller::read_if()
{
	_emu.RAM[0xFF0F] |= 0xE0;
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


uint8_t		*Memory_controller::cpu_regs(uint8_t *addr)
{
	if (addr >= reinterpret_cast<uint8_t *>(&_emu.regs) && addr < reinterpret_cast<uint8_t *>(&_emu.regs) + sizeof(_emu.regs))
		return (addr);
	return (NULL);
}

uint8_t		*Memory_controller::read_gb_regs(uint8_t *addr)
{
	if (addr == _emu.RAM + 0xff00) {
		read_p1();
		return (addr);
	}
	else if (addr == _emu.RAM + 0xff69) {
		read_bcpd();
		return (addr);
	}
	else if (addr == _emu.RAM + 0xff6b) {
		read_ocpd();
		return (addr);
	}
	else if (addr == _emu.RAM + 0xff4f) {
		read_vbk();
		return (addr);
	}
	else if (addr == _emu.RAM + 0xff0f) {
		read_if();
		return (addr);
	}
	return (NULL);
}

uint8_t		*Memory_controller::write_gb_regs(uint8_t *addr, uint8_t value)
{
	if (addr < _emu.RAM + 0xff00 || addr > _emu.RAM + 0xff7f)
		return (NULL);
	if (_ram_regs[addr - 0xff00 - _emu.RAM].write)
		(this->*_ram_regs[addr - 0xff00 - _emu.RAM].write)(value);
	else return (NULL);
	return (addr);
}

uint8_t		*Memory_controller::gb_mem(uint8_t *addr)
{
	if (addr < _emu.RAM || addr > _emu.RAM + 0xffff)
		return (NULL);
	return (addr);
}

uint8_t		*Memory_controller::write_ram_work_bank(uint8_t *addr, uint8_t value)
{
	if (addr < _emu.RAM + 0xd000 || addr > _emu.RAM + 0xdfff)
		return (NULL);
	if (ram_work_bank_selected == 1)
		return (NULL);
	uint16_t offset = (ram_work_bank_selected - 2) * 0x1000 + (addr - _emu.RAM) - 0xd000;
	*(uint8_t *)(_ram_work_bank + offset) = (uint8_t)value;
	return (_ram_work_bank + offset);
}

uint8_t		*Memory_controller::write_video_ram(uint8_t *addr, uint8_t value)
{
	if (addr < _emu.RAM + 0x8000 || addr > _emu.RAM + 0x9fff)
		return (NULL);
	if (_emu.gb_regs.vbk.bank == 0)
		return (NULL);
	uint16_t offset = addr - _emu.RAM - 0x8000;
	*(uint8_t *)(_ram_video_bank1 + offset) = (uint8_t)value;
	return (_ram_video_bank1 + offset);
}

uint8_t		*Memory_controller::read_ram_work_bank(uint8_t *addr)
{
	if (addr < _emu.RAM + 0xd000 || addr > _emu.RAM + 0xdfff)
		return (NULL);
	if (ram_work_bank_selected == 1)
		return (NULL);
	return (_ram_work_bank + (ram_work_bank_selected - 2) * 0x1000 + (addr - _emu.RAM) - 0xd000);
}

uint8_t		*Memory_controller::read_video_bank(uint8_t *addr)
{
	if (addr < _emu.RAM + 0x8000 || addr > _emu.RAM + 0x9fff)
		return (NULL);
	if (_emu.gb_regs.vbk.bank == 0)
		return (NULL);
	return (_ram_video_bank1 + (addr - _emu.RAM - 0x8000));
}

uint8_t	Memory_controller::mem_read(uint8_t *addr)
{
	uint8_t	*read_addr = NULL;

	if ((read_addr = read_ROM_RAM_regs(addr))) ;
	else {
		if (_debug)
			_emu.check_watchpoint((uint8_t *)addr, RD, 0);
		if ((read_addr = cpu_regs(addr))) ;
		else if ((read_addr = read_gb_regs(addr))) ;
		else if (_emu.cgb.on && (read_addr = read_ram_work_bank(addr))) ;
		else if (_emu.cgb.on && (read_addr = read_video_bank(addr))) ;
		else if ((read_addr = gb_mem(addr))) ;
		else {
			printf("GBmu: warning: Invalid read at 0x%hx", (uint16_t)((uint8_t *)addr - _emu.RAM));
			return (0);
		}
	}
	return (*read_addr);
}

uint16_t	Memory_controller::mem_read(void *addr, uint8_t size)
{
	uint16_t ret = mem_read(reinterpret_cast<uint8_t *>(addr));
	if (size == 2)
		ret += mem_read(reinterpret_cast<uint8_t *>(addr) + 1) << 8;
	return (ret);
}

void		Memory_controller::mem_write(uint8_t *addr, uint8_t value)
{
	void	*write_addr;

	if ((write_addr = cpu_regs(addr))) ;
	else {
		if (_debug)
			_emu.check_watchpoint((uint8_t *)addr, WR, value);
		if (write_ROM_regs(addr, value))
			return ;
		else if (write_RAM_regs(addr, value))
			return ;
		else if (write_gb_regs(addr, value))
			return ;
		else if (_emu.cgb.on && write_ram_work_bank(addr, value))
			return ;
		else if (_emu.cgb.on && write_video_ram(addr, value))
			return ;
		else if ((write_addr = gb_mem(addr))) ;
		else {
			printf("GBmu: warning: Invalid write at 0x%hx", (uint16_t)((uint8_t *)addr - _emu.RAM));
			return ;
		} 
	}
	*addr = value;
}

void		Memory_controller::mem_write(void *addr, uint16_t value, int8_t size)
{
	mem_write(reinterpret_cast<uint8_t *>(addr), value);
	if (size == 2)
		mem_write(reinterpret_cast<uint8_t *>(addr) + 1, value >> 8);
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
	if (_emu.cgb.on) {
		delete _ram_work_bank;
		delete _ram_video_bank1;
	}
}

void	Memory_controller::init(size_t ram_size) {
	_ram_size = ram_size;
	rom_bank = (const uint8_t*)(_emu.ROM + 0x4000);
	ram_ext_work_orig_ptr = (_ram_size > 0) ? new uint8_t[_ram_size] : _emu.RAM + 0xa000;
	ram_ext_work_bank = ram_ext_work_orig_ptr;
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

uint8_t	*Memory_controller::get_ptr_from_off(uint16_t src_offset)
{
	if (src_offset < 0x4000)
		return (_emu.RAM + src_offset);
	else if (src_offset < 0x8000)
		return (const_cast<uint8_t *>(rom_bank + (src_offset - 0x4000)));
	else if (src_offset < 0xC000)
		return (ram_ext_work_bank + (src_offset - 0xa000));
	else if (src_offset < 0xd000 || ram_work_bank_selected == 1)
		return (_emu.RAM + src_offset);
	else
		return (_ram_work_bank + (ram_work_bank_selected - 2) * 0x1000 + (src_offset - 0xd000));

}

void	Memory_controller::new_dma(uint16_t dst_offset, uint16_t src_offset, uint16_t len)
{
	uint8_t *dst_real_addr;
	uint8_t *src_real_addr;
	uint16_t tmp = 0xa000 - dst_offset;

	dst_offset += ((dst_offset < 0x8000) ? 0x8000 : 0x0);
	if ((src_offset >= 0x8000 && src_offset < 0xa000) || src_offset >= 0xe000 || dst_offset < 0x8000 || dst_offset >= 0xa000)
		return ;
	if (_emu.gb_regs.vbk.bank)
		dst_real_addr = _ram_video_bank1 + (dst_offset - 0x8000);
	else
		dst_real_addr = _emu.RAM + dst_offset;
	len = std::min(tmp, len);
	tmp = 0x1000 - (src_offset & 0xfff);
	while (len > 0) {
		tmp = std::min(tmp, len);
		src_real_addr = get_ptr_from_off(src_offset);
		memcpy(dst_real_addr, src_real_addr, tmp);
		src_offset += tmp;
		dst_offset += tmp;
		len -= tmp;
		tmp = 0x1000;
	}
}

const struct s_bg_atrb	&Memory_controller::get_bg_atrb(bool area, uint32_t id) const {
	return (reinterpret_cast<struct s_bg_atrb*>(_ram_video_bank1 + (area ? 0x1c00 : 0x1800))[id]);
}

const uint8_t			*Memory_controller::get_ram_video_bank1(void) const {
	return (_ram_video_bank1);
}


Memory_controller::Memory_controller(Emulateur &emu, size_t ram_size, bool debug): _emu(emu), _ram_regs({RAM_REGS}), _debug(debug)
{
	(void)ram_size;
	if (_emu.cgb.on) {
		_ram_work_bank = new uint8_t[0x6000];
		for (int x = 0; x < 0x6000; x++)
			_ram_work_bank[x] = (x & 8) ^ ((x >> 8) & 8) ? 0x00 : 0xff;
		ram_work_bank_selected = 1;
		_ram_video_bank1 = new uint8_t[0x2000];
		for (int x = 0; x < 0x2000; x++)
			_ram_video_bank1[x] = (x & 8) ^ ((x >> 8) & 8) ? 0x00 : 0xff;
		}
}

Memory_controller::~Memory_controller() {
}

bool	Memory_controller::test()
{
	int x = 0;

	memset(_ram_video_bank1, 0, 0x2000);
	memset(_emu.RAM + 0x8000, 0, 0x2000);
	mem_write(&_emu.gb_regs.vbk, 0, 1);
	while (x < 0x2000)
	{
		mem_write(_emu.RAM + 0x8000 + x, 42, 1);
		if (*(_emu.RAM + 0x8000 + x) != 42 || *(_ram_video_bank1 + x) != 0)
			return (false);
		x++;
	}
	x = 0;
	mem_write(&_emu.gb_regs.vbk, 1, 1);
	while (x < 0x2000)
	{
		mem_write(_emu.RAM + 0x8000 + x, 21, 1);
		if (*(_emu.RAM + 0x8000 + x) != 42 || *(_ram_video_bank1 + x) != 21)
			return (false);
		x++;
	}


	_emu.RAM[0xff68] = 0;
	memset(pal_col_bg, 0, 64);
	mem_write(_emu.RAM + 0xff69, 42, 1);
	if (*pal_col_bg != 42)
		return (false);
	mem_write(_emu.RAM + 0xff69, 1, 1);
	if (*pal_col_bg != 1 && *(pal_col_bg + 1) != 0)
		return (false);
	_emu.RAM[0xff68] = 0x80;
	x = 0;
	while (x < 64)
	{
		mem_write(_emu.RAM + 0xff69, x, 1);
		if (*(pal_col_bg + x) != x)
			return (false);
			x++;
	}

	_emu.RAM[0xff6a] = 0;
	memset(pal_col_obj, 0, 64);
	mem_write(_emu.RAM + 0xff6b, 42, 1);
	if (*pal_col_obj != 42)
		return (false);
	mem_write(_emu.RAM + 0xff6b, 1, 1);
	if (*pal_col_obj != 1 && *(pal_col_obj + 1) != 0)
		return (false);
	_emu.RAM[0xff6a] = 0x80;
	x = 0;
	while (x < 64)
	{
		mem_write(_emu.RAM + 0xff6b, x, 1);
		if (*(pal_col_obj + x) != x)
			return (false);
			x++;
	}

	return (true);
}

Memory_controller &	Memory_controller::operator=(const Memory_controller & cp) {
	(void)cp;
	return (*this);
}


