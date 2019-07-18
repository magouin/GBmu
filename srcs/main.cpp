#include <gbmu.hpp>
#include <functional>
#include <instructions.hpp>
#include <Emulateur.hpp>

using namespace std::placeholders;

Emulateur emu;


int main(int ac, const char **av)
{

	if (ac != 2)
	{
		cerr << "Usage : " << av[0] << " rom.gb" << endl;
		return (1);
	}


	// struct s_instruction_params instrs[3] = {
	// {0b00000000, "NOP", 0, {_, _, _, _}, 0, std::bind(&Emulateur::nop, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0})},
	// {0b00000001, "NOT AN INSTRUCTION (0b00000001)", 0, {_, _, _, _}, 0},
	// {0b00000010, "LD (BC), A", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, &emu, 2, (struct s_inc){0, 0}, &emu.regs.bc.BC, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 0})},
	// 			};

	// for (auto i = 0; i < 3; i++)
	// {
	// 	const struct s_instruction_params& cur = instrs[i];

	// 	std::cout << "Calling inst(" << i << ")\n";

	// 	// struct s_params p = {false, 0};

	// 	if (cur.f != NULL)
	// 		cur.f();
	// }

	ifstream rom_file(av[1], ios_base::in | ios::binary);
	if (rom_file.fail())
	{
		perror("Open error");
		return (2);
	}

	stringstream rom_stream;
	rom_stream << rom_file.rdbuf();

	string rom = rom_stream.str();

	emu.set_rom(rom);

	// Disassembler disas(rom);
	// disas.disassemble(0x100, 0x10);

	emu.emu_start(0x100, 0x110);


	return (0);
}
