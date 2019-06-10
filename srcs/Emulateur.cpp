#include "Emulateur.hpp"

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

void Emulateur::emu_start(uint32_t begin, uint32_t end)
{
	printf("Starting emulation from 0x%X to 0x%X\n", begin, end);

	memcpy(_RAM, _ROM.c_str(), 0x8000);

	const struct s_instruction_params	*instr;
	this->regs.PC = begin;
	while (true)
	{
		printf("PC : 0x%X\n", this->regs.PC);
		if (this->regs.PC > end)
		{
			printf("Emulation ended. Stopping...\n");
			return ;
		}
		instr = &g_opcode[*reinterpret_cast<uint8_t*>(this->_RAM + this->regs.PC)];

		this->regs.PC += 1 + instr->nb_params * 1;
		instr->f();
	}
}

void Emulateur::set_rom(std::string rom)
{
	_ROM = rom;
}
