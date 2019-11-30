#ifndef MEMORY_CONTROLLER_HPP
# define MEMORY_CONTROLLER_HPP

# define MBC2_RAM_SIZE 512
# define MBC2_SAV_SIZE 256

# include <iostream>
# include <vector>

using namespace std;

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
	void			(Memory_controller::*write)(uint8_t value);
};

class Memory_controller {
	public:
		uint8_t				*ram_ext_work_orig_ptr;
		uint8_t				*ram_ext_work_bank;
		const uint8_t		*rom_bank;
		uint8_t				pal_col_bg[64];
		uint8_t				pal_col_obj[64];
		const struct s_bg_atrb		*bg_atrb;

		Memory_controller(Emulateur &emu, size_t ram_size, bool debug = false);
		~Memory_controller();
		Memory_controller & operator=(const Memory_controller & cp);

		virtual uint16_t	mem_read(void *addr, int8_t size);
		virtual void		mem_write(void *addr, uint16_t value, int8_t size);

		void	new_dma(uint16_t video_offset, uint16_t src_offset, uint16_t len);

		const struct s_bg_atrb &get_bg_atrb(bool area, uint32_t id) const;
		const uint8_t			*get_ram_video_bank1(void) const;

		virtual void		save();
		bool				test();


	protected:
		Emulateur &_emu;
		const vector<struct s_ram_regs> _ram_regs;
		size_t	_ram_size;

		bool			_ram_ext_work_enable;
		uint8_t			_rom_bank_selected;
		const uint8_t	_debug;

		uint8_t		*_ram_work_bank; // bank 0 -> 0xc000 / 0xd000 ||| bank1 -> 0xd000 / 0xe000 ||| / bank 2 -> 7 in ram_work_bank
		uint8_t		_ram_work_bank_selected;

		uint8_t		*_ram_video_bank1;
		// bool		_ram_video_bank1_selected;

		virtual void		init(size_t ram_size);

		void	write_div(uint8_t value);
		void	write_lcdc(uint8_t value);
		void	write_stat(uint8_t value);
		void	write_scy(uint8_t value);
		void	write_scx(uint8_t value);
		void	write_ly(uint8_t value);
		void	write_lyc(uint8_t value);
		void	write_dma(uint8_t value);
		void	write_hdma5(uint8_t value);
		void	write_tac(uint8_t value);
		void	write_svbk(uint8_t value);
		void	write_key1(uint8_t value);
		void	write_bcpd(uint8_t value);
		void	write_ocpd(uint8_t value);

		void	read_p1(void);
		void	read_bcpd(void);
		void	read_ocpd(void);
		void	read_vbk(void);

		virtual void	*read_ROM_RAM_regs(uint8_t *addr) = 0;
		virtual bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size) = 0;
		virtual bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size) = 0;

		void	*cpu_regs(void *addr);
		void	*read_gb_regs(uint8_t *addr);
		void	*read_ram_work_bank(uint8_t *addr);
		void	*read_video_bank(uint8_t *addr);
		void	*write_gb_regs(uint8_t *addr, uint8_t value, int8_t size);
		void	*write_ram_work_bank(uint8_t *addr, uint16_t value, int8_t size);
		void	*write_video_ram(uint8_t *addr, uint16_t value, int8_t size);
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
		Memory_controller_MBC1(Emulateur &emu, size_t ram_size, bool debug);

	private:
		uint8_t	_rom_ram_bank;
		uint8_t	_rom_ram_select;

		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC2 : public Memory_controller {
	public:
		Memory_controller_MBC2(Emulateur &emu, size_t ram_size, bool debug);
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
		Memory_controller_MBC3(Emulateur &emu, size_t ram_size, bool debug);
		void		init(size_t ram_size);
		void		save();

	private:
		enum e_ram_rtc_switch {
			E_RAM,
			E_RTC
		};

		enum e_ram_rtc_switch	_ram_rtc_select;
		bool	_ram_rtc_enable;
		uint8_t	_ram_ext_work_bank_to_select;

		class RTC {
			public:
				RTC(void);
				~RTC();
				RTC & operator=(const RTC & cp);

				void	init_timestamp(std::time_t last_shutdown, std::time_t old_timestamp, uint8_t value);
				void	init_timestamp();

				uint8_t	get_register(void);
				void	set_register(uint8_t value);

				uint8_t get_DH(void);
				bool 	get_halt_flag(void);

				time_t	get_timestamp_gb(void);
				void	update_timestamp_gb();

				void 	switch_halt_flag();
				void	set_register_in_use(uint8_t value);


			private:
				union {
					struct __attribute__((__packed__)) {
						bool _day_count_9_bit : 1;
						uint8_t _unused : 5;
						bool _halt : 1;
						bool _day_count_cy : 1;
					};
					uint8_t	_RTC_DH;
				};

				const vector<uint8_t (RTC::*)(time_t)> _getters;
				const vector<void (RTC::*)(uint8_t, time_t)> _setters;

				uint8_t _register_in_use;

				std::time_t _timestamp_gb;
				std::time_t _real_timestamp;
				std::time_t _diff_timestamp;
				std::time_t _halt_timestamp_gb;

				uint8_t get_S(time_t timestamp_gb);
				uint8_t get_M(time_t timestamp_gb);
				uint8_t get_H(time_t timestamp_gb);
				uint8_t get_DL(time_t timestamp_gb);
				uint8_t get_DH(time_t timestamp_gb);

				void set_S(uint8_t value, time_t timestamp_gb);
				void set_M(uint8_t value, time_t timestamp_gb);
				void set_H(uint8_t value, time_t timestamp_gb);
				void set_DL(uint8_t value, time_t timestamp_gb);
				void set_DH(uint8_t value, time_t timestamp_gb);
		};

		RTC _RTC;
		uint16_t	_read_reg_RTC;

		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

class Memory_controller_MBC5 : public Memory_controller {
	public:
		Memory_controller_MBC5(Emulateur &emu, size_t ram_size, bool debug);

	private:
		uint8_t	_ram_ext_work_bank_to_select;

		void	*read_ROM_RAM_regs(uint8_t *addr);
		bool	write_ROM_regs(uint8_t *addr, uint8_t value, int8_t size);
		bool	write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
};

#endif
