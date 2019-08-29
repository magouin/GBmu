#include <functional>
#include <instructions.hpp>
#include <Emulateur.hpp>

using namespace std::placeholders;

int main(int ac, const char **av)
{
	const char	*file_name;
	bool		debug;

	if (ac < 2 || ac > 3)
	{
		cerr << "Usage : " << av[0] << " [-d] rom.gb" << endl;
		return (1);
	}

	if (ac == 3 && strcmp(av[1], "-d") == 0)
	{
		file_name = av[2];
		debug = 1;
	}
	else if (ac == 3)
	{
		cerr << "Usage : " << av[0] << " [-d] rom.gb" << endl;
		return (1);
	}
	else
	{
		file_name = av[1];
		debug = false;
	}
	ifstream rom_file(file_name, ios_base::in | ios::binary);

	if (rom_file.fail())
	{
		perror("Open error");
		return (2);
	}

	stringstream rom_stream;
	rom_stream << rom_file.rdbuf();

	string rom = rom_stream.str();

	Header r(rom);

	Emulateur emu(rom, debug);

	try {
		emu.emu_start();
	}
	catch (Emulateur::InvalidRead &e) {
		cout << e.what() << endl;
	}
	catch (Emulateur::InvalidWrite &e) {
		cout << e.what() << endl;
	}
	return (0);
}
