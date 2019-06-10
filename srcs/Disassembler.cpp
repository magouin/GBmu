#include <Disassembler.hpp>

Disassembler::Disassembler(const string & file) : _file(file), _header(Header(file))
{
}

Disassembler::Disassembler(const Disassembler & cp) : _file(cp._file), _header(Header(cp._file))
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

void			Disassembler::disassemble(uint32_t offset)
{
	uint32_t x;
	const struct s_instruction_params *instr;

	x = offset;
	while (x < _file.size())
	{
		instr = &g_opcode[static_cast<const uint8_t>(_file[x])];
		if (_file[x] == static_cast<const char>(203))
		{
			x++;
			instr = &g_op203[static_cast<const uint8_t>(_file[x])];
		}
		std::cout << instr->mnemonic;
		if (instr->nb_params == 1)
		{
			x++;
			printf(" %#04x\n", static_cast<const uint8_t>(_file[x]));
		}
		else if (instr->nb_params == 2)
		{
			x++;
			printf(" %#06hX\n", *reinterpret_cast<const uint16_t *>(_file .c_str() + x));
			x++;
		}
		else
			printf("\n");
		x++;
	}
}
