#include <Emulateur.hpp>

#define MINUTES 60
#define HOURS 3600
#define DAY_LOW 86400
#define DAY_HIGH 22032000

uint8_t Memory_controller_MBC3::RTC::get_S(void) {
	printf("SECOND GET REQUEST\n");
	return get_timestamp_gb() % 60;
}

uint8_t Memory_controller_MBC3::RTC::get_M(void) {
	printf("MINUTE GET REQUEST\n");
	return get_timestamp_gb() / 60 % 60;
}

uint8_t Memory_controller_MBC3::RTC::get_H(void) {
	printf("HOUR GET REQUEST\n");
	return get_timestamp_gb() / 3600 % 24;
}

uint8_t Memory_controller_MBC3::RTC::get_DL(void) {
	// update_RTC();
	// change_stored_timestamp();
	// get_new_value_on_RTC();
	printf("DAY LOW BIT GET REQUEST\n");
	return get_timestamp_gb() / 86400 % 0xff;
}

uint8_t Memory_controller_MBC3::RTC::get_DH(void) {
	_day_count_9_bit = get_timestamp_gb() / 22032000;
	return _RTC_DH;
}

void Memory_controller_MBC3::RTC::set_S(uint8_t value) {
	printf("SECOND SET REQUEST\n");
	time_t current_timestamp_gb = get_timestamp_gb();
	time_t tmp = (current_timestamp_gb / 60 * 60) + value;
	if (_halt)
		_halt_timestamp_gb = tmp;
	else {
		_timestamp_gb = tmp;
		_real_timestamp += value - (current_timestamp_gb % 60);
	}
}

void Memory_controller_MBC3::RTC::set_M(uint8_t value) {
	printf("MINUTE SET REQUEST\n");
	time_t current_timestamp_gb = get_timestamp_gb();
	time_t tmp = (current_timestamp_gb / 3600 * 3600 + value * 60) + (current_timestamp_gb % 60);
	if (_halt)
		_halt_timestamp_gb = tmp;
	else {
		_timestamp_gb = tmp;
		_real_timestamp += value * 60 - (current_timestamp_gb / 60 % 60);
	}
}

void Memory_controller_MBC3::RTC::set_H(uint8_t value) {
	printf("HOUR SET REQUEST\n");
	time_t current_timestamp_gb = get_timestamp_gb();
	time_t tmp = (current_timestamp_gb / 86400 * 86400 + value * 3600) + (current_timestamp_gb / 60 % 60) + (current_timestamp_gb % 60);
	if (_halt)
		_halt_timestamp_gb = tmp;
	else
		_timestamp_gb = tmp;
}

void Memory_controller_MBC3::RTC::set_DL(uint8_t value) {
	printf("DAY LOW BIT SET REQUEST\n");
	time_t current_timestamp_gb = get_timestamp_gb();
	time_t tmp = (current_timestamp_gb / 22032000 * 22032000 + value * 86400) + (current_timestamp_gb / 3600 % 24) + (current_timestamp_gb / 60 % 60) + (current_timestamp_gb % 60);
	if (_halt)
		_halt_timestamp_gb = tmp;
	else
		_timestamp_gb = tmp;
}

void Memory_controller_MBC3::RTC::set_DH(uint8_t value) {
	printf("DH SET REQUEST\n");
	time_t current_timestamp_gb = get_timestamp_gb();
	time_t tmp = (current_timestamp_gb / 22118400 * 22118400 + (value & 0x01)) + (current_timestamp_gb / 86400 % 0xff) + (current_timestamp_gb / 3600 % 24) + (current_timestamp_gb / 60 % 60) + (current_timestamp_gb % 60);
	if (_halt)
		_halt_timestamp_gb = tmp;
	else
		_timestamp_gb = tmp;
	_RTC_DH = value;
}

void Memory_controller_MBC3::RTC::set_halt_flag() {
	printf("HALT LA\n");
	if (!_halt) {
		_halt_timestamp_gb = get_timestamp_gb();
	}
	else {
		_timestamp_gb = _halt_timestamp_gb;
		_real_timestamp = std::time(nullptr);
	}
	_halt = !_halt;
}

uint8_t	Memory_controller_MBC3::RTC::get_register() {
	return (this->*_getters[_register_in_use])();
}

void 	Memory_controller_MBC3::RTC::set_register(uint8_t value) {
	(this->*_setters[_register_in_use])(value);
}

time_t	Memory_controller_MBC3::RTC::get_timestamp_gb(void) {
	if (_halt)
		return (_halt_timestamp_gb);
	_timestamp_gb += std::time(nullptr) - _real_timestamp;
	if (_timestamp_gb / 44236800) // ((0x1ff + 1) * 24 * 60 * 60)
	{
		_day_count_cy = true;
		_timestamp_gb %= 44236800;
	}
	return (_timestamp_gb);
}

void	Memory_controller_MBC3::RTC::init_timestamp(std::time_t last_shutdown, std::time_t old_timestamp, uint8_t RTC_DH) {
	printf("Found timestamp\n");

	_real_timestamp = std::time(nullptr);
	time_t elapse_time = _real_timestamp - last_shutdown;
	_timestamp_gb = old_timestamp + elapse_time;
	_halt = RTC_DH & 0x40;
	printf("Halt init -> %d\n", _halt);
}

void	Memory_controller_MBC3::RTC::init_timestamp() {
	printf("No timestamp\n");
	_real_timestamp = std::time(nullptr);
	_timestamp_gb = 0;
	_day_count_cy = false;
	_halt = true;
}

Memory_controller_MBC3::RTC::RTC(void):
	_getters({
		&Memory_controller_MBC3::RTC::get_S,
		&Memory_controller_MBC3::RTC::get_M,
		&Memory_controller_MBC3::RTC::get_H,
		&Memory_controller_MBC3::RTC::get_DL,
		&Memory_controller_MBC3::RTC::get_DH
	}),
	_setters({
		&Memory_controller_MBC3::RTC::set_S,
		&Memory_controller_MBC3::RTC::set_M,
		&Memory_controller_MBC3::RTC::set_H,
		&Memory_controller_MBC3::RTC::set_DL,
		&Memory_controller_MBC3::RTC::set_DH
	})
{
	_register_in_use = 0;
	// _halt = false;
}


void	Memory_controller_MBC3::RTC::set_register_in_use(uint8_t value) {
	// printf("SET register to use 0x%02hhx\n", value);
	if (value >= 0x08 && value <= 0x0C)
		_register_in_use = value - 0x08;
}

Memory_controller_MBC3::RTC::~RTC(void) {
}

Memory_controller_MBC3::RTC &	Memory_controller_MBC3::RTC::operator=(const Memory_controller_MBC3::RTC & cp) {
	(void)cp;
	return (*this);
}

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
		if (_RAM_RTC_ENABLE) {
			if (_RAM_RTC_SELECT == E_RTC) {
				_read_reg_RTC = _RTC.get_register();
				return (&_read_reg_RTC);
			}
			return (void*)(ram_bank + (addr - _emu._RAM - 0xa000));
		}
		printf("_RAM_RTC_ENABLE not true\n");
	}
	return (NULL);
}

bool		Memory_controller_MBC3::write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size)
{
	if (addr < _emu._RAM)
		return (false);

	if (addr - _emu._RAM < 0x2000)
		_RAM_RTC_ENABLE = ((value & 0xf) == 0xa ? true : false);
	else if (addr - _emu._RAM < 0x4000)
	{
		if (!value)
			value = 1;
		_ROM_BANK = value & 0x7f;
	}
	else if (addr - _emu._RAM < 0x6000)
	{
		if (value <= 3) {
			_RAM_RTC_SELECT = E_RAM;
			_RAM_BANK = value;
		}
		else if (value >= 0x08 && value <= 0x0C) {
			_RAM_RTC_SELECT = E_RTC;
			_RTC.set_register_in_use(value);
		}
		else
			printf("ERROR: This value (%hhx) should be between 0x00-0x03 or 0x08-0x0C\n", value);
	}
	else if (addr - _emu._RAM  < 0x8000)
	{
		static bool previous_write_0 = false;

		if (value > 1)
			printf("ERROR: This value (%hhx) should be between 0 and 1\n", value);
		else {
			if (value == 0)
				previous_write_0 = true;
			else {
				if (previous_write_0)
					_RTC.set_halt_flag();
				previous_write_0 = false;
			}
		}
	}
	else
		return (false);
	rom_bank = (const uint8_t*)(_emu._ROM.c_str() + 0x4000 * _ROM_BANK);
	ram_bank = external_ram + _RAM_BANK * 0x2000;
	return (true);
}

bool		Memory_controller_MBC3::write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size)
{
	if (addr - _emu._RAM  >= 0xA000 && addr - _emu._RAM  < 0xC000)
	{
		if (_RAM_RTC_ENABLE && _RAM_RTC_SELECT == E_RTC) {
			_RTC.set_register((uint8_t)value);
			return true;
		}
		else {
			if (size == 2)
				*(uint16_t *)(ram_bank + (addr - _emu._RAM - 0xA000)) = value;
			else
				*(uint8_t *)(ram_bank + (addr - _emu._RAM - 0xA000)) = (uint8_t)value;
			return (true);
		}
	}
	return (false);
}

void	Memory_controller_MBC3::save()
{
	ofstream fs;

	fs.open(_emu._save_name, ios::out | ios::binary);
	if (fs.is_open()) {
		time_t tmp;
		tmp = std::time(nullptr);
		fs.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
		tmp = _RTC.get_timestamp_gb();
		fs.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
		uint8_t RTC_DH = _RTC.get_DH();
		fs.write(reinterpret_cast<char *>(&RTC_DH), sizeof(RTC_DH));
		fs.write((char *)external_ram, _ram_size);
		fs.close();
	}
	if (_ram_size > 0)
		delete external_ram;
}

void	Memory_controller_MBC3::init(size_t ram_size) {
	_ram_size = ram_size;
	rom_bank = (const uint8_t*)(_emu._ROM.c_str() + 0x4000);
	external_ram = (_ram_size > 0) ? new uint8_t[_ram_size] : _emu._RAM + 0xa000;
	ram_bank = external_ram;
	_RAM_ENABLE = false;
	_ROM_BANK = 1;
	_RAM_BANK = 0;
	_RAM_RTC_SELECT = E_RAM;
	_RAM_RTC_ENABLE = false;

	std::ifstream fs;
	fs.open(_emu._save_name, std::fstream::in | ios::binary);
	if (fs.is_open())
	{
		time_t last_shutdown;
		time_t old_timestamp;
		uint8_t RTC_DH;
		fs.read(reinterpret_cast<char *>(&last_shutdown), sizeof(last_shutdown));
		fs.read(reinterpret_cast<char *>(&old_timestamp), sizeof(old_timestamp));
		fs.read(reinterpret_cast<char *>(&RTC_DH), sizeof(RTC_DH));
		// printf("last_shutdown = %ld and old_timestamp = %ld\n", last_shutdown, old_timestamp);
		if (fs.good()) {
			_RTC.init_timestamp(last_shutdown, old_timestamp, RTC_DH);
			fs.read((char *)external_ram, _ram_size);
			fs.close();
		}
		else {
			_RTC.init_timestamp();
			fs.close();
		}
	}
	else
		_RTC.init_timestamp();
}

Memory_controller_MBC3::Memory_controller_MBC3(Emulateur &emu, size_t ram_size): Memory_controller(emu, ram_size)
{
	init(ram_size);
}