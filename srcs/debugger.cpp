#include <Emulateur.hpp>

bool	Emulateur::get_number(string param, uint16_t &addr)
{
	size_t		x = -1;
	bool		hex = false;

	if (param[0] == '0' && (param[1] == 'x' || param[1] == 'X'))
	{
		hex = true;
		x = 1;
	}
	while (++x < param.length())
		if (!(std::isdigit(param[x]) || (hex && ((param[x] >= 'a' && param[x] <= 'f') || (param[x] >= 'A' && param[x] <= 'F')))))
		{
			printf("Parse Error\n");
			return (false);
		}
	if (hex)
		addr = std::stoul(param, nullptr, 16);
	else
		addr = (uint16_t)std::stoi(param);
	return (true);
}


void	Emulateur::cmd_quit(vector<string> param)
{
	printf("QUITTING\n");
	quit();
}

void	Emulateur::cmd_breakpoint(vector<string> param)
{
	uint16_t	addr;

	if (!get_number(param[1], addr))
		return ;
	_breakpoints.push_front({_id_break, addr});
	printf("Added breakpoint %d at 0x%04hX\n", _id_break, addr);
	_id_break++;
}

bool	Emulateur::check_breakpoint()
{
	list<s_break>::iterator it;
	list<s_break>::iterator end;

	it = _breakpoints.begin();
	end = _breakpoints.end();
	while (it != end)
	{
		if ((*it).addr == regs.PC)
			return (true);
		it++;
	}
	return (false);
}

void	Emulateur::cmd_continue(vector<string> param)
{
	_step_by_step = false;
	_debug_mode = false;
}

void	Emulateur::cmd_next(vector<string> param)
{
	_step_by_step = true;
	_debug_mode = false;
}

void	Emulateur::cmd_delete(vector<string> param)
{
	uint16_t id;
	list<s_break>::iterator it_b;
	list<s_break>::iterator end_b;

	it_b = _breakpoints.begin();
	end_b = _breakpoints.end();
	if (!get_number(param[1], id))
		return ;
	_breakpoints.remove_if([id](struct s_break b){ return b.id == id; });
}

void	Emulateur::print_instr(void)
{
	if (_instr->nb_params == 0)
		printf(_instr->mnemonic, NULL);
	else if (_instr->nb_params == 1)
		printf(_instr->mnemonic, mem_read(_RAM + regs.PC + 1, 1));
	else if (_instr->nb_params == 2)
		printf(_instr->mnemonic, mem_read(_RAM + regs.PC + 1, 2));
}

void	Emulateur::print_regs(void)
{
	int i;

	i = -1;
	printf("A: %02hhX  F: %02hhX  (AF: %04hX)\n", regs.A, regs.F, regs.AF);
	printf("B: %02hhX  C: %02hhX  (BC: %04hX)\n", regs.B, regs.C, regs.BC);
	printf("D: %02hhX  E: %02hhX  (DE: %04hX)\n", regs.D, regs.E, regs.DE);
	printf("H: %02hhX  L: %02hhX  (HL: %04hX)\n", regs.H, regs.L, regs.HL);
	printf("PC: %04hX  SP: %04X\n", regs.PC, regs.SP);
	printf("ROM: %02x  RAM: %02x  WRAM: %02X  VRAM: %02X\n", (uint8_t)(((uint8_t *)_rom_bank - (uint8_t *)_ROM.c_str()) / 0x4000), (uint8_t)(((uint8_t *)_ram_bank - (uint8_t *)_external_ram) / 0x2000), (_RAM[0xff70] & 7) ? (_RAM[0xff70] & 7) : 1, _RAM[0xff4f]);
	printf("F: [");
	regs.Z ? printf("Z") : printf("-");
	regs.N ? printf("N") : printf("-");
	regs.HC ? printf("H") : printf("-");
	regs.CY ? printf("C") : printf("-");
	printf("]\n");
	printf("%02X:%04X:  ", (regs.PC >= 0x4000 && regs.PC < 0x8000 ? (uint8_t)(((uint8_t *)_rom_bank - (uint8_t *)_ROM.c_str()) / 0x4000) : 0), regs.PC);
	while (++i < _instr->nb_params) printf("%02X", mem_read(_RAM + regs.PC + i, 1));
	printf("%02X\t", mem_read(_RAM + regs.PC + i, 1));
	print_instr();
}

void	Emulateur::debug_mode()
{
	string			cmd;
	static string	last;
	vector<string>	param;
	regex			regex("\\s+");
	size_t			i;

	print_regs();
	_debug_mode = true;
	while (_debug_mode)
	{
		if (_isatty)
			printf("> ");
		if (!std::getline (std::cin, cmd))
			exit(0);
		if (cmd.empty() && last.empty())
			continue ;
		if (cmd.empty())
			cmd = last;
   		std::copy( std::sregex_token_iterator(cmd.begin(), cmd.end(), regex, -1),
              std::sregex_token_iterator(),
              back_inserter(param));
		i = 0;
		while (i < _deb_cmd.size() && _deb_cmd[i].cmd != param[0]) i++;
		if (i == _deb_cmd.size())
			printf("Command not found\n");
		else if (!(1 << (param.size() - 1) & _deb_cmd[i].nb_param))
			printf("Wrong number of arguments\n");
		else
			(this->*_deb_cmd[i].f)(param);
		param.clear();
		last = cmd;
	}
}
