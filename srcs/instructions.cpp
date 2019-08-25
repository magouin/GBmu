#include <instructions.hpp>
#include <iostream>
#include <Emulateur.hpp>

void	Emulateur::nop(int cycle)
{
	_cycle += cycle;
}

void	Emulateur::ld(struct s_param *p1, struct s_param *p2, int8_t inc, int size, int cycle)
{
	get_param(p1);
	get_param(p2);
	regs.HL += inc;
	mem_write(p1->val, mem_read(p2->val, size), size);
	_cycle += cycle;
}

void	Emulateur::inc(struct s_param *p, int cycle)
{
	uint16_t val;

	get_param(p);
	val = mem_read(p->val, p->size);
	if (p->size == 1)
	{
		regs.N = false;
		regs.HC = (val == 0xf);
		regs.Z = (val == 0xff);
	}
	mem_write(p->val, val + 1, p->size);
	_cycle += cycle;
}

void	Emulateur::dec(struct s_param *p, int cycle)
{
	uint16_t val;

	get_param(p);
	val = mem_read(p->val, p->size);
	if (p->size == 1)
	{
		regs.N = true;
		regs.HC = (val == 0x10);
		regs.Z = (val == 1);
	}
	mem_write(p->val, val - 1, p->size);
	_cycle += cycle;
}

void	Emulateur::rlca(int cycle)
{
	uint8_t				*m;

	m = &regs.A;
	regs.F = 0;
	regs.CY = (*m & 0x80);
	*m = (*m << 1) | (*m >> 7);
	_cycle += cycle;
}

void	Emulateur::rrca(int cycle)
{
	uint8_t				*m;

	m = &regs.A;
	regs.F = 0;
	regs.CY = (*m & 1);
	*m = (*m >> 1) | (*m << 7);
	_cycle += cycle;
}

void	Emulateur::rla(int cycle)
{
	uint8_t				*m;
	bool				tmp;

	m = &regs.A;
	tmp = regs.CY;
	regs.F = 0;
	regs.CY = *m & 0x80;
	*m = (*m << 1) | tmp;
	_cycle += cycle;
}

void	Emulateur::rra(int cycle)
{
	uint8_t				*m;
	bool				tmp;

	m = &regs.A;
	tmp = regs.CY;
	regs.F = 0;
	regs.CY = *m & 1;
	*m = (*m >> 1) | (tmp << 7);
	_cycle += cycle;
}

void	Emulateur::daa(int cycle)
{
	uint8_t convert_bcd = 0;

	regs.CY = false;
	if ((regs.F & FLAG_H) || (!(regs.F & FLAG_N) && (regs.A & 0x0f) > 9))
		convert_bcd |= 0x06;
	if ((regs.F & FLAG_CY) || (!(regs.F & FLAG_N) && (regs.A >> 4) > 9))
	{
		convert_bcd |= 0x60;
		regs.CY = true;
	}
	regs.A += (regs.F & FLAG_N) ? (-convert_bcd) : convert_bcd;
	regs.HC = false;
	regs.Z = (regs.A == 0);
	_cycle += cycle;
}

void	Emulateur::cpl(int cycle)
{
	regs.A = ~(regs.A);
	regs.HC = true;
	regs.N = true;
	_cycle += cycle;
}

void	Emulateur::stop(int cycle) // TODO
{
	while ((_input.p14 & 0xf) != 0xf || (_input.p15 & 0xf) != 0xf) ;
	_stop_status = true;
	_cycle += cycle;
}

void	Emulateur::halt(int cycle) // TODO
{
	_halt_status = true;
	_cycle += cycle;
}

void	Emulateur::_and(struct s_param *p, int cycle)
{
	get_param(p);
	regs.A = regs.A & mem_read(p->val, 1);
	regs.F = FLAG_H;
	regs.Z = regs.A ? false : true;
	_cycle += cycle;
}

void	Emulateur::_or(struct s_param *p, int cycle)
{
	get_param(p);
	regs.A = regs.A | mem_read(p->val, 1);
	regs.F = regs.A ? 0 : FLAG_Z;
	_cycle += cycle;
}

void	Emulateur::_xor(struct s_param *p, int cycle)
{
	get_param(p);
	regs.A = regs.A ^ mem_read(p->val, 1);
	regs.F = regs.A ? 0 : FLAG_Z;
	_cycle += cycle;
}

void	Emulateur::cp(struct s_param *p, int cycle)
{
	uint8_t v;

	get_param(p);
	regs.N = true;
	v = mem_read(p->val, 1);
	regs.Z = (regs.A == v);
	regs.CY = (regs.A < v);
	regs.HC = ((regs.A & 0xf) > (v & 0xf));
	_cycle += cycle;
}

void	Emulateur::add(struct s_param *p1, struct s_param *p2, int size, int cycle)
{
	uint16_t	v1;
	uint16_t	v2;
	uint32_t	val;
	uint16_t	H_val;
	uint16_t	CY_val;

	get_param(p1);
	get_param(p2);
	v1 = mem_read(p1->val, p1->size);
	v2 = mem_read(p2->val, p2->size);
	val = v1 + ((p2->t == SIGN) ? (int8_t)v2 : v2);
	H_val = (size == 2 ? 0xfff : 0xf);
	CY_val = (size == 2 ? 0xffff : 0xff);
	regs.N = false;
	regs.Z = (size == 1) ? !val : regs.Z;
	regs.Z = (p2->t == SIGN) ? false : regs.Z;
	regs.CY = (val > CY_val);
	regs.HC = ((v1 & H_val) + (v2 & H_val) > H_val);
	mem_write(p1->val, val, size);
	_cycle += cycle;
}

void	Emulateur::adc(struct s_param *p, int cycle)
{
	uint8_t v1;
	uint8_t v2;
	uint8_t val;
	bool carry;

	get_param(p);
	v1 = regs.A;
	v2 = mem_read(p->val, 1);
	carry = regs.CY;
	val = v1 + v2 + carry;
	regs.F = val ? 0 : FLAG_Z;
	regs.CY = (v1 + v2 + carry > 0xff);
	regs.HC = ((v1 & 0x0f) + (v2 & 0x0f) + carry > 0x0f);
	mem_write(&regs.A, val, 1);
	_cycle += cycle;
}

 
void	Emulateur::sub(struct s_param *p, int cycle)
{
	uint8_t v1;
	uint8_t v2;

	get_param(p);
	v1 = regs.A;
	v2 = mem_read(p->val, 1);
	regs.F = FLAG_N;
	regs.CY = v1 < v2;
	regs.HC = ((v1 & 0x0f) < (v2 & 0x0f));
	regs.Z = (v1 == v2);
	mem_write(&regs.A, v1 - v2, 1);
	_cycle += cycle;
}

void	Emulateur::sbc(struct s_param *p, int cycle)
{
	uint8_t v1;
	uint8_t v2;
	uint8_t val;
	bool carry;

	get_param(p);
	v1 = regs.A;
	v2 = mem_read(p->val, 1);
	carry = regs.CY;
	val = v1 - v2 - carry;
	regs.F = val ? 0 : FLAG_Z;
	regs.N = true;
	regs.CY = v1 < v2 + carry;
	regs.HC = (v1 & 0x0f) < (v2 & 0x0f) + carry;
	mem_write(&regs.A, val, 1);
	_cycle += cycle;
}

bool	Emulateur::check_rules(enum e_cond cond)
{
	if ((cond == NZ && ((regs.F & FLAG_Z) != 0)) ||
		(cond == Z && ((regs.F & FLAG_Z) == 0)) ||
		(cond == NC && ((regs.F & FLAG_CY) != 0)) ||
		(cond == C && ((regs.F & FLAG_CY) == 0)))
		return (false);
	return (true);
}

void	Emulateur::jr(struct s_param *p, enum e_cond cond)
{
	_cycle += 2;
	if (!check_rules(cond))
		return ;
	get_param(p);
	regs.PC += *(int8_t *)p->val;
	_cycle += 1;
}

void	Emulateur::ret(enum e_cond cond)
{
	_cycle += 2;
	if (!check_rules(cond))
		return ;
	if (cond == EMPTY)
		_cycle -= 1;
	regs.PC = mem_read(_RAM + regs.SP, 2);
	regs.SP += 2;
	_cycle += 3;
}

void	Emulateur::reti(int cycle)
{
	regs.PC = mem_read(_RAM + regs.SP, 2);
	regs.SP += 2;
	_IME = true;
	_cycle += cycle;
}

void	Emulateur::pop(struct s_param *p, int cycle)
{
	get_param(p);
	mem_write(p->val, mem_read(_RAM + regs.SP, 2), 2);
	regs.SP += 2;
	_cycle += cycle;
}

void	Emulateur::get_param(struct s_param *p)
{
	if (p->type == REG)
		p->val = p->p;
	else
		p->val = _RAM + regs.PC - p->s;
	if (p->deref && p->s == 1)
		p->val = _RAM + 0xFF00 + mem_read(p->val, 1);
	else if (p->deref && p->s == 2)
		p->val = _RAM + mem_read(p->val, 2);
}

void	Emulateur::jp(struct s_param *p, enum e_cond cond)
{
	_cycle += 3;
	if (!check_rules(cond))
		return ;
	get_param(p);
	regs.PC = mem_read(p->val, 2);
	_cycle += 1;
}

void	Emulateur::call(struct s_param *p, enum e_cond cond)
{
	_cycle += 3;
	if (!check_rules(cond))
		return ;
	get_param(p);
	*(uint16_t *)(_RAM + regs.SP - 2) = regs.PC;
	regs.PC = mem_read(p->val, 2);
	regs.SP -= 2;
	_cycle += 3;
}

void	Emulateur::push(struct s_param *p, int cycle)
{
	get_param(p);
	regs.SP -= 2;
	mem_write(_RAM + regs.SP, mem_read(p->val, 2), 2);
	_cycle += cycle;
}

void	Emulateur::rst(uint8_t nb, int cycle)
{
	regs.SP -= 2;
	mem_write(_RAM + regs.SP, regs.PC, 2);
	regs.PC = nb * 8;
	_cycle += cycle;
}

void	Emulateur::ldhl(struct s_param *p, int cycle)
{
	int8_t e;

	get_param(p);
	regs.F = 0;
	mem_read(p->val, 1);
	e = *(int8_t *)p->val;
	regs.HL = regs.SP + e;
	regs.CY = (regs.SP + e > 0xffff);
	regs.HC = ((regs.SP & 0x0fff) + e > 0x0fff);
	_cycle += cycle;
}

void	Emulateur::rlc(struct s_param *p, int cycle)
{
	bool	tmp;
	uint8_t	val;

	get_param(p);
	val = mem_read(p->val, 1);
	tmp = val & 0x80;
	mem_write(p->val, (val << 1) | tmp, 1);
	regs.F = 0;
	regs.Z = !val;
	regs.CY = tmp;
	_cycle += cycle;
}

void	Emulateur::rrc(struct s_param *p, int cycle)
{
	bool	tmp;
	uint8_t	val;

	get_param(p);
	val = mem_read(p->val, 1);
	tmp = val & 1;
	mem_write(p->val, (val >> 1) | (tmp << 7), 1);
	regs.F = 0;
	regs.Z = !val;
	regs.CY = tmp;
	_cycle += cycle;
}

void	Emulateur::rl(struct s_param *p, int cycle)
{
	uint8_t				val;
	bool				tmp;

	get_param(p);
	val = mem_read(p->val, 1);
	tmp = regs.CY;
	regs.F = 0;
	regs.CY = val & 0x80;
	val = (val << 1) | tmp;
	regs.Z = !val;
	mem_write(p->val, val, 1);
	_cycle += cycle;
}

void	Emulateur::rr(struct s_param *p, int cycle)
{
	uint8_t				val;
	bool				tmp;

	get_param(p);
	val = mem_read(p->val, 1);
	tmp = regs.CY;
	regs.F = 0;
	regs.CY = val & 1;
	val = (val >> 1) | (tmp << 7);
	regs.Z = !val;
	mem_write(p->val, val, 1);
	_cycle += cycle;
}

void	Emulateur::sla(struct s_param *p, int cycle)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = val << 1;
	regs.CY = val & 0x80;
	mem_write(p->val, val << 1, 1);
	_cycle += cycle;
}

void	Emulateur::sra(struct s_param *p, int cycle)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = val >> 1;
	regs.CY = val & 1;
	mem_write(p->val, val >> 1 | (val & 0x80), 1);
	_cycle += cycle;
}

void	Emulateur::srl(struct s_param *p, int cycle)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = val >> 1;
	regs.CY = val & 1;
	mem_write(p->val, val >> 1, 1);
	_cycle += cycle;
}

void	Emulateur::_swap(struct s_param *p, int cycle)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = !val;
	mem_write(p->val, val << 4 | val >> 4, 1);
	_cycle += cycle;
}

void	Emulateur::bit(struct s_param *p, uint8_t bit, int cycle)
{
	get_param(p);
	regs.HC = true;
	regs.N = false;
	regs.Z = (mem_read(p->val, 1) & (1 << bit)) ? 0 : 1;
	_cycle += cycle;
}

void	Emulateur::res(struct s_param *p, uint8_t bit, int cycle)
{
	get_param(p);
	mem_write(p->val, mem_read(p->val, 1) & ~(1 << bit), 1);
	_cycle += cycle;
}

void	Emulateur::set(struct s_param *p, uint8_t bit, int cycle)
{
	get_param(p);
	mem_write(p->val, mem_read(p->val, 1) | (1 << bit), 1);
	_cycle += cycle;
}

void	Emulateur::op203()
{
	const struct s_instruction_params	*instr;

	instr = &_op203[*reinterpret_cast<uint8_t*>(_RAM + regs.PC)];
	regs.PC += 1 + instr->nb_params;
	instr->f();
}

void	Emulateur::di(int cycle)
{
	_IME = false;
	_cycle += cycle;
}

void	Emulateur::ei(int cycle)
{
	_IME = true;
	mem_write(_RAM + 0xffff, 0x1f, 1);
	_cycle += cycle;
}

void	Emulateur::ccf(int cycle)
{
}
