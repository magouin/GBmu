#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <cstdint>
# include <functional>

struct s_regs {

	union u_AF {
		struct s_AF {
			uint8_t A;
			uint8_t F;
		} af;
		uint16_t AF;
	} af;

	union u_BC {
		struct s_BC {
			uint8_t B;
			uint8_t C;
		} bc;
		uint16_t BC;
	} bc;

	union u_DE {
		struct s_DE {
			uint8_t D;
			uint8_t E;
		} de;
		uint16_t DE;
	} de;

	union u_HL {
		struct s_HL {
			uint8_t H;
			uint8_t L;
		} hl;
		uint16_t HL;
	} hl;

	uint16_t SP;
	uint16_t PC;

}; // packed

struct s_emu {
	struct s_regs regs;
};

extern struct s_emu emu;

enum e_param_type
{
	ADDR_gb,
	ADDR_x64,
	UDIRECT,
	DIRECT,
	MEM_gb,
	NOTHING,
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
	uint8_t				nn_index_params;
	// Magouin: "Y en n'a jamais plus que deux", le 09/06/19
	// Paris de cafe lance par jeremy

	// Second paris de cafe lance par maxime, quant a l'inexistence de trucs avec deux n qui ne soient pas des nn. (Ca veut dire quelque chose, promis.)
};

struct s_inc
{
	int8_t inc_param1;
	int8_t inc_param2;
};

// typedef void (*t_instr)(s_emu& s);

typedef std::function<void(s_emu&)> t_instr;

void	nop(s_emu& s, struct s_params& p);
void	ld(uint8_t size, struct s_inc inc, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	inc(uint8_t size, void *param, s_emu& s, struct s_params& p);
void	decr(uint8_t size, void *param, s_emu& s, struct s_params& p);
void	rlca(s_emu& s, struct s_params& p);
void	rla(s_emu& s, struct s_params& p);
void	rrca(s_emu& s, struct s_params& p);
void	rra(s_emu& s, struct s_params& p);
void	daa(s_emu& s, struct s_params& p);
void	cpl(s_emu& s, struct s_params& p);
void	stop(s_emu& s, struct s_params& p);
void	halt(s_emu& s, struct s_params& p);
void	_and(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	_or(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	_xor(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	cp(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	add(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	adc(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	sub(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	sbc(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p);
void	jr(enum e_cond cond, s_emu& s, struct s_params& p);

void	jp(enum e_cond cond, void *param_1, s_emu& s, struct s_params& p);

void	ret(enum e_cond cond, s_emu& s, struct s_params& p);
void	reti(s_emu& s, struct s_params& p);
void	pop(void *param, s_emu& s, struct s_params& p);
void	push(void *param, s_emu& s, struct s_params& p);
void	call(enum e_cond cond, s_emu& s, struct s_params& p);
void	rst(uint8_t nb, s_emu& s, struct s_params& p);

void	ldhl(uint8_t size, void *param1, void *param2, s_emu& s, struct s_params& p);

void	rlc(void *param1, s_emu& s, struct s_params& p);
void	rrc(void *param1, s_emu& s, struct s_params& p);
void	rl(void *param1, s_emu& s, struct s_params& p);
void	rr(void *param1, s_emu& s, struct s_params& p);
void	sla(void *param1, s_emu& s, struct s_params& p);
void	sra(void *param1, s_emu& s, struct s_params& p);
void	srl(void *param1, s_emu& s, struct s_params& p);
void	_swap(void *param1, s_emu& s, struct s_params& p);

void	bit(uint8_t bit, void *param1, s_emu& s, struct s_params &p);
void	res(uint8_t bit, void *param1, s_emu& s, struct s_params &p);
void	set(uint8_t bit, void *param1, s_emu& s, struct s_params &p);
#endif
