#include <instructions.hpp>
#include <iostream>
#include <Emulateur.hpp>

void	Emulateur::nop(struct s_params& p, int cycle)
{
	(void)p;
	this->_cycle += cycle;
}

void	Emulateur::ld(int8_t inc, void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	param1;
	struct s_param_info	param2;
	const struct s_params tmp1 = (struct s_params){ADDR_x64, UDIRECT, false, true, 2};
	const struct s_params tmp2 = (struct s_params){UDIRECT, ADDR_x64, true, false, 2};

	param1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param1, p.size);
	param2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&param2, p.size);
	this->regs.hl.HL += inc;
	if (p.size == 1
		|| (!memcmp((void *)&p, (void *)&tmp1, sizeof(p)) && (param1.rez == (uint16_t *)&regs.af.af.A))
		|| (!memcmp((void *)&p, (void *)&tmp2, sizeof(p)) && (param2.rez == (uint16_t *)&regs.af.af.A)))
		mem_write(param1.rez, mem_read(param2.rez, 1), 1);
	else if (p.size == 2)
		mem_write(param1.rez, mem_read(param2.rez, 2), 2);
	else
		exit(0);
	this->_cycle += cycle;
}

void	Emulateur::inc(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;
	uint8_t				val;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	if (p.size == 1)
	{
		this->regs.af.af.F &= ~FLAG_N;
		this->regs.af.af.F &= ~FLAG_H;
		this->regs.af.af.F &= ~FLAG_Z;
		val = mem_read(para.rez, 1);
		if ((val & 0xf) == 0xf)
			this->regs.af.af.F |= FLAG_H;
		if (val == 0xff)
			this->regs.af.af.F |= FLAG_Z;
		mem_write(para.rez, ++val, 1);
	}
	if (p.size == 2)
		mem_write(para.rez, mem_read(para.rez, 2) + 1, 2);
	this->_cycle += cycle;
}

void	Emulateur::decr(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;
	uint8_t				val;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	if (p.size == 1)
	{
		this->regs.af.af.F |= FLAG_N;
		this->regs.af.af.F &= ~FLAG_H;
		this->regs.af.af.F &= ~FLAG_Z;
		val = mem_read(para.rez, 1);
		if ((val & 0xf) == 0)
			this->regs.af.af.F |= FLAG_H;
		if (val == 0x01)
			this->regs.af.af.F |= FLAG_Z;
		mem_write(para.rez, --val, 1);
	}
	if (p.size == 2)
		mem_write(para.rez, mem_read(para.rez, 2) - 1, 2);
	this->_cycle += cycle;
}

void	Emulateur::rlca(struct s_params& p, int cycle)
{
	uint8_t				*m;

	m = &regs.af.af.A;
	*m = *m << 1 | ((*m & 0x80) >> 7);
	regs.af.af.F = (regs.af.af.F & FLAG_Z) | (*m & 0x1 ? FLAG_CY : 0);
	this->_cycle += cycle;
}

void	Emulateur::rrca(struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rla(struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rra(struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::daa(struct s_params& p, int cycle)
{
	uint8_t convert_bcd = 0;
	uint8_t deb[13][8] = {
		{0, 0, 0x0, 0x9, 0, 0x0, 0x9, 0x00},
		{0, 0, 0x0, 0x8, 0, 0xa, 0xf, 0x06},
		{0, 0, 0x0, 0x9, FLAG_H, 0x0, 0x3, 0x06},
		{0, 0, 0xa, 0xf, 0, 0x0, 0x9, 0x60},
		{0, 0, 0x9, 0xf, 0, 0xa, 0xf, 0x66},
		{0, 0, 0xa, 0xf, FLAG_H, 0x0, 0x3, 0x66},
		{0, FLAG_CY, 0x0, 0x2, 0, 0x0, 0x9, 0x60},
		{0, FLAG_CY, 0x0, 0x2, 0, 0xa, 0xf, 0x66},
		{0, FLAG_CY, 0x0, 0x3, FLAG_H, 0x0, 0x3, 0x66},
		{FLAG_N, 0, 0x0, 0x9, 0, 0x0, 0x9, 0x00},
		{FLAG_N, 0, 0x0, 0x8, FLAG_H, 0x6, 0xf, 0xfa},
		{FLAG_N, FLAG_CY, 0x7, 0xf, 0, 0x0, 0x9, 0xa0},
		{FLAG_N, FLAG_CY, 0x6, 0xf, FLAG_H, 0x6, 0xf, 0x9a}
	};
	uint8_t f;
	uint8_t ra;

	// printf("In daa\n");
	// print_regs();
	f = regs.af.af.F;
	ra = regs.af.af.A;
	if ((regs.af.af.F & FLAG_H) || (!(regs.af.af.F & FLAG_N) && (regs.af.af.A & 0x0f) > 9))
		convert_bcd |= 0x06;

	if ((regs.af.af.F & FLAG_CY) || (!(regs.af.af.F & FLAG_N) && (regs.af.af.A >> 4) > 9)) {
		convert_bcd |= 0x60;
		regs.af.af.F |= FLAG_CY;
	}

	regs.af.af.A += (regs.af.af.F & FLAG_N) ? (-convert_bcd) : convert_bcd;
	regs.af.af.F &= ~FLAG_H;
	if (regs.af.af.A == 0)
		regs.af.af.F |= FLAG_Z;
	int x;

	x = 0;
	while (x < 13)
	{
		if (deb[x][0] == (f & FLAG_N) &&
			deb[x][1] == (f & FLAG_CY) &&
			deb[x][2] <= (ra >> 4) &&
			deb[x][3] >= (ra >> 4) &&
			deb[x][4] == (f & FLAG_H) &&
			deb[x][5] <= (ra & 0xf) &&
			deb[x][6] >= (ra & 0xf) &&
			deb[x][7] == convert_bcd)
			break ;
		x++;
	}
	if (x == 13)
	{
		// print_regs();
		printf("C'est du caca debug [%hhx] | regs.PC [%hx] | _RAM[HL] = %hhx\n", convert_bcd, regs.PC, _RAM[regs.hl.HL]);
	}
	this->_cycle += cycle;
}

void	Emulateur::cpl(struct s_params& p, int cycle)
{
	regs.af.af.A = ~(regs.af.af.A);
	this->regs.af.af.F |= (FLAG_H | FLAG_N);
	this->_cycle += cycle;
}

void	Emulateur::stop(struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::halt(struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
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
	this->regs.af.af.A = mem_read(param1.rez, 1) & mem_read(param2.rez, 1);
	this->regs.af.af.F = this->regs.af.af.A ? FLAG_H : (FLAG_H | FLAG_Z);
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
	this->regs.af.af.A = mem_read(param1.rez, 1) | mem_read(param2.rez, 1);
	this->regs.af.af.F = this->regs.af.af.A ? 0 : FLAG_Z;
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
	this->regs.af.af.A = mem_read(param1.rez, 1) ^ mem_read(param2.rez, 1);
	this->regs.af.af.F = this->regs.af.af.A ? 0 : FLAG_Z;
	this->_cycle += cycle;
}

void	Emulateur::cp(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	p1;
	struct s_param_info	p2;
	uint8_t v1;
	uint8_t v2;

	p1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&p1, p.size);
	p2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&p2, p.size);
	this->regs.af.af.F = FLAG_N;
	v1 = mem_read(p1.rez, 1);
	v2 = mem_read(p2.rez, 1);
	if (v1 == v2)
		this->regs.af.af.F |= FLAG_Z;
	if (v1 < v2)
		this->regs.af.af.F |= FLAG_CY;
	if ((v1 & 0x0f) < (v2 & 0x0f))
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
	if (p.size == 2)
	{
		uint16_t v1;
		uint16_t v2;

		this->regs.af.af.F &= ~FLAG_N;
		v1 = mem_read(p1.rez, 2);
		if (p2.rez)
		{
			v2 = mem_read(p2.rez, 2);
			if ((uint32_t)v1 + (uint32_t)v2 > 0xffff)
				this->regs.af.af.F |= FLAG_CY;
			if ((v1 & 0x0fff) + (v2 & 0x0fff) > 0x0fff)
				this->regs.af.af.F |= FLAG_H;
			mem_write(p1.rez, v1 + v2, 2);
		}
		else
		{
			this->regs.af.af.F = 0;
			if ((uint32_t)v1 + (int32_t)p2.e > 0xffff)
				this->regs.af.af.F |= FLAG_CY;
			if (((v1) & 0x0fff) + (p2.e & 0x0fff) > 0x0fff)
				this->regs.af.af.F |= FLAG_H;
			mem_write_signed(p1.rez, v1 + p2.e, 2);
		}
	}
	else
	{
		uint8_t v1;
		uint8_t v2;

		// if (regs.PC == 0x168) {printf("BEGIN\n") ; print_regs();}
		v1 = mem_read(p1.rez, 1);
		v2 = mem_read(p2.rez, 1);
		this->regs.af.af.F = (uint8_t)(v1 + v2) == 0 ? FLAG_Z : 0;
		if ((uint16_t)v1 + (uint16_t)v2 > 0xff)
			this->regs.af.af.F |= FLAG_CY;
		if ((v1 & 0x0f) + (v2 & 0x0f) > 0x0f)
			this->regs.af.af.F |= FLAG_H;
		mem_write(p1.rez, v1 + v2, 1);
		// if (regs.PC == 0x168) {print_regs(); printf("END\n") ; }
	}
	this->_cycle += cycle;
}

void	Emulateur::adc(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	p1;
	struct s_param_info	p2;
	uint8_t v1;
	uint8_t v2;
	uint8_t carry;


	// if (regs.PC == 0x16c || regs.PC == 0x171) {printf("BEGIN\n") ; print_regs();}
	p1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&p1, p.size);
	p2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&p2, p.size);
	v1 = mem_read(p1.rez, 1);
	v2 = mem_read(p2.rez, 1);
	carry = regs.af.af.F & FLAG_CY ? 1 : 0;
	mem_write(p1.rez, v1 + v2 + carry, 1);
	this->regs.af.af.F = ((uint8_t)(v1 + v2 + carry) == 0) ? FLAG_Z : 0;
	if ((uint16_t)v1 + (uint16_t)v2 + carry > 0xff)
		this->regs.af.af.F |= FLAG_CY;
	if ((v1 & 0x0f) + (v2 & 0x0f) + carry > 0x0f)
		this->regs.af.af.F |= FLAG_H;
	// if (regs.PC == 0x16c || regs.PC == 0x171) {print_regs(); printf("END\n") ; }
	this->_cycle += cycle;
}

 
void	Emulateur::sub(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	struct s_param_info	p1;
	struct s_param_info	p2;
	uint8_t v1;
	uint8_t v2;

	p1 = {param_1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&p1, p.size);
	p2 = {param_2, p.param2, p.deref_param2, NULL, 0};
	this->get_params(&p2, p.size);
	v1 = mem_read(p1.rez, 1);
	v2 = mem_read(p2.rez, 1);
	this->regs.af.af.F |= FLAG_N;
	if (v1 < v2)
		this->regs.af.af.F |= FLAG_CY;
	if ((v1 & 0x0f) < (v2 & 0x0f))
		this->regs.af.af.F |= FLAG_H;
	mem_write(p1.rez, v1 - v2, 1);
	this->_cycle += cycle;
}

void	Emulateur::sbc(void *param_1, void *param_2, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
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
		exit(0);
	this->regs.PC += param.e;
	this->_cycle += 1;
}

void	Emulateur::ret(enum e_cond cond, struct s_params& p, int cycle)
{
	this->_cycle += 2;
	if (!check_rules(cond))
		return ;
	if (cond == EMPTY)
		this->_cycle -= 1;
	this->regs.PC = mem_read(this->_RAM + this->regs.SP, 2);
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
	// mem_write(this->_RAM + this->regs.SP, this->regs.PC, 2);
	this->regs.PC = mem_read(this->_RAM + this->regs.SP, 2);
	this->regs.SP += 2;
	if (_idata.routine && this->regs.PC == _idata.old_pc)
		_idata.routine = false;
	_IME = true;
	this->_cycle += cycle;
}

void	Emulateur::pop(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	mem_write(para.rez, mem_read(this->_RAM + this->regs.SP, 2), 2);
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
			p->rez = (uint16_t *)(this->_RAM + 0xFF00 + mem_read(p->rez, 1));
		else if (p->type != ADDR_x64)
			exit(0);
	}
	else
	{
		p->rez = (uint16_t *)(this->_RAM + this->regs.PC - size);
		if (p->type == DIRECT)
		{
			p->e = (int8_t)mem_read(p->rez, 1);
			p->rez = NULL;
		}
		else if (p->type == MEM_gb)
			p->rez = (uint16_t *)(this->_RAM + 0xFF00 + mem_read(p->rez, 1));
		else if (p->type != UDIRECT)
			exit(0);
	}
	if (p->deref)
		p->rez = (uint16_t *)(this->_RAM + mem_read(p->rez, 2));
}

void	Emulateur::jp(enum e_cond cond, void* param1, struct s_params& p, int cycle)
{
	this->_cycle += 3;
	struct s_param_info	param;

	if (!check_rules(cond))
		return ;
	param = {param1, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&param, p.size);
	this->regs.PC = mem_read(param.rez, 2);
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
	this->regs.PC = mem_read(param.rez, 2);
	this->regs.SP -= 2;
	this->_cycle += 3;
}

void	Emulateur::push(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	this->regs.SP -= 2;
	mem_write(this->_RAM + this->regs.SP, mem_read(para.rez, 2), 2);
	this->_cycle += cycle;
}

void	Emulateur::rst(uint8_t nb, struct s_params& p, int cycle)
{
	this->regs.SP -= 2;
	mem_write(this->_RAM + this->regs.SP, regs.PC, 2);
	regs.PC = nb * 8;
	this->_cycle += cycle;
}

void	Emulateur::ldhl(void *param1, void *param2, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rlc(void *param1, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rrc(void *param1, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rl(void *param1, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::rr(void *param1, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::sla(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;
	uint8_t				m;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	m = mem_read(para.rez, 1);
	regs.af.af.F = (regs.af.af.F & FLAG_Z) | (m & 0x80 ? FLAG_CY : 0);
	mem_write(para.rez, m << 1, 1);
	this->_cycle += cycle;
}

void	Emulateur::sra(void *param1, struct s_params& p, int cycle)
{
	printf("In %s\n", __FUNCTION__);
	exit(1);
	this->_cycle += cycle;
}

void	Emulateur::srl(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;
	uint8_t				m;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	m = mem_read(para.rez, 1);
	regs.af.af.F = (regs.af.af.F & FLAG_Z) | (m & 1 ? FLAG_CY : 0);
	mem_write(para.rez, m >> 1, 1);
	this->_cycle += cycle;
}

void	Emulateur::_swap(void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;
	uint8_t				m;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	m = mem_read(para.rez, 1);
	mem_write(para.rez, m << 4 | m >> 4, 1);
	this->regs.af.af.F = m ? 0 : FLAG_Z;
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
	if (mem_read(para.rez, 1) & (1 << bit))
		this->regs.af.af.F &= ~FLAG_Z;
	this->_cycle += cycle;
}

void	Emulateur::res(uint8_t bit, void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	mem_write(para.rez, mem_read(para.rez, 1) & ~(uint8_t)(1 << bit), 1);
	this->_cycle += cycle;
}

void	Emulateur::set(uint8_t bit, void *param, struct s_params& p, int cycle)
{
	struct s_param_info	para;

	para = {param, p.param1, p.deref_param1, NULL, 0};
	this->get_params(&para, p.size);
	mem_write(para.rez, mem_read(para.rez, 1) | (uint8_t)(1 << bit), 1);
	this->_cycle += cycle;
}

void	Emulateur::op203(struct s_params& p, int cycle)
{
	const struct s_instruction_params	*instr;

	instr = &_op203[*reinterpret_cast<uint8_t*>(this->_RAM + this->regs.PC)];
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
	mem_write(_RAM + 0xffff, 0x1f, 1);
	_idata.routine = false;
	this->_cycle += cycle;
}
