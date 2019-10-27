#include <Emulateur.hpp>

void		*Memory_controller_MBC2::read_ROM_RAM_regs(uint8_t *addr)
{
	if (addr < _emu.RAM)
		return (NULL);
	if (addr - _emu.RAM < 0x4000)
		return (addr);
	else if (addr - _emu.RAM  < 0x8000)
		return (void*)(rom_bank + (addr - _emu.RAM - 0x4000));
	else if (addr - _emu.RAM >= 0xa000 && addr - _emu.RAM <= 0xa1ff)
	{
		if (_ram_ext_work_enable)
			return (void*)(ram_ext_work_bank + (addr - _emu.RAM - 0xa000));
		return (NULL);
	}
	else return (NULL);
}

bool		Memory_controller_MBC2::write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr < _emu.RAM)
		return (false);

	if (addr - _emu.RAM < 0x2000) {
		_ram_ext_work_enable = !((addr - _emu.RAM) & 0x1000) ? !_ram_ext_work_enable : _ram_ext_work_enable;
	}
	else if (addr - _emu.RAM < 0x4000)
	{
		if ((addr - _emu.RAM) & 0x0100) {
			_rom_bank_selected = value & 0x0f;
		}
		else
			printf("ERROR: Address range should have 0x1000 bit set to 1 at addr 0x%hx\n", (uint16_t)(addr - _emu.RAM));
	}
	else
		return (false);
	rom_bank = (const uint8_t*)(_emu.ROM.c_str() + 0x4000 * _rom_bank_selected);
	ram_ext_work_bank = ram_ext_work_orig_ptr;
	return (true);
}

bool		Memory_controller_MBC2::write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size)
{
	if (addr - _emu.RAM >= 0xA000 && addr - _emu.RAM <= 0xa1ff)
	{
		if (size == 2)
			*(uint16_t *)(ram_ext_work_bank + (addr - _emu.RAM - 0xA000)) = value & 0x0f0f;
		else
			*(uint8_t *)(ram_ext_work_bank + (addr - _emu.RAM - 0xA000)) = (uint8_t)value & 0x0f;
		return (true);
	}
	return (false);
}

uint16_t	Memory_controller_MBC2::mem_read(void *addr, int8_t size)
{
	void	*read_addr = NULL;

	_emu.check_watchpoint((uint8_t *)addr, RD, size);
	if ((read_addr = read_ROM_RAM_regs((uint8_t*)addr))) {
		if ((uint8_t*)addr - _emu.RAM >= 0xa000 && (uint8_t*)addr - _emu.RAM <= 0xa1ff) {
			if (size == 2)
				return ((*(uint16_t *)read_addr) & 0x0f0f);
			else
				return ((*(uint8_t *)read_addr) & 0x0f);
		}
	}
	else if ((read_addr = cpu_regs(addr))) ;
	else if ((read_addr = read_gb_regs((uint8_t*)addr))) ;
	else if (_emu.cgb.on && (read_addr = read_ram_work_bank((uint8_t*)addr))) ;
	else if (_emu.cgb.on && (read_addr = read_video_bank((uint8_t*)addr))) ;
	else if ((read_addr = gb_mem(addr))) ;
	else {
		printf("GBmu: warning: Invalid read at 0x%hx", (uint16_t)((uint8_t *)addr - _emu.RAM));
		return (0);
	}
	if (size == 2)
		return (*(uint16_t *)read_addr);
	else
		return (*(uint8_t *)read_addr);
}

void	Memory_controller_MBC2::save()
{
	ofstream fs;
	char	tmp[MBC2_SAV_SIZE];

	for (uint16_t i = 0; i < MBC2_SAV_SIZE; i++)
		tmp[i] = (ram_ext_work_orig_ptr[i * 2] & 0x0f) + ((ram_ext_work_orig_ptr[i * 2 + 1] & 0x0f) << 4);
	fs.open(_emu.save_name, ios::out | ios::binary);
	if (fs.is_open()) {
		fs.write(tmp, MBC2_SAV_SIZE);
		fs.close();
	}
	if (_emu.cgb.on) {
		delete _ram_work_bank;
		delete _ram_video_bank1;
	}
}

void	Memory_controller_MBC2::init(size_t ram_size) {
	_ram_size = MBC2_RAM_SIZE;
	ram_ext_work_orig_ptr = _emu.RAM + 0xa000;

	std::ifstream fs;
	char	tmp[MBC2_SAV_SIZE];

	fs.open(_emu.save_name, std::fstream::in | ios::binary);
	if (fs.is_open())
	{
		fs.read(tmp, MBC2_SAV_SIZE);
		fs.close();
	}
	for (uint16_t i = 0; i < MBC2_SAV_SIZE; i++) {
		ram_ext_work_orig_ptr[i * 2] = tmp[i] & 0x0f;
		ram_ext_work_orig_ptr[i * 2 + 1] = (tmp[i] & 0xf0) >> 4;
	}
}

Memory_controller_MBC2::Memory_controller_MBC2(Emulateur &emu, size_t ram_size, bool debug): Memory_controller(emu, ram_size, debug)
{
	init(MBC2_RAM_SIZE);
}
