#ifndef EMULATEUR_HPP
# define EMULATEUR_HPP

# include <string>
# include <iostream>
# include <instructions.hpp>

# define FLAG_Z  (1 << 7)
# define FLAG_N  (1 << 6)
# define FLAG_H  (1 << 5)
# define FLAG_CY (1 << 4)

# define TYPE_FROM_SIZE(size) (size == 1 ? (uint8_t) : (uint16_t))

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
};

struct s_param_info
{
	void				*param;
	enum e_param_type	type;
	bool				deref;
	uint16_t			*rez;
	int8_t				e;
};

class Emulateur {
	private:
		std::string	_ROM;
		uint8_t		_RAM[0x10000];
		Emulateur & operator=(const Emulateur & cp);
		Emulateur(const Emulateur & cp);

void	get_params(struct s_param_info *p, uint8_t size);


	public:
		static const struct s_instruction_params g_op203[256];
		static const struct s_instruction_params g_opcode[256];

		Emulateur();
		Emulateur(std::string rom);
		~Emulateur(/* args */);

		void emu_start(uint32_t begin, uint32_t end);
		void set_rom(std::string rom);

		struct s_regs regs;

		void	nop(struct s_params& p);
		void	ld(struct s_inc inc, void *param_1, void *param_2, struct s_params& p);
		void	inc(void *param, struct s_params& p);
		void	decr(void *param, struct s_params& p);
		void	rlca(struct s_params& p);
		void	rla(struct s_params& p);
		void	rrca(struct s_params& p);
		void	rra(struct s_params& p);
		void	daa(struct s_params& p);
		void	cpl(struct s_params& p);
		void	stop(struct s_params& p);
		void	halt(struct s_params& p);
		void	_and(void *param_1, void *param_2, struct s_params& p);
		void	_or(void *param_1, void *param_2, struct s_params& p);
		void	_xor(void *param_1, void *param_2, struct s_params& p);
		void	cp(void *param_1, void *param_2, struct s_params& p);
		void	add(void *param_1, void *param_2, struct s_params& p);
		void	adc(void *param_1, void *param_2, struct s_params& p);
		void	sub(void *param_1, void *param_2, struct s_params& p);
		void	sbc(void *param_1, void *param_2, struct s_params& p);
		void	jr(enum e_cond cond, struct s_params& p);

		void	jp(enum e_cond cond, void *param_1, struct s_params& p);

		void	ret(enum e_cond cond, struct s_params& p);
		void	reti(struct s_params& p);
		void	pop(void *param, struct s_params& p);
		void	push(void *param, struct s_params& p);
		void	call(enum e_cond cond, struct s_params& p);
		void	rst(uint8_t nb, struct s_params& p);

		void	ldhl(void *param1, void *param2, struct s_params& p);

		void	rlc(void *param1, struct s_params& p);
		void	rrc(void *param1, struct s_params& p);
		void	rl(void *param1, struct s_params& p);
		void	rr(void *param1, struct s_params& p);
		void	sla(void *param1, struct s_params& p);
		void	sra(void *param1, struct s_params& p);
		void	srl(void *param1, struct s_params& p);
		void	_swap(void *param1, struct s_params& p);
		void	bit(uint8_t bit, void *param1, struct s_params &p);
		void	res(uint8_t bit, void *param1, struct s_params &p);
		void	set(uint8_t bit, void *param1, struct s_params &p);
};

#endif
