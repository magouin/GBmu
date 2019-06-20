#ifndef DISASSEMBLER_HPP
# define DISASSEMBLER_HPP

# include <Header.hpp>
# include <iostream>
# include <string>
# include <instructions.hpp>

using namespace std;

class Disassembler {
	private:
		const string & _file;
		const Header _header;
		Disassembler();
		Disassembler & operator=(const Disassembler & cp);
public:
		Disassembler(const string & file);
		Disassembler(const Disassembler & cp);
		~Disassembler();

		void disassemble(uint32_t offset, uint32_t size = 0);
};

#endif
