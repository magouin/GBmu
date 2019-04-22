#include <gbmu.hpp>


int main(int ac, char **av)
{
	if (ac != 2)
	{
		cerr << "Usage : " << av[0] << " rom.gb" << endl;
		return (1);
	}

	string rom_name = av[1];
	cout << "Coucou" << endl;
	return (0);
}
