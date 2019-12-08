#include <Emulateur.hpp>
#include <debugger.hpp>

bool	Emulateur::check_cpu_reg(string param, uint16_t * &addr, uint16_t &val)
{
	static const string		cpu_regs[] = {"a", "f", "af", "b", "c", "bc", "d", "e", "de", "h", "l", "hl"};
	static const int8_t		cpu_off[] = {1, -1, -2, 0, -2, -3, -1, -3, -4, -2, -4, -5};
	uint8_t					x = 0;
	bool					deref = false;

	if (param[0] == '*')
	{
		deref = true;
		param.erase(param.begin(), param.begin() + 1);
	}
	while (x < 12)
	{
		if (cpu_regs[x] == param)
		{
			addr = (uint16_t *)((uint8_t *)&regs + x + cpu_off[x]);
			val = (x % 3 != 2) ? *(uint8_t *)addr : *addr;
			if (deref)
			{
				addr = (uint16_t *)(RAM + val);
				val = _MBC.mem_read(addr, 2);
			}
			return (true);
		}
		x++;
	}
	return (false);
}

void	Emulateur::print_trace()
{
	int i;

	i = -1;
	printf("A: %02hhX F: %02hhX B: %02hhX C: %02hhX D: %02hhX E: %02hhX H: %02hhX L: %02hhX SP: %04X PC: ", regs.A, regs.F, regs.B, regs.C, regs.D, regs.E, regs.H, regs.L, regs.SP);
	printf("%02X:%04X | ", (regs.PC >= 0x4000 && regs.PC < 0x8000 ? (uint8_t)((_MBC.rom_bank - ROM) / 0x4000) : 0), regs.PC);
	while (++i < _instr->nb_params) printf("%02X", _MBC.mem_read(RAM + regs.PC + i, 1));
	printf("%02X: ", _MBC.mem_read(RAM + regs.PC + i, 1));
	print_instr();
	if (_trace == 0)
	{
		_step_by_step = true;
		_debug_mode = true;
	}
}

bool	Emulateur::get_number(string param, uint16_t * &addr, uint16_t &val)
{
	size_t		x = -1;
	bool		hex = false;
	bool		deref = false;

	if (check_cpu_reg(param, addr, val))
		return (true);
	if (param[x + 1] == '*')
	{
		deref = true;
		param.erase(param.begin(), param.begin() + 1);
	}
	if (param[x + 1] == '0' && (param[x + 2] == 'x' || param[x + 2] == 'X'))
	{
		hex = true;
		x += 2;
	}
	while (++x < param.length())
		if (!(std::isdigit(param[x]) || (hex && ((param[x] >= 'a' && param[x] <= 'f') || (param[x] >= 'A' && param[x] <= 'F')))))
		{
			printf("Parse Error\n");
			return (false);
		}
	addr = NULL;
	val = hex ? std::stoul(param, nullptr, 16) : (uint16_t)std::stoi(param);
	if (deref)
	{
		addr = (uint16_t *)(RAM + val);
		val = _MBC.mem_read(addr, 2);
	}
	return (true);
}

bool	Emulateur::check_watchpoint(uint8_t *addr, enum e_right right)
{
	list<s_watch>::iterator it;
	list<s_watch>::iterator end;

	it = _watchpoints.begin();
	end = _watchpoints.end();
	while (it != end)
	{
		if ((*it).addr == (addr - RAM) && ((*it).right & right))
		{
			_step_by_step = true;
			_debug_mode = false;
			printf("Exec: ");
			print_instr();
			return (true);
		}
		it++;
	}
	return (false);
}

void	Emulateur::cmd_watchpoint(vector<string> param, enum e_right right)
{
	uint16_t	*addr;
	uint16_t	val;

	if (!get_number(param[1], addr, val))
		return ;
	_watchpoints.push_front({_id_break, val, right});
	printf("Added watchpoint %d at 0x%04hX\n", _id_break, val);
	_id_break++;
}

void	Emulateur::cmd_trace(vector<string> param)
{
	uint16_t	*addr;
	uint16_t	val;

	if (!get_number(param[1], addr, val))
		return ;
	_trace = val;
	_step_by_step = false;
	_debug_mode = !_trace;
}

void	Emulateur::cmd_print(vector<string> param, uint8_t base)
{
	uint16_t	*addr;
	uint16_t	val;
	int			x = -1;

	if (!get_number(param[1], addr, val))
		return ;
	if (base == 2)
	{
		printf(" 0b");
		while (++x < 16)
			printf(((val << x) & 0x8000) ? "1" : "0");
		printf("\n");
	}
	else if (base == 10)
		printf(" %hd\n", val);
	else
		printf(" 0x%04hX\n", val);
}

void	Emulateur::cmd_info(vector<string> param)
{
	print_regs();
}

void	Emulateur::cmd_quit(vector<string> param)
{
	printf("QUITTING\n");
	quit();
}

void	Emulateur::cmd_breakpoint(vector<string> param)
{
	uint16_t	*addr;
	uint16_t	val;

	if (!get_number(param[1], addr, val))
		return ;
	_breakpoints.push_front({_id_break, val});
	printf("Added breakpoint %d at 0x%04hX\n", _id_break, val);
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

void	Emulateur::cmd_examine(vector<string> param, uint8_t size)
{
	uint16_t	*addr;
	uint16_t	val1;
	uint16_t	val2;
	uint8_t		*data;
	uint16_t	x;

	if (!get_number(param[1], addr, val1))
		return ;
	if (param.size() == 3)
	{
		if (!get_number(param[2], addr, val2))
			return ;
	}
	else
		val2 = 16 / size;
	data = RAM + val1;
	x = 0;
	while (x < val2)
	{
		if (x % (16 / size) == 0)
			printf("0x%04X:", (uint16_t)(data - RAM));
		if (size == 1)
			printf(" %02hhX", *data);
		else if (size == 2)
			printf(" %04hX", *(uint16_t *)data);
		else
			printf(" %08X", *(uint32_t *)data);
		x++;
		if (x % (16 / size) == 0 && x != val2)
			printf("\n");
		data += size;
	}
	printf("\n");
}


void	Emulateur::cmd_write(vector<string> param, uint8_t size)
{
	uint16_t *addr;
	uint16_t val1;
	uint16_t val2;

	if (!get_number(param[2], addr, val1))
		return ;
	if (!get_number(param[1], addr, val2))
		return ;
	if (!addr)
		addr = (uint16_t *)(RAM + val2);
	_MBC.mem_write(addr, val1, size);
}

void	Emulateur::cmd_read(vector<string> param, uint8_t size)
{
	uint16_t *addr;
	uint16_t val;

	if (!get_number(param[1], addr, val))
		return ;
	if (size == 1)
		printf(" 0x%02hhX\n", (uint8_t)_MBC.mem_read(RAM + val, 1));
	else if (size == 2)
		printf(" 0x%04hX\n", _MBC.mem_read(RAM + val, 2));
	else if (size == 4)
		printf(" 0x%04hX%04hX\n", _MBC.mem_read(RAM + val + 2, 2), _MBC.mem_read(RAM + val, 2));
}

void	Emulateur::cmd_reset(vector<string> param)
{
	_reset = true;
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
	uint16_t *addr;
	uint16_t id;

	if (!get_number(param[1], addr, id))
		return ;
	_breakpoints.remove_if([id](struct s_break b){ return b.id == id; });
	_watchpoints.remove_if([id](struct s_watch w){ return w.id == id; });
}

void	Emulateur::cmd_help(vector<string> param)
{
	printf(USAGE);
}

void	Emulateur::print_instr(void)
{
	if (_instr->nb_params == 0)
		printf(_instr->mnemonic, NULL);
	else if (_instr->nb_params == 1)
		printf(_instr->mnemonic, _MBC.mem_read(RAM + regs.PC + 1, 1));
	else if (_instr->nb_params == 2)
		printf(_instr->mnemonic, _MBC.mem_read(RAM + regs.PC + 1, 2));
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
	printf("ROM: %02X  RAM: %02X  WRAM: %02X  VRAM: %02X\n", (uint8_t)((_MBC.rom_bank - ROM) / 0x4000),
															 (uint8_t)(((uint8_t *)_MBC.ram_ext_work_bank - (uint8_t *)_MBC.ram_ext_work_orig_ptr) / 0x2000),
															 (RAM[0xff70] & 7) ? (RAM[0xff70] & 7) : 1,
															 RAM[0xff4f]);
	printf("F: [");
	regs.Z ? printf("Z") : printf("-");
	regs.N ? printf("N") : printf("-");
	regs.HC ? printf("H") : printf("-");
	regs.CY ? printf("C") : printf("-");
	printf("]\n");
	printf("%02X:%04X:  ", (regs.PC >= 0x4000 && regs.PC < 0x8000 ? (uint8_t)((_MBC.rom_bank - ROM) / 0x4000) : 0), regs.PC);
	while (++i < _instr->nb_params) printf("%02X", _MBC.mem_read(RAM + regs.PC + i, 1));
	printf("%02X\t", _MBC.mem_read(RAM + regs.PC + i, 1));
	print_instr();
}

void	Emulateur::debug_mode()
{
	string			cmd;
	static string	last;
	vector<string>	param;
	regex			regex("\\s+");
	size_t			i;

	if (!_debug_mode)
		print_regs();
	_debug_mode = true;
	while (_debug_mode)
	{
		if (_is_a_tty)
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
			_deb_cmd[i].f(param);
		param.clear();
		last = cmd;
	}
}
