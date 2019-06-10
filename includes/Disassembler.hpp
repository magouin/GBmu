#ifndef DISASSEMBLER_HPP
# define DISASSEMBLER_HPP

# include <Header.hpp>
# include <iostream>
# include <string>
# include <instructions.hpp>

using namespace std;

class Disassembler {
	private:
		const string & _file;
		const Header _header;
		Disassembler();
		Disassembler & operator=(const Disassembler & cp);
	public:
		Disassembler(const string & file);
		Disassembler(const Disassembler & cp);
		~Disassembler();

		void disassemble(uint32_t offset);
};

enum e_flags_modif {
	_,
	SET_1,
	SET_0,
	SET
};

struct s_flags {
	enum e_flags_modif	cy;
	enum e_flags_modif	h;
	enum e_flags_modif	n;
	enum e_flags_modif	z;

};

struct s_instruction_params {
	uint8_t				opcode;
	const std::string	mnemonic;
	uint8_t				nb_params;
	struct s_flags		flags;
	uint8_t				cycle;

	t_instr f;
};

extern const struct s_instruction_params g_op203[256];
extern const struct s_instruction_params g_opcode[256];

#endif
