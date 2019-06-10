#include <instructions.hpp>
#include <iostream>
#include <Emulateur.hpp>

void	Emulateur::nop(struct s_params& p)
{
	printf("<<< %s >>>\n", __FUNCTION__);
}

void	Emulateur::ld(uint8_t size, struct s_inc inc, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
	printf("Called ld(%d, %p, %p, s)\n", size, param_1, param_2);
}

void	Emulateur::inc(uint8_t size, void *param, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::decr(uint8_t size, void *param, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rlca(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rrca(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rla(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rra(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::daa(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::cpl(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::stop(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::halt(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::_and(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::_or(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::_xor(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::cp(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::add(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::adc(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::sub(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::sbc(uint8_t size, void *param_1, void *param_2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}


void	Emulateur::jr(enum e_cond cond, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::ret(enum e_cond cond, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::reti(struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}
void	Emulateur::pop(void *param, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

uint16_t	get_value_from_size(uint16_t *ptr, uint8_t size)
{
	if (size == 1)
		return (*(uint8_t *)ptr);
	else if (size == 2)
		return (*(uint16_t *)ptr);
	else
	{
		printf("Invalid parameter 1's size\n");
		exit(0);
	}
}

void	Emulateur::get_params(struct s_param_info *p, uint8_t size)
{
	if (p->type == NO_PARAM)
		return ;
	if (p->param)
	{
		p->rez = (uint16_t *)p->param;
		if (p->type == MEM_gb)
			p->rez = (uint16_t *)(this->_RAM + 0xFF00 + *(uint8_t *)p->rez);
		else if (p->type != ADDR_x64)
		{
			printf("Invalid parameter 1's TYPE\n");
			exit(0);
		}
	}
	else
	{
		p->rez = (uint16_t *)(this->_RAM + this->regs.PC - size);
		if (p->type == DIRECT)
		{
			p->rez = NULL;
			p->e = *(int8_t *)p->rez;
		}
		else if (p->type != UDIRECT)
		{
			printf("Invalid parameter 1's TYPE\n");
			exit(0);
		}
	}
	if (p->deref)
		p->rez = (uint16_t *)(this->_RAM + *(p->rez));
}

void	Emulateur::jp(enum e_cond cond, void* param1, struct s_params& p)
{
	struct s_param_info	param;

	if ((cond == NZ && ((this->regs.af.af.F & FLAG_Z) != 0)) ||
		(cond == Z && ((this->regs.af.af.F & FLAG_Z) == 0)) ||
		(cond == NC && ((this->regs.af.af.F & FLAG_CY) != 0)) ||
		(cond == Z && ((this->regs.af.af.F & FLAG_CY) == 0)))
		return ;
	param.param = param1;
	param.type = p.param1;
	param.deref = p.deref_param1;
	param.size = p.size;
	this->get_params(&param, 2);
	printf("JP 0x%x\n", *param.rez);
	this->regs.PC = *(param.rez);
}

void	Emulateur::call(enum e_cond cond, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::push(void *param, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rst(uint8_t nb, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::ldhl(uint8_t size, void *param1, void *param2, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rlc(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rrc(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rl(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::rr(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::sla(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::sra(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::srl(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::_swap(void *param1, struct s_params& p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::bit(uint8_t bit, void *param1, struct s_params &p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::res(uint8_t bit, void *param1, struct s_params &p)
{
	printf("In %s\n", __FUNCTION__);
}

void	Emulateur::set(uint8_t bit, void *param1, struct s_params &p)
{
	printf("In %s\n", __FUNCTION__);
}
