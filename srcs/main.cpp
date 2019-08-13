#include <functional>
#include <instructions.hpp>
#include <Emulateur.hpp>

using namespace std::placeholders;



int main(int ac, const char **av)
{
	if (ac != 2)
	{
		cerr << "Usage : " << av[0] << " rom.gb" << endl;
		return (1);
	}

	ifstream rom_file(av[1], ios_base::in | ios::binary);
	if (rom_file.fail())
	{
		perror("Open error");
		return (2);
	}

	stringstream rom_stream;
	rom_stream << rom_file.rdbuf();

	string rom = rom_stream.str();

	Header r(rom);

	Emulateur emu(rom);

	try {
		emu.emu_start(0x100, 0x110);
	}
	catch (Emulateur::InvalidRead &e) {
		cout << e.what() << endl;
	}
	catch (Emulateur::InvalidWrite &e) {
		cout << e.what() << endl;
	}


	return (0);
}
