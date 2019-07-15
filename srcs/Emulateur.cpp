#include <Emulateur.hpp>

Emulateur::Emulateur()
{
}

Emulateur::Emulateur(const Emulateur & cp)
{
	(void)cp;
}

Emulateur::~Emulateur()
{
}

Emulateur &	Emulateur::operator=(const Emulateur & cp)
{
	(void)cp;
	return (*this);
}

Emulateur::Emulateur(std::string rom): _ROM(rom)
{
	bzero(_RAM, sizeof(_RAM));
	_IME = true;
}

void	Emulateur::print_regs(void)
{
	int i;

	i = 0;
	printf("A: %02hhX  F: %02hhX  (AF: %04hX)\n", this->regs.af.af.A, this->regs.af.af.F, this->regs.af.AF);
	printf("B: %02hhX  C: %02hhX  (BC: %04hX)\n", this->regs.bc.bc.B, this->regs.bc.bc.C, this->regs.bc.BC);
	printf("D: %02hhX  E: %02hhX  (DE: %04hX)\n", this->regs.de.de.D, this->regs.de.de.E, this->regs.de.DE);
	printf("H: %02hhX  L: %02hhX  (HL: %04hX)\n", this->regs.hl.hl.H, this->regs.hl.hl.L, this->regs.hl.HL);
	printf("PC: %04hX  SP: %04X\n", this->regs.PC, this->regs.SP);
	printf("ROM: 01  RAM: 00  WRAM: 01  VRAM: 00\n");
	printf("F: [");
	this->regs.af.af.F & FLAG_Z ? printf("Z") : printf("-");
	this->regs.af.af.F & FLAG_N ? printf("N") : printf("-");
	this->regs.af.af.F & FLAG_H ? printf("H") : printf("-");
	this->regs.af.af.F & FLAG_CY ? printf("C") : printf("-");
	printf("]\n");


}

void	Emulateur::init_registers(void)
{
	this->regs.af.AF = 0x01B0; // Il faudra faire gaffe a A
	this->regs.bc.BC = 0x0013;
	this->regs.de.DE = 0x00d8;
	this->regs.hl.HL = 0x014d;
	this->regs.SP = 0xfffe;
	this->_RAM[0xff00] = 0x00; // P1
	this->_RAM[0xff05] = 0x00; // TIMA
	this->_RAM[0xff06] = 0x00; // TMA 
	this->_RAM[0xff07] = 0x00; // TAC
	this->_RAM[0xff10] = 0x80; // NR10
	this->_RAM[0xff11] = 0xbf; // NR11
	this->_RAM[0xff12] = 0xf3; // NR12
	this->_RAM[0xff14] = 0xbf; // NR14
	this->_RAM[0xff16] = 0x3f; // NR21
	this->_RAM[0xff17] = 0x00; // NR22
	this->_RAM[0xff19] = 0xbf; // NR24
	this->_RAM[0xff1a] = 0x7f; // NR30
	this->_RAM[0xff1b] = 0xff; // NR31
	this->_RAM[0xff1c] = 0x9f; // NR32
	this->_RAM[0xff1e] = 0xbf; // NR33
	this->_RAM[0xff20] = 0xff; // NR41
	this->_RAM[0xff21] = 0x00; // NR42
	this->_RAM[0xff22] = 0x00; // NR43
	this->_RAM[0xff23] = 0xbf; // NR30
	this->_RAM[0xff24] = 0x77; // NR50
	this->_RAM[0xff25] = 0xf3; // NR51
	this->_RAM[0xff26] = 0xf1; // NR52
	this->_RAM[0xff40] = 0x91; // LCDC
	this->_RAM[0xff42] = 0x00; // SCY
	this->_RAM[0xff43] = 0x00; // SCX
	this->_RAM[0xff44] = 0x05; // LY
	this->_RAM[0xff45] = 0x00; // LYC
	this->_RAM[0xff47] = 0xfc; // BGP
	this->_RAM[0xff48] = 0xff; // OBPO
	this->_RAM[0xff49] = 0xff; // OBP1
	this->_RAM[0xff4a] = 0x00; // WY
	this->_RAM[0xff4b] = 0x00; // WX
	this->_RAM[0xffff] = 0x00; // IE
}

// void	Emulateur::timer_thread(uint8_t *_RAM)
void	Emulateur::timer_thread()
{
	bool			timer_status = false;
	uint			timer_freq;
	int				clock_freq[4] = {4096, 262144, 65536, 16384};
	struct timeval	t1, t2;
	long			elapsedTime;
	int				elapsedTick;

	gettimeofday(&t1, NULL);
	printf("Timer Begin\n");
	while (42)
	{
		if (timer_status != (_RAM[0xFF07] & 4))
		{
			if (!timer_status)
				printf("Starting Timer\n");
			gettimeofday(&t1, NULL);
			timer_status = _RAM[0xFF07] & 4;
		}
		if (timer_status)
		{
			timer_freq = clock_freq[_RAM[0xFF07] & 3];
			printf("timer_freq = %d\n", timer_freq);
			printf("I'm here\n");
			gettimeofday(&t2, NULL);
			elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000 * 1000;      // sec to us
			elapsedTime += (t2.tv_usec - t1.tv_usec);
			elapsedTick = elapsedTime / 1000 / timer_freq;
			if (_RAM[0xFF05] + elapsedTick > 255)
			{
				_RAM[0xFF0F] |= 4;
				elapsedTick -= 255 - _RAM[0xFF05];
				_RAM[0xFF05] = _RAM[0xFF06] + elapsedTick;
			}
			else
				_RAM[0xFF05] += elapsedTick;
		}
	}
}

void	Emulateur::interrupt_func(short addr, uint8_t iflag)
{
	_IME = false;
	_RAM[0xFF0F] &= ~iflag;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.af.AF;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.bc.BC;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.de.DE;
	// this->regs.SP -= 2;
	// *(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.hl.HL;
	this->regs.SP -= 2;
	*(uint16_t *)(this->_RAM + this->regs.SP) = this->regs.PC;
	_idata.old_pc = this->regs.PC; 
	regs.PC = addr;
	_idata.routine = true; 
}

void	Emulateur::interrupt(void)
{
	if (!_IME)
		return ;
	if(_RAM[0xFF0F] & 16 && _RAM[0xFFFF] & 16)
		interrupt_func(0x0060, 16);
	else if(_RAM[0xFF0F] & 8 && _RAM[0xFFFF] & 8)
		interrupt_func(0x0058, 8);
	else if(_RAM[0xFF0F] & 4 && _RAM[0xFFFF] & 4)
		interrupt_func(0x0050, 4);
	else if(_RAM[0xFF0F] & 2 && _RAM[0xFFFF] & 2)
		interrupt_func(0x0048, 2);
	else if(_RAM[0xFF0F] & 1 && _RAM[0xFFFF] & 1)
		interrupt_func(0x0040, 1);
}

void	Emulateur::emu_start(uint32_t begin, uint32_t end)
{
	const struct s_instruction_params	*instr;
	int	x;
	char c;
	# ifndef DEBUG
		struct timeval t2;
		long			elapsedTime;
	# endif
	struct timeval t1;

	memcpy(_RAM, _ROM.c_str(), 0x8000);
	this->regs.PC = begin;
	x = 0;

	init_registers();
	this->_cycle = 0;
	gettimeofday(&t1, NULL);

	// printf("time begin = %ld\n", t1.tv_sec * 1000 * 1000 + t1.tv_usec);
	std::thread timer(&Emulateur::timer_thread, this);
	// std::thread timer(timer_thread, _RAM);
	while (true)
	{
		// printf("0x%X : ", this->regs.PC);
		// if (this->regs.PC > end)
		// {
		// 	printf("Emulation ended. Stopping...\n");
		// 	return ;
		// }
		interrupt();
		instr = &g_opcode[*reinterpret_cast<uint8_t*>(this->_RAM + this->regs.PC)];
		# ifdef DEBUG
			print_regs();
			if (!read(0, &c, 1))
				exit(0);
			// std::cout << instr->mnemonic << " -> ";
		# endif
		x++;
		this->regs.PC += 1 + instr->nb_params * 1;
		instr->f();

		# ifndef DEBUG
			if (_cycle > 17470)
			{
				_cycle -= 17470;
				gettimeofday(&t2, NULL);
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000 * 1000;      // sec to us
				elapsedTime += (t2.tv_usec - t1.tv_usec);
				while (elapsedTime / 1000.0 / 1000.0 < 1.0 / 60)
				{
					gettimeofday(&t2, NULL);
					elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000 * 1000;      // sec to us
					elapsedTime += (t2.tv_usec - t1.tv_usec);
				}
				t1 = t2;

			}
		# endif
		// std::cout << std::endl;
	}
}

void Emulateur::set_rom(std::string rom)
{
	_ROM = rom;
}
