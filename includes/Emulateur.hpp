#ifndef EMULATEUR_HPP
# define EMULATEUR_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>

using namespace std;

# include <strings.h>
# include <string.h>
# include <string>
# include <iostream>
# include <instructions.hpp>
# include <Header.hpp>
# include <thread>
# include <sdl.hpp>
# include <vector>
# include <SDL2/SDL.h>
# include <csignal>

# include <time.h>
# include <sys/time.h> 
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# define FLAG_Z  (1 << 7)
# define FLAG_N  (1 << 6)
# define FLAG_H  (1 << 5)
# define FLAG_CY (1 << 4)

# define IO_RIGHT 1
# define IO_LEFT 2
# define IO_UP 4
# define IO_DOWN 8
# define IO_A 1
# define IO_B 2
# define IO_SELECT 4
# define IO_START 8

# define TYPE_FROM_SIZE(size) (size == 1 ? (uint8_t) : (uint16_t))

struct s_regs {
	union u_AF {
		struct s_AF {
			uint8_t F;
			uint8_t A;
		} af;
		uint16_t AF;
	} af;

	union u_BC {
		struct s_BC {
			uint8_t C;
			uint8_t B;
		} bc;
		uint16_t BC;
	} bc;

	union u_DE {
		struct s_DE {
			uint8_t E;
			uint8_t D;
		} de;
		uint16_t DE;
	} de;

	union u_HL {
		struct s_HL {
			uint8_t L;
			uint8_t H;
		} hl;
		uint16_t HL;
	} hl;

	uint16_t SP;
	uint16_t PC;
};

struct user_input
{
	uint8_t p14;
	uint8_t p15;
};

struct s_param_info
{
	void				*param;
	enum e_param_type	type;
	bool				deref;
	uint16_t			*rez;
	uint16_t			e;
};

struct s_oam_obj
{
	uint8_t				y;
	uint8_t				x;
	uint8_t				chrcode;
	uint8_t				color_pal : 3;
	bool				char_bank : 1;
	bool				mono_pal : 1;
	bool				h_flip : 1;
	bool				v_flip : 1;
	bool				prio : 1;
};

struct s_interrupt
{
	uint16_t	old_pc;
	bool		routine;
};

enum e_right {
	PROHIB = 0,
	RD = 1,
	WR = 2,
	RDWR = 3
};

class Emulateur;

struct s_ram_regs {
	enum e_right	right;
	uint8_t		(Emulateur::*read)();
	void			(Emulateur::*write)(uint16_t value);
};

class Emulateur {
	private:
		const vector<struct s_ram_regs> _ram_regs;
		const vector<struct s_instruction_params> _op203;
		const vector<struct s_instruction_params> _opcode;

		std::string	_ROM;
		uint64_t	_cycle;
		uint8_t		_RAM[0x10000];
		bool		_IME;
		s_interrupt	_idata;

		struct user_input	_input;

		uint32_t _begin;
		uint32_t _end;
		
		SDL_Window*		_window;
		SDL_Renderer*	_renderer;
		SDL_Surface*	_surface;
		uint32_t		_pixels_map[GB_WINDOW_SIZE_X * GB_WINDOW_SIZE_Y];

		SDL_Thread		*_cpu_thread;
		SDL_Thread		*_lcd_thread;
		SDL_Thread		*_timer_thread;
		SDL_Thread		*_tima_thread;

		uint16_t	_cpu_tick_counter;
		uint32_t	_frequency; // in Hetz
		uint16_t	_timer;
		uint64_t	_timer_counter;
		bool		_timer_status;

		Emulateur();

		void	set_rom(std::string rom);
		void	print_regs(void);

		struct s_regs regs;

		void	nop(struct s_params& p, int cycle);
		void	ld(int8_t inc, void *param_1, void *param_2, struct s_params& p, int cycle);
		void	inc(void *param, struct s_params& p, int cycle);
		void	decr(void *param, struct s_params& p, int cycle);
		void	rlca(struct s_params& p, int cycle);
		void	rla(struct s_params& p, int cycle);
		void	rrca(struct s_params& p, int cycle);
		void	rra(struct s_params& p, int cycle);
		void	daa(struct s_params& p, int cycle);
		void	cpl(struct s_params& p, int cycle);
		void	stop(struct s_params& p, int cycle);
		void	halt(struct s_params& p, int cycle);
		void	_and(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	_or(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	_xor(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	cp(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	add(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	adc(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	sub(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	sbc(void *param_1, void *param_2, struct s_params& p, int cycle);
		void	jr(enum e_cond cond, struct s_params& p, int cycle);

		void	jp(enum e_cond cond, void *param_1, struct s_params& p, int cycle);

		void	ret(enum e_cond cond, struct s_params& p, int cycle);
		void	reti(struct s_params& p, int cycle);
		void	pop(void *param, struct s_params& p, int cycle);
		void	push(void *param, struct s_params& p, int cycle);
		void	call(enum e_cond cond, struct s_params& p, int cycle);
		void	rst(uint8_t nb, struct s_params& p, int cycle);

		void	ldhl(void *param1, void *param2, struct s_params& p, int cycle);

		void	rlc(void *param1, struct s_params& p, int cycle);
		void	rrc(void *param1, struct s_params& p, int cycle);
		void	rl(void *param1, struct s_params& p, int cycle);
		void	rr(void *param1, struct s_params& p, int cycle);
		void	sla(void *param1, struct s_params& p, int cycle);
		void	sra(void *param1, struct s_params& p, int cycle);
		void	srl(void *param1, struct s_params& p, int cycle);
		void	_swap(void *param1, struct s_params& p, int cycle);
		void	bit(uint8_t bit, void *param1, struct s_params& p, int cycle);
		void	res(uint8_t bit, void *param1, struct s_params& p, int cycle);
		void	set(uint8_t bit, void *param1, struct s_params& p, int cycle);

		void	di(struct s_params& p, int cycle);
		void	ei(struct s_params& p, int cycle);
		
		void	op203(struct s_params& p, int cycle);

		Emulateur(const Emulateur & cp);
		void		init_registers(void);
		bool		check_rules(enum e_cond cond);

		void		get_params(struct s_param_info *p, uint8_t size);

		uint16_t	mem_read(void *addr, int8_t size);
		void		mem_write(void *addr, uint16_t value, int8_t size);
		void		mem_write_signed(void *addr, int16_t value, int8_t size);
		bool		is_cpu_regs(void *addr);
		

		void		sdl_init();

		void		interrupt(void);
		void		interrupt_func(short addr, uint8_t iflag);


		void		print_line(uint64_t ly, uint64_t start, struct s_oam_obj **objs);
		uint32_t	get_time_from_frequency(uint8_t freq);

		int			cpu_thread(void *data);
		int			lcd_thread(void *data);
		int			tima_thread(void *data);
		int			timer_thread(void *data);

		bool		update();
		void		render();

		void		set_pixel(uint32_t pixel, uint16_t x, uint16_t y);
		uint8_t		color_htor(uint32_t color);
		uint8_t		color_htog(uint32_t color);
		uint8_t		color_htob(uint32_t color);
		uint8_t		color_htoa(uint32_t color);
		uint32_t 	color_5_to_8(uint16_t gb_color);

		uint8_t		read_p1();

		void		write_div(uint16_t value);
		void		write_lcdc(uint16_t value);
		void		write_stat(uint16_t value);
		void		write_scy(uint16_t value);
		void		write_scx(uint16_t value);
		void		write_ly(uint16_t value);
		void		write_lyc(uint16_t value);
		void		write_dma(uint16_t value);

		void		print_bg();
		void		print_tile(uint8_t *tile, int x, int y);
		void		print_all_tiles();
		void		dump_data_tiles();
		void		fill_input_from_key(SDL_Keycode sym, SDL_EventType t);
		uint8_t		bit_to_gray(uint8_t b);

		// static void	timer_thread(uint8_t *_RAM);

		void		sort_obj(struct s_oam_obj **objs);
		void		print_obj_line(struct s_oam_obj	*obj, uint64_t ly);
		void		print_tile_line(uint8_t *tile, int x, int y, int ly, bool flip);


	public:
		static int create_cpu_thread(void *ptr);
		static int create_lcd_thread(void *ptr);
		static int create_timer_thread(void *ptr);
		static int create_tima_thread(void *ptr);

		class InvalidRead : public std::exception
		{
			public:
			short addr;
			stringstream s;
			InvalidRead(short ad) throw() : addr(ad) {
				s << "Invalid Read at 0x" << std::setfill('0') << std::setw(4) << std::hex << addr << endl;
			}
			const char *what() const throw ()
			{
				return (s.str().c_str());
			}
		};
		class InvalidWrite : public std::exception
		{
			public:
			short addr;
			stringstream s;
			InvalidWrite(short ad) throw() : addr(ad) {
				s << "Invalid Write at 0x" << std::setfill('0') << std::setw(4) << std::hex << addr << endl;
			}
			const char *what() const throw ()
			{
				return (s.str().c_str());
			}
		};

		Emulateur(std::string rom);
		~Emulateur(/* args */);
		Emulateur & operator=(const Emulateur & cp);

		void	emu_start(uint32_t begin, uint32_t end);

};

#endif
