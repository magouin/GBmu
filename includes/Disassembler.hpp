#ifndef DISASSEMBLER_HPP
# define DISASSEMBLER_HPP

# include <gbmu.hpp>

class Disassembler {
	private:
		const string & _file;
		Disassembler();
		Disassembler & operator=(const Disassembler & cp);

	public:

		Disassembler(const string & _file);
		Disassembler(const Disassembler & cp);
		~Disassembler();

		void disassemble(uint32_t offset);
};

#endif
