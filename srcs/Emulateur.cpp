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
}

void	Emulateur::print_regs(void)
{
	printf("\n--- REGISTERS ---\n");
	printf("B: 0x%02hhx\t\tC: 0x%02hhx\t(0x%04hx)\n", this->regs.bc.bc.B, this->regs.bc.bc.C, this->regs.bc.BC);
	printf("D: 0x%02hhx\t\tE: 0x%02hhx\t(0x%04hx)\n", this->regs.de.de.D, this->regs.de.de.E, this->regs.de.DE);
	printf("H: 0x%02hhx\t\tL: 0x%02hhx\t(0x%04hx)\n", this->regs.hl.hl.H, this->regs.hl.hl.L, this->regs.hl.HL);
	printf("A: 0x%02hhx\t(0x%04hx)\n", this->regs.af.af.A, this->regs.af.AF);
	printf("SP: 0x%04hx\tPC: 0x%04hx\n", this->regs.SP, this->regs.PC);
	printf("F =");
	if (this->regs.af.af.F & FLAG_Z)
		printf(" FLAG_Z");
	if (this->regs.af.af.F & FLAG_H)
		printf(" FLAG_H");
	if (this->regs.af.af.F & FLAG_N)
		printf(" FLAG_N");
	if (this->regs.af.af.F & FLAG_CY)
		printf(" FLAG_CY");
	printf("\n");
}

void	Emulateur::init_registers(void)
{
	this->regs.af.AF = 0x01B0; // Il faudra faire gaffe a A
	this->regs.bc.BC = 0x0013;
	this->regs.de.DE = 0x00d8;
	this->regs.hl.HL = 0x014d;
	this->regs.SP = 0xfffe;
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
	this->_RAM[0xff45] = 0x00; // LYC
	this->_RAM[0xff47] = 0xfc; // BGP
	this->_RAM[0xff48] = 0xff; // OBPO
	this->_RAM[0xff49] = 0xff; // OBP1
	this->_RAM[0xff4a] = 0x00; // WY
	this->_RAM[0xff4b] = 0x00; // WX
	this->_RAM[0xffff] = 0x00; // IE
}

void Emulateur::emu_start(uint32_t begin, uint32_t end)
{
	const struct s_instruction_params	*instr;
	int	x;

	memcpy(_RAM, _ROM.c_str(), 0x8000);
	this->regs.PC = begin;
	x = 0;



	while (true)
	{
		printf("0x%X : ", this->regs.PC);
		// if (this->regs.PC > end)
		// {
		// 	printf("Emulation ended. Stopping...\n");
		// 	return ;
		// }
		instr = &g_opcode[*reinterpret_cast<uint8_t*>(this->_RAM + this->regs.PC)];


		if (x == 259)
			print_regs();
		std::cout << instr->mnemonic << " -> ";
		x++;
		this->regs.PC += 1 + instr->nb_params * 1;
		instr->f();

		std::cout << std::endl;
	}
}

void Emulateur::set_rom(std::string rom)
{
	_ROM = rom;
}
