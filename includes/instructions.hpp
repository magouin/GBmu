#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <cstdint>
# include <functional>
# include <string>

enum e_param_type
{
	ADDR_x64,
	UDIRECT,
	DIRECT,
	MEM_gb,
	NO_PARAM
};

enum e_cond
{
	NZ,
	Z,
	NC,
	C,
	EMPTY
};

struct s_params {
	enum e_param_type	param1;
	enum e_param_type	param2;
	bool				deref_param1;
	bool				deref_param2;
	uint8_t				size;
	// Magouin: "Y en n'a jamais plus que deux", le 09/06/19
	// Paris de cafe lance par jeremy

	// Second paris de cafe lance par maxime, quant a l'inexistence de trucs avec deux n qui ne soient pas des nn. (Ca veut dire quelque chose, promis.)
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

typedef std::function<void(void)> t_instr;

struct s_instruction_params {
	uint8_t				opcode;
	const std::string	mnemonic;
	uint8_t				nb_params;
	struct s_flags		flags;

	t_instr f;
};



#endif
