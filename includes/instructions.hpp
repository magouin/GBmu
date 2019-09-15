#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <cstdint>
# include <functional>
# include <string>

enum e_param_type
{
	REG,
	DIR,
	GB
};

enum e_type
{
	SIGN,
	UNSIGN
};

enum e_cond
{
	NZ,
	Z,
	NC,
	C,
	EMPTY
};

struct s_param {
	enum e_param_type	type;
	void				*p;
	void				*val;
	enum e_type			t;
	bool				deref;
	uint8_t				s;
	uint8_t				size;
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

struct s_instr_params {
	uint8_t				opcode;
	const std::string	mnemonic;
	uint8_t				nb_params;
	struct s_flags		flags;
	uint8_t				cycle_nb;
	t_instr f;
};

struct s_cv_instr {
	uint8_t				opcode;
	const std::string	mnemonic;
	uint8_t				cycle_true;
	uint8_t				cycle_false;
	enum e_cond			condition;
};


#endif
