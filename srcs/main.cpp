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
	Emulateur emu(file_name, debug);
	emu.emu_start();
	return (0);
}
