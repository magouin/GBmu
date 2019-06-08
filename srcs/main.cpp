#include <gbmu.hpp>


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

	Header h(rom);


	return (0);
}
