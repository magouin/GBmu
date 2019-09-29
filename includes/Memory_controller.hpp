#ifndef MEMORY_CONTROLLER_HPP
# define MEMORY_CONTROLLER_HPP

# define MBC2_RAM_SIZE 512
# define MBC2_SAV_SIZE 256

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
	public:
		uint8_t				*external_ram;
		uint8_t				*ram_bank;
		const uint8_t		*rom_bank;

		Memory_controller(Emulateur &emu, size_t ram_size);
		~Memory_controller();
		Memory_controller & operator=(const Memory_controller & cp);

		virtual uint16_t	mem_read(void *addr, int8_t size);
		virtual void		mem_write(void *addr, uint16_t value, int8_t size);

		virtual void		save();

	protected:
		Emulateur &_emu;
		const vector<struct s_ram_regs> _ram_regs;
		size_t	_ram_size;

		bool	_RAM_ENABLE;
		uint8_t	_ROM_BANK;

		virtual void		init(size_t ram_size);

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

// class Memory_controller_ROM : public Memory_controller {
// 	public:
// 		using Memory_controller::Memory_controller;

// 	private:
// 		void	*read_ROM_RAM_regs(uint8_t *addr);
// 		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
// 		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
// };

class Memory_controller_MBC1 : public Memory_controller {
	public:
		Memory_controller_MBC1(Emulateur &emu, size_t ram_size);

	private:
		uint8_t	_ROM_RAM_BANK;
		uint8_t	_ROM_RAM_SELECT;

		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC2 : public Memory_controller {
	public:
		Memory_controller_MBC2(Emulateur &emu, size_t ram_size);
		uint16_t	mem_read(void *addr, int8_t size);
		void		init(size_t ram_size);
		void		save();

	private:
		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC3 : public Memory_controller {
	public:
		Memory_controller_MBC3(Emulateur &emu, size_t ram_size);

	private:
		uint8_t	_ROM_RAM_BANK;
		uint8_t	_ROM_RAM_SELECT;

		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC5 : public Memory_controller {
	public:
		Memory_controller_MBC5(Emulateur &emu, size_t ram_size);

	private:
		uint8_t	_RAM_BANK;

		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

#endif
