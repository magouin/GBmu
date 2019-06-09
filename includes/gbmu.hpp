#ifndef GBMU_H
# define GBMU_H


# include <iostream>
# include <string>
# include <fstream>
# include <sstream>

# include <Header.hpp>


using namespace std;

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
};

extern struct s_instruction_params g_op203[256];
extern struct s_instruction_params g_opcode[256];


#endif
