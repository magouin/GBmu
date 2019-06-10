#include <instructions.hpp>
#include <iostream>

void	nop(s_emu& s, struct s_params& p)
{
	(void)s;
	std::cout << "Called nop" << std::endl;
}

void	ld(uint8_t size, struct s_inc inc, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{
	// std::cout << "Called ld(" << size <<  << std::endl;
	printf("Called ld(%d, %p, %p, s)\n", size, param_1, param_2);
}

void inc(uint8_t size, void *param, s_emu& s, struct s_params& p)
{

}

void decr(uint8_t size, void *param, s_emu& s, struct s_params& p)
{

}

void rlca(s_emu& s, struct s_params& p)
{

}

void rrca(s_emu& s, struct s_params& p)
{

}

void rla(s_emu& s, struct s_params& p)
{

}

void rra(s_emu& s, struct s_params& p)
{

}

void daa(s_emu& s, struct s_params& p)
{

}

void cpl(s_emu& s, struct s_params& p)
{

}

void stop(s_emu& s, struct s_params& p)
{

}

void halt(s_emu& s, struct s_params& p)
{

}

void	_and(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	_or(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	_xor(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	cp(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	add(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	adc(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	sub(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}

void	sbc(uint8_t size, void *param_1, void *param_2, s_emu& s, struct s_params& p)
{

}


void	jr(enum e_cond cond, s_emu& s, struct s_params& p)
{

}

void	ret(enum e_cond cond, s_emu& s, struct s_params& p)
{

}

void	reti(s_emu& s, struct s_params& p)
{

}
void	pop(void *param, s_emu& s, struct s_params& p)
{

}

void	jp(enum e_cond cond, void* param1, s_emu& s, struct s_params& p)
{

}

void	call(enum e_cond cond, s_emu& s, struct s_params& p)
{

}

void	push(void *param, s_emu& s, struct s_params& p)
{

}

void	rst(uint8_t nb, s_emu& s, struct s_params& p)
{

}

void	ldhl(uint8_t size, void *param1, void *param2, s_emu& s, struct s_params& p)
{

}
