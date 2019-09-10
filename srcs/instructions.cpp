#include <instructions.hpp>
#include <iostream>
#include <Emulateur.hpp>

void	Emulateur::nop()
{
}

void	Emulateur::ld(struct s_param *p1, struct s_param *p2, int8_t inc, int size)
{
	get_param(p1);
	get_param(p2);
	regs.HL += inc;
	mem_write(p1->val, mem_read(p2->val, size), size);
}

void	Emulateur::inc(struct s_param *p)
{
	uint16_t val;

	get_param(p);
	val = mem_read(p->val, p->size);
	if (p->size == 1)
	{
		regs.N = false;
		regs.HC = ((val & 0xf) == 0xf);
		regs.Z = (val == 0xff);
	}
	mem_write(p->val, val + 1, p->size);
}

void	Emulateur::dec(struct s_param *p)
{
	uint16_t val;

	get_param(p);
	val = mem_read(p->val, p->size);
	if (p->size == 1)
	{
		regs.N = true;
		regs.HC = ((val & 0xf) == 0x00);
		regs.Z = (val == 1);
	}
	mem_write(p->val, val - 1, p->size);
}

void	Emulateur::rlca()
{
	uint8_t				*m;

	m = &regs.A;
	regs.F = 0;
	regs.CY = (*m & 0x80);
	*m = (*m << 1) | (*m >> 7);
}

void	Emulateur::rrca()
{
	uint8_t				*m;

	m = &regs.A;
	regs.F = 0;
	regs.CY = (*m & 1);
	*m = (*m >> 1) | (*m << 7);
}

void	Emulateur::rla()
{
	uint8_t				*m;
	bool				tmp;

	m = &regs.A;
	tmp = regs.CY;
	regs.F = 0;
	regs.CY = *m & 0x80;
	*m = (*m << 1) | tmp;
}

void	Emulateur::rra()
{
	uint8_t				*m;
	bool				tmp;

	m = &regs.A;
	tmp = regs.CY;
	regs.F = 0;
	regs.CY = *m & 1;
	*m = (*m >> 1) | (tmp << 7);
}

void	Emulateur::daa()
{
	int a;

	if (regs.N)
	{
		if (regs.HC) regs.A += 0xFA;
		if (regs.CY) regs.A += 0xA0;
	}
	else
	{
		a = regs.A;
		if ((regs.A & 0xF) > 0x9 || regs.HC) a += 0x6;
		if ((a & 0x1F0) > 0x90 || regs.CY) {
			a += 0x60;
			regs.CY = true;
		}
		else regs.CY = false;
		regs.A = a;
	}
	regs.HC = 0;
	regs.Z = !regs.A;
}

void	Emulateur::cpl()
{
	regs.A = ~(regs.A);
	regs.HC = true;
	regs.N = true;
}

void	Emulateur::stop() // TODO
{
	while ((_input.p14 & 0xf) != 0xf || (_input.p15 & 0xf) != 0xf) ;
	_stop_status = true;
}

void	Emulateur::halt() // TODO
{
	_halt_status = true;
	// printf("Halte qui va la ?\n");
	// exit(0);
	// printf("Entering halt status\n");
	// printf("ime: %d, ie : %02x, if: %02x\n", regs.IME, _RAM[REG_IE], _RAM[REG_IF]);
}

void	Emulateur::_and(struct s_param *p)
{
	get_param(p);
	regs.A = regs.A & mem_read(p->val, 1);
	regs.F = FLAG_H;
	regs.Z = regs.A ? false : true;
}

void	Emulateur::_or(struct s_param *p)
{
	get_param(p);
	regs.A = regs.A | mem_read(p->val, 1);
	regs.F = regs.A ? 0 : FLAG_Z;
}

void	Emulateur::_xor(struct s_param *p)
{
	get_param(p);
	regs.A = regs.A ^ mem_read(p->val, 1);
	regs.F = regs.A ? 0 : FLAG_Z;
}

void	Emulateur::cp(struct s_param *p)
{
	uint8_t v;

	get_param(p);
	regs.N = true;
	v = mem_read(p->val, 1);
	regs.Z = (regs.A == v);
	regs.CY = (regs.A < v);
	regs.HC = ((regs.A & 0xf) < (v & 0xf));
}

void	Emulateur::add(struct s_param *p1, struct s_param *p2, int size)
{
	uint32_t	v1;
	uint32_t	v2;
	uint32_t	val;
	uint32_t	H_val;
	uint32_t	CY_val;

	get_param(p1);
	get_param(p2);
	v1 = mem_read(p1->val, p1->size);
	v2 = mem_read(p2->val, p2->size);
	val = v1 + ((p2->t == SIGN) ? (int8_t)v2 : v2);
	H_val = (size == 2 ? 0xfff : 0xf);
	CY_val = (size == 2 ? 0xffff : 0xff);
	regs.N = false;
	if (size == 1) regs.Z = !(uint8_t)val;
	regs.HC = ((val & H_val) < (v1 & H_val));
	regs.CY = ((val & CY_val) < (v1 & CY_val));
	regs.Z = ((p2->t == SIGN) ? false : regs.Z);
	mem_write(p1->val, val, p1->size);
}

void	Emulateur::adc(struct s_param *p)
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
}

 
void	Emulateur::sub(struct s_param *p)
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
}

void	Emulateur::sbc(struct s_param *p)
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
}

bool	Emulateur::check_rules(enum e_cond cond)
{
	if ((cond == NZ && (regs.Z != false)) ||
		(cond == Z && (regs.Z == false)) ||
		(cond == NC && (regs.CY != false)) ||
		(cond == C && (regs.CY == false)))
		return (false);
	return (true);
}

void	Emulateur::jr(struct s_param *p)
{
	get_param(p);
	regs.PC += (int8_t)mem_read(p->val, 1);
}

void	Emulateur::ret()
{
	regs.PC = mem_read(_RAM + regs.SP, 2);
	regs.SP += 2;
}

void	Emulateur::reti()
{
	regs.PC = mem_read(_RAM + regs.SP, 2);
	regs.SP += 2;
	regs.IME = true;
}

void	Emulateur::pop(struct s_param *p)
{
	get_param(p);
	mem_write(p->val, mem_read(_RAM + regs.SP, 2), 2);
	regs.SP += 2;
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

void	Emulateur::jp(struct s_param *p)
{
	get_param(p);
	// printf("in jump - jumping to 0x%X\n", mem_read(p->val, 2));
	regs.PC = mem_read(p->val, 2);
}

void	Emulateur::call(struct s_param *p)
{
	get_param(p);
	mem_write(_RAM + regs.SP - 2, regs.PC, 2);
	regs.PC = mem_read(p->val, 2);
	regs.SP -= 2;
}

void	Emulateur::push(struct s_param *p)
{
	get_param(p);
	regs.SP -= 2;
	mem_write(_RAM + regs.SP, mem_read(p->val, 2), 2);
}

void	Emulateur::rst(uint8_t nb)
{
	regs.SP -= 2;
	mem_write(_RAM + regs.SP, regs.PC, 2);
	regs.PC = nb * 8;
}

void	Emulateur::ldhl(struct s_param *p)
{
	int16_t e;

	get_param(p);
	regs.F = 0;
	e = (int8_t)mem_read(p->val, 1);
	regs.HL = regs.SP + e;
	regs.CY = (((regs.SP ^ e ^ regs.HL) & 0x100) == 0x100);
	regs.HC = (((regs.SP ^ e ^ regs.HL) & 0x10) == 0x10);
}

void	Emulateur::rlc(struct s_param *p)
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
}

void	Emulateur::rrc(struct s_param *p)
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
}

void	Emulateur::rl(struct s_param *p)
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
}

void	Emulateur::rr(struct s_param *p)
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
}

void	Emulateur::sla(struct s_param *p)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = !((val & 0x7f));
	regs.CY = val >> 7;
	mem_write(p->val, (val << 1), 1);
}

void	Emulateur::sra(struct s_param *p)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = !(val >> 1);
	regs.CY = val & 1;
	mem_write(p->val, val >> 1 | (val & 0x80), 1);
}

void	Emulateur::srl(struct s_param *p)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = !(val >> 1);
	regs.CY = val & 1;
	mem_write(p->val, val >> 1, 1);
}

void	Emulateur::_swap(struct s_param *p)
{
	uint8_t				val;

	get_param(p);
	val = mem_read(p->val, 1);
	regs.F = 0;
	regs.Z = !val;
	mem_write(p->val, val << 4 | val >> 4, 1);
}

void	Emulateur::bit(struct s_param *p, uint8_t bit)
{
	get_param(p);
	regs.HC = true;
	regs.N = false;
	regs.Z = (mem_read(p->val, 1) & (1 << bit)) ? 0 : 1;
}

void	Emulateur::res(struct s_param *p, uint8_t bit)
{
	get_param(p);
	mem_write(p->val, mem_read(p->val, 1) & ~(1 << bit), 1);
}

void	Emulateur::set(struct s_param *p, uint8_t bit)
{
	get_param(p);
	mem_write(p->val, mem_read(p->val, 1) | (1 << bit), 1);
}

void	Emulateur::op203()
{
}

void	Emulateur::di()
{
	regs.IME = false;
}

void	Emulateur::ei()
{
	regs.IME = true;
}

void	Emulateur::ccf()
{
	regs.CY = !regs.CY;
	regs.HC = false;
	regs.N = false;
}

void	Emulateur::scf()
{
	regs.CY = true;
	regs.HC = false;
	regs.N = false;
}
