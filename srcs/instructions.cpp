#include <instructions.hpp>
#include <iostream>
#include <Emulateur.hpp>

void	Emulateur::nop(struct s_params& p, int cycle)
{
	(void)p;
	#ifdef DEBUG
		// std::cout << "...";
	#endif
	this->_cycle += cycle;
}

void	Emulateur::ld(int8_t inc, void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	param1;
	struct s_param_info	param2;

	param1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param1, p.size);
	param2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&param2, p.size);
	this->regs.hl.HL += inc;
	if (p.size == 1)
	{
		*((uint8_t *)param1.rez) = *((uint8_t *)param2.rez);
		#ifdef DEBUG
			// std::cout << "*(" << param1.rez << ") = 0x" << (int)*((uint8_t *)param2.rez);
		#endif
	}
	else if (p.size == 2)
	{
		*(param1.rez) = *(param2.rez);
		#ifdef DEBUG
			// std::cout << "*(" << param1.rez << ") = 0x" << *(param2.rez);
		#endif
	}
	else
	{
		// printf("Il y un problem\n");
		exit(0);
	}
	this->_cycle += cycle;
}

void	Emulateur::inc(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	if (p.size == 1)
	{
		#ifdef DEBUG
			// printf("param = 0x%x", *((uint8_t *)para.rez) + 1);
		#endif
		this->regs.af.af.F &= ~FLAG_N;
		this->regs.af.af.F &= ~FLAG_Z;
		this->regs.af.af.F &= ~FLAG_H;
		if (((*(uint8_t *)para.rez) & ((1 << 4) - 1)) == ((1 << 4) - 1))
		{
			this->regs.af.af.F |= FLAG_H;
			#ifdef DEBUG
				// printf(" | FLAG_H");
			#endif
		}
		if (*(uint8_t *)para.rez == 0xff)
		{
			this->regs.af.af.F |= FLAG_Z;
			#ifdef DEBUG
				// printf(" | FLAG_Z");
			#endif
		}
		(*(uint8_t *)para.rez)++;
	}
	if (p.size == 2)
	{
		(*(uint16_t *)para.rez)++;
		#ifdef DEBUG
			// printf("param = 0x%x", *(uint16_t *)para.rez);
		#endif
	}
	this->_cycle += cycle;
}

void	Emulateur::decr(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	if (p.size == 1)
	{
		#ifdef DEBUG
			// printf("param = 0x%x", *((uint8_t *)para.rez) - 1);
		#endif
		this->regs.af.af.F |= FLAG_N;
		this->regs.af.af.F &= ~FLAG_Z;
		this->regs.af.af.F &= ~FLAG_H;
		if (((*(uint8_t *)para.rez) & ((1 << 4) - 1)) == 0)
		{
			this->regs.af.af.F |= FLAG_H;
			#ifdef DEBUG
				// printf(" | FLAG_H");
			#endif
		}
		if (*(uint8_t *)para.rez == 0x01)
		{
			this->regs.af.af.F |= FLAG_Z;
			#ifdef DEBUG
				// printf(" | FLAG_Z");
			#endif
		}
		(*(uint8_t *)para.rez)--;
	}
	if (p.size == 2)
	{
		(*(uint16_t *)para.rez)--;
		#ifdef DEBUG
			// printf("param = 0x%x", *(uint16_t *)para.rez);
		#endif
	}
	this->_cycle += cycle;
}

void	Emulateur::rlca(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rrca(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rla(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rra(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::daa(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::cpl(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::stop(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::halt(struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::_and(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	param1;
	struct s_param_info	param2;

	param1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param1, p.size);
	param2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&param2, p.size);
	if ((void*)&this->regs.af.af.A != (void*)param1.rez)
	{
		// printf("C'est pas normal ...\n");
		exit(0);
	}
	this->regs.af.af.A = *(param1.rez) & *((uint8_t *)param2.rez);
	this->regs.af.af.F = this->regs.af.af.A ? FLAG_H : (FLAG_H | FLAG_Z);
	#ifdef DEBUG
		// std::cout << "A &= 0x" << (int)*((uint8_t *)param2.rez) << " - F = 0x" << (int)this->regs.af.af.F;
	#endif
	this->_cycle += cycle;
}

void	Emulateur::_or(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	param1;
	struct s_param_info	param2;

	param1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param1, p.size);
	param2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&param2, p.size);
	if ((void*)&this->regs.af.af.A != (void*)param1.rez)
	{
		// printf("C'est pas normal ...\n");
		exit(0);
	}
	this->regs.af.af.A = *(param1.rez) | *((uint8_t *)param2.rez);
	this->regs.af.af.F = this->regs.af.af.A ? 0 : FLAG_Z;
	#ifdef DEBUG
		// std::cout << "A |= 0x" << (int)*((uint8_t *)param2.rez) << " - F = 0x" << (int)this->regs.af.af.F;
	#endif
	this->_cycle += cycle;
}

void	Emulateur::_xor(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	param1;
	struct s_param_info	param2;

	param1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param1, p.size);
	param2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&param2, p.size);
	if ((void*)&this->regs.af.af.A != (void*)param1.rez)
	{
		// printf("C'est pas normal ...\n");
		exit(0);
	}
	this->regs.af.af.A = *(param1.rez) ^ *((uint8_t *)param2.rez);
	this->regs.af.af.F = this->regs.af.af.A ? 0 : FLAG_Z;
	#ifdef DEBUG
		// std::cout << "A ^= 0x" << (int)*((uint8_t *)param2.rez) << " - F = 0x" << (int)this->regs.af.af.F;
	#endif
	this->_cycle += cycle;
}

void	Emulateur::cp(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	p1;
	struct s_param_info	p2;

	p1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&p1, p.size);
	p2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&p2, p.size);
	this->regs.af.af.F = FLAG_N;
	if (p1.rez != (uint16_t *)&(this->regs.af.af.A))
	{
		// printf("Il y a un probleme\n");
		exit(0);
	}
	if (*(uint8_t *)p1.rez == *(uint8_t *)p2.rez)
		this->regs.af.af.F |= FLAG_Z;
	if (*(uint8_t *)p1.rez < *(uint8_t *)p2.rez)
		this->regs.af.af.F |= FLAG_CY;
	if ((*(uint8_t *)p1.rez & 0x0f) < (*(uint8_t *)p2.rez & 0x0f))
		this->regs.af.af.F |= FLAG_H;
	this->_cycle += cycle;
}

void	Emulateur::add(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	p1;
	struct s_param_info	p2;

	p1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&p1, p.size);
	p2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&p2, p.size);
	if (!p2.rez)
	{
		this->regs.af.af.F &= ~FLAG_N;
		if ((uint32_t)*(uint16_t *)p1.rez + (uint32_t)*(uint16_t *)p2.rez > 0xffff)
			this->regs.af.af.F |= FLAG_CY;
		if (((*(uint16_t *)p1.rez) & 0x0fff) + ((*(uint16_t *)p2.rez) & 0x0fff) > 0x0fff)
			this->regs.af.af.F |= FLAG_H;
		*(uint16_t *)p1.rez = *(uint16_t *)p2.rez;
	}
	else
	{
		this->regs.af.af.F = 0;
		if ((uint32_t)*(uint16_t *)p1.rez + (uint32_t)p2.e > 0xffff)
			this->regs.af.af.F |= FLAG_CY;
		if (((*(uint16_t *)p1.rez) & 0x0fff) + (p2.e & 0x0fff) > 0x0fff)
			this->regs.af.af.F |= FLAG_H;
		*(uint16_t *)p1.rez = (int16_t)p2.e;
	}
	this->_cycle += cycle;
}

void	Emulateur::adc(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::sub(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::sbc(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

bool	Emulateur::check_rules(enum e_cond cond)
{
	if ((cond == NZ && ((this->regs.af.af.F & FLAG_Z) != 0)) ||
		(cond == Z && ((this->regs.af.af.F & FLAG_Z) == 0)) ||
		(cond == NC && ((this->regs.af.af.F & FLAG_CY) != 0)) ||
		(cond == C && ((this->regs.af.af.F & FLAG_CY) == 0)))
		return (false);
	return (true);
}

void	Emulateur::jr(enum e_cond cond, struct s_params& p, int cycle)
{
	struct s_param_info	param;

	this->_cycle += 2;
	if (!check_rules(cond))
		return ;
	param = {NULL, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param, p.size);
	if (param.rez)
	{
		// printf("problem ...\n");
		exit(0);
	}
	#ifdef DEBUG
		// printf("add %hd at PC = 0x%hx", param.e, this->regs.PC);
	#endif
	this->regs.PC += param.e;
	#ifdef DEBUG
		// printf(" -> 0x%hx", this->regs.PC);
	#endif
	this->_cycle += 1;
}

void	Emulateur::ret(enum e_cond cond, struct s_params& p, int cycle)
{
	this->_cycle += 2;
	if (!check_rules(cond))
		return ;
	this->regs.PC = *(uint16_t *)(this->_RAM + this->regs.SP);
	this->regs.SP += 2;
	if (_idata.routine && this->regs.PC == _idata.old_pc)
	{
		_idata.routine = false;
		_IME = false;
	}
	this->_cycle += 3;
}

void	Emulateur::reti(struct s_params& p, int cycle)
{
	this->_cycle += cycle;
	*(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.PC;
	this->regs.SP += 2;
	if (_idata.routine && this->regs.PC == _idata.old_pc)
		_idata.routine = false;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.hl.HL;
	// this->regs.SP += 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.de.DE;
	// this->regs.SP += 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.bc.BC;
	// this->regs.SP += 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.af.AF;
	// this->regs.SP += 2;
	_IME = true;
}
void	Emulateur::pop(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	*(para.rez) = *(uint16_t *)(this->_RAM + this->regs.SP);
	#ifdef DEBUG
		// std::cout << "Pop de 0x" << *((uint16_t *)para.rez) << " a SP = 0x" << this->regs.SP;
	#endif
	this->regs.SP += 2;
	this->_cycle += cycle;
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
			// printf("Invalid parameter 1's TYPE\n");
			exit(0);
		}
	}
	else
	{
		p->rez = (uint16_t *)(this->_RAM + this->regs.PC - size);
		if (p->type == DIRECT)
		{
			p->e = (int16_t)*(int8_t *)p->rez;
			p->rez = NULL;
		}
		else if (p->type == MEM_gb)
			p->rez = (uint16_t *)(this->_RAM + 0xFF00 + *(uint8_t *)p->rez);
		else if (p->type != UDIRECT)
		{
			// printf("Invalid parameter 1's TYPE -- PARAM == NULL\n");
			exit(0);
		}
	}
	if (p->deref)
		p->rez = (uint16_t *)(this->_RAM + *(p->rez));
}

void	Emulateur::jp(enum e_cond cond, void* param1, struct s_params& p, int cycle)
{
	this->_cycle += 3;
	struct s_param_info	param;

	if (!check_rules(cond))
		return ;
	param = {param1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param, p.size);
	this->regs.PC = *(param.rez);
	#ifdef DEBUG
		// std::cout << "jp 0x" << std::hex << *(param.rez);
	#endif
	this->_cycle += 1;
}

void	Emulateur::call(enum e_cond cond, struct s_params& p, int cycle)
{
	struct s_param_info	param;

	this->_cycle += 3;
	if (!check_rules(cond))
		return ;
	param = {NULL, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param, p.size);
	*(uint16_t *)(this->_RAM + this->regs.SP - 2) = this->regs.PC;
	this->regs.PC = *(param.rez);
	this->regs.SP -= 2;
	#ifdef DEBUG
		// std::cout << "SP = 0x" << this->regs.SP << " -- NEW PC = 0x" << this->regs.PC << " -- OLD PC = 0x" << (int)*(uint16_t *)(this->_RAM + this->regs.SP);
	#endif
	this->_cycle += 3;
}

void	Emulateur::push(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	this->regs.SP -= 2;
	*(uint16_t *)(this->_RAM + this->regs.SP) = *(uint16_t *)(para.rez);
	#ifdef DEBUG
		// std::cout << "Push de 0x" << *(para.rez) << " a SP = 0x" << this->regs.SP;
	#endif
	this->_cycle += cycle;
}

void	Emulateur::rst(uint8_t nb, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::ldhl(void *param1, void *param2, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rlc(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rrc(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rl(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rr(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::sla(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::sra(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::srl(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::_swap(void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::bit(uint8_t bit, void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	this->regs.af.af.F |= FLAG_H;
	this->regs.af.af.F &= ~FLAG_N;
	this->regs.af.af.F |= FLAG_Z;
	if (*para.rez & (1 << bit))
		this->regs.af.af.F &= ~FLAG_Z;
	this->_cycle += cycle;
}

void	Emulateur::res(uint8_t bit, void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	*(uint8_t *)(para.rez) &= ~(uint8_t)(1 << bit);
	this->_cycle += cycle;
}

void	Emulateur::set(uint8_t bit, void *param1, struct s_params& p, int cycle)
{
	// printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::op203(struct s_params& p, int cycle)
{
	const struct s_instruction_params	*instr;

	instr = &g_op203[*reinterpret_cast<uint8_t*>(this->_RAM + this->regs.PC)];
	#ifdef DEBUG
		// std::cout << instr->mnemonic;
	#endif
	this->regs.PC += 1 + instr->nb_params * 1;
	instr->f();
	this->_cycle += cycle;
}

void	Emulateur::di(struct s_params& p, int cycle)
{
	(void)p;
	_IME = false;
	this->_cycle += cycle;
}

void	Emulateur::ei(struct s_params& p, int cycle)
{
	(void)p;

	_IME = true;
	_RAM[0xffff] = 0x1f;
	this->_cycle += cycle;
	_idata.routine = false;
}
