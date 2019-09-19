#include <Header.hpp>

const struct s_cartridge Header::cartridge_types[] = {CARTRIDGE_TYPE};

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
	// cout << "Cartdrige type: " << cartridge_types[(int)this->_header.cartridge].to_str << endl;

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

const struct s_cartridge *Header::get_cartridge_type() const
{
	uint16_t i = 0;
	while (i < 257) {
		if (cartridge_types[i].id == (int)this->_header.cartridge)
			return (&cartridge_types[i]);
		i++;
	}
	printf("Wrong cartridge type\n");
	exit(EXIT_FAILURE);
	// return (0);
}