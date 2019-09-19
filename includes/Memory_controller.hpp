#ifndef MEMORY_CONTROLLER_HPP
# define MEMORY_CONTROLLER_HPP

class Emulateur;

enum e_right {
	PROHIB = 0,
	RD = 1,
	WR = 2,
	RDWR = 3
};

class Memory_controller;

struct s_ram_regs {
	enum e_right	right;
	void			(Memory_controller::*read)();
	void			(Memory_controller::*write)(uint8_t value);
};

class Memory_controller {
	protected:
		Emulateur *_emu;
		const vector<struct s_ram_regs> _ram_regs;

	public:
		Memory_controller();
		Memory_controller(Emulateur *emu);
		~Memory_controller();
		Memory_controller & operator=(const Memory_controller & cp);

		uint16_t	mem_read(void *addr, int8_t size);
		void		mem_write(void *addr, uint16_t value, int8_t size);

	private:
		void	write_div(uint8_t value);
		void	write_lcdc(uint8_t value);
		void	write_stat(uint8_t value);
		void	write_scy(uint8_t value);
		void	write_scx(uint8_t value);
		void	write_ly(uint8_t value);
		void	write_lyc(uint8_t value);
		void	write_dma(uint8_t value);
		void	write_tac(uint8_t value);
		void	read_p1(void);

		virtual void	*read_ROM_RAM_regs(uint8_t *addr) = 0;
		virtual bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size) = 0;
		virtual bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size) = 0;

		void	*cpu_regs(void *addr);
		void	*read_gb_regs(uint8_t *addr);
		void	*write_gb_regs(uint8_t *addr, uint8_t value, int8_t size);
		void	*gb_mem(void *addr);

};

class Memory_controller_ROM : public Memory_controller {
	public:
		using Memory_controller::Memory_controller;

	private:
		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC1 : public Memory_controller {
	public:
		using Memory_controller::Memory_controller;

	private:
		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC2 : public Memory_controller {
	public:
		using Memory_controller::Memory_controller;

	private:
		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC3 : public Memory_controller {
	public:
		using Memory_controller::Memory_controller;

	private:
		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC5 : public Memory_controller {
	public:
		using Memory_controller::Memory_controller;

	private:
		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

#endif
