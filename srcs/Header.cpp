#include <Header.hpp>

const string Header::cartridge_types[] = {"ROM ONLY","MBC1","MBC1+RAM","MBC1+RAM+BATTERY","","MBC2","MBC2+BATTERY","","ROM+RAM","ROM+RAM+BATTERY","",
										  "MMM01","MMM01+RAM","MMM01+RAM+BATTERY","","MBC3+TIMER+BATTERY","MBC3+TIMER+RAM+BATTERY","MBC3","MBC3+RAM",
										  "MBC3+RAM+BATTERY","","","","","","MBC5","MBC5+RAM","MBC5+RAM+BATTERY","MBC5+RUMBLE","MBC5+RUMBLE+RAM",
										  "MBC5+RUMBLE+RAM+BATTERY","","MBC6","","MBC7+SENSOR+RUMBLE+RAM+BATTERY","","","","","","","","","","","",
										  "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
										  "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
										  "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
										  "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
										  "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
										  "","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
										  "POCKET CAMERA","BANDAI TAMA5","HuC3","HuC1+RAM+BATTERY"};

Header::Header()
{
}

Header::Header(const string & file) : _file(file)
{
	const char	*str;
	const char	*head;

	str = file.c_str();
	head = str + 0x100;

	_header = *reinterpret_cast<const struct s_header*>(head);

	// cout << "Title: " << this->_header.title << endl;
	// cout << "Cartdrige type: " << cartridge_types[(int)this->_header.cartridge] << endl;

	// this->_header.entrypoint = endian_conv_32(this->_header.entrypoint);
	// this->read_instr(0x150);
}

Header::Header(const Header & cp) : _file(cp._file)
{
	(void)cp;
}

Header::~Header()
{
}

void		Header::read_instr(size_t offset)
{
	(void)offset;
}

Header &	Header::operator=(const Header & cp)
{
	(void)cp;
	return (*this);
}

size_t		Header::get_ram_size() const
{
	if (_header.ram_size == 0)
		return (0);
	else if (_header.ram_size == 1)
		return (2 * 1024);
	else if (_header.ram_size == 2)
		return (8 * 1024);
	else if (_header.ram_size == 3)
		return (32 * 1024);
	else if (_header.ram_size == 4)
		return (128 * 1024);
	else if (_header.ram_size == 5)
		return (64 * 1024);
	printf("Error: Invalid ram_size in header\n");
	return (0);
}
