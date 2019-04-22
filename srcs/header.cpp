#include "Header.hpp"

Header::Header(const string & file) : _file(file)
{
	const char	*str;
	const char	*head;

	str = file.c_str();
	head = str + 0x100;

	this->_header = reinterpret_cast<const struct s_header*>(head);
	cout << this->_header->title << endl;
	cout << "0x" << setw(2) << setfill('0') << hex << (int)this->_header->cartridge << endl;
}

Header::Header(const Header & cp) : _file(cp._file)
{
	(void)cp;
}

Header::~Header()
{
}

Header &	Header::operator=(const Header & cp)
{
	(void)cp;
	return (*this);
}
