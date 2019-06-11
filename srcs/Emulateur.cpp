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
	printf("B: 0x%02hhx\t\tC: 0x%02hhx\n", this->regs.bc.bc.B, this->regs.bc.bc.C);
	printf("D: 0x%02hhx\t\tE: 0x%02hhx\n", this->regs.de.de.D, this->regs.de.de.E);
	printf("H: 0x%02hhx\t\tL: 0x%02hhx\n", this->regs.hl.hl.H, this->regs.hl.hl.L);
	printf("A: 0x%02hhx\n", this->regs.af.af.A);
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

void Emulateur::emu_start(uint32_t begin, uint32_t end)
{
	const struct s_instruction_params	*instr;

	printf("Starting emulation from 0x%X to 0x%X\n", begin, end);
	memcpy(_RAM, _ROM.c_str(), 0x8000);
	this->regs.PC = begin;
	while (true)
	{
		printf("0x%X : ", this->regs.PC);
		// if (this->regs.PC > end)
		// {
		// 	printf("Emulation ended. Stopping...\n");
		// 	return ;
		// }
		instr = &g_opcode[*reinterpret_cast<uint8_t*>(this->_RAM + this->regs.PC)];
		std::cout << instr->mnemonic << " -> ";

		this->regs.PC += 1 + instr->nb_params * 1;
		instr->f();
		print_regs();
		std::cout << std::endl;
	}
}

void Emulateur::set_rom(std::string rom)
{
	_ROM = rom;
}
