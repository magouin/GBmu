#include "Disassembler.hpp"

Disassembler::Disassembler()
{
}

Disassembler::Disassembler(const Disassembler & cp) : _file(cp._file)
{
}

Disassembler::~Disassembler()
{
}

Disassembler &	Disassembler::operator=(const Disassembler & cp)
{
	(void)cp;
	return (*this);
}
