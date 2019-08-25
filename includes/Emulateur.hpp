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
	union {
		struct {
			union {
				uint8_t F;
				struct {
					uint8_t unused : 4;
					bool CY : 1;
					bool HC : 1;
					bool N : 1;
					bool Z : 1;
				};
			};
			uint8_t A;
		};
		uint16_t AF;
	};
	union {
		struct {
			uint8_t C;
			uint8_t B;
		};
		uint16_t BC;
	};
	union {
		struct {
			uint8_t E;
			uint8_t D;
		};
		uint16_t DE;
	};
	union {
		struct {
			uint8_t L;
			uint8_t H;
		};
		uint16_t HL;
	};
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
	void			(Emulateur::*write)(uint8_t value);
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

		struct s_param	p_A = {REG, &regs.A, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_B = {REG, &regs.B, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_C = {REG, &regs.C, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_D = {REG, &regs.D, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_E = {REG, &regs.E, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_F = {REG, &regs.F, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_H = {REG, &regs.H, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_L = {REG, &regs.L, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_A_D = {REG, &regs.A, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_B_D = {REG, &regs.B, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_C_D = {REG, &regs.C, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_D_D = {REG, &regs.D, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_E_D = {REG, &regs.E, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_F_D = {REG, &regs.F, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_H_D = {REG, &regs.H, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_L_D = {REG, &regs.L, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_BC = {REG, &regs.BC, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_AF = {REG, &regs.AF, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_DE = {REG, &regs.DE, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_HL = {REG, &regs.HL, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_SP = {REG, &regs.SP, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_PC = {REG, &regs.PC, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_BC_D1 = {REG, &regs.BC, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_AF_D1 = {REG, &regs.AF, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_DE_D1 = {REG, &regs.DE, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_HL_D1 = {REG, &regs.HL, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_SP_D1 = {REG, &regs.SP, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_BC_D2 = {REG, &regs.BC, NULL, UNSIGN, true, 2, 2};
		struct s_param	p_AF_D2 = {REG, &regs.AF, NULL, UNSIGN, true, 2, 2};
		struct s_param	p_DE_D2 = {REG, &regs.DE, NULL, UNSIGN, true, 2, 2};
		struct s_param	p_HL_D2 = {REG, &regs.HL, NULL, UNSIGN, true, 2, 2};
		struct s_param	p_SP_D2 = {REG, &regs.SP, NULL, UNSIGN, true, 2, 2};
		struct s_param	p_n = {DIR, NULL, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_nn = {DIR, NULL, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_e = {DIR, NULL, NULL, SIGN, false, 1, 1};
		struct s_param	p_n_D = {DIR, NULL, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_nn_D1 = {DIR, NULL, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_nn_D2 = {DIR, NULL, NULL, UNSIGN, true, 2, 2};

		Emulateur();

		void	set_rom(std::string rom);
		void	print_regs(void);

		struct s_regs regs;


		void	nop(int cycle);
		void	ld(struct s_param *p1, struct s_param *p2, int8_t inc, int size, int cycle);
		void	inc(struct s_param *p, int cycle);
		void	dec(struct s_param *p, int cycle);
		void	rrca(int cycle);
		void	rlca(int cycle);
		void	rla(int cycle);
		void	rra(int cycle);
		void	daa(int cycle);
		void	cpl(int cycle);
		void	stop(int cycle);
		void	halt(int cycle);
		void	_and(struct s_param *p, int cycle);
		void	_or(struct s_param *p, int cycle);
		void	_xor(struct s_param *p, int cycle);
		void	cp(struct s_param *p, int cycle);
		void	add(struct s_param *p1, struct s_param *p2, int size, int cycle);
		void	adc(struct s_param *p, int cycle);
		void	sub(struct s_param *p, int cycle);
		void	sbc(struct s_param *p, int cycle);
		void	jr(struct s_param *p, enum e_cond cond);
		void	ret(enum e_cond cond);
		void	reti(int cycle);
		void	pop(struct s_param *p, int cycle);
		void	jp(struct s_param *p, enum e_cond cond);
		void	call(struct s_param *p, enum e_cond cond);
		void	push(struct s_param *p, int cycle);
		void	rst(uint8_t nb, int cycle);
		void	ldhl(struct s_param *p, int cycle);
		void	rlc(struct s_param *p, int cycle);
		void	rrc(struct s_param *p, int cycle);
		void	rl(struct s_param *p, int cycle);
		void	rr(struct s_param *p, int cycle);
		void	sla(struct s_param *p, int cycle);
		void	sra(struct s_param *p, int cycle);
		void	srl(struct s_param *p, int cycle);
		void	_swap(struct s_param *p, int cycle);
		void	bit(struct s_param *p, uint8_t bit, int cycle);
		void	res(struct s_param *p, uint8_t bit, int cycle);
		void	set(struct s_param *p, uint8_t bit, int cycle);
		void	di(int cycle);
		void	ei(int cycle);
		void	ccf(int cycle);
		void	op203();
		void	get_param(struct s_param *p);

		Emulateur(const Emulateur & cp);
		void		init_registers(void);
		bool		check_rules(enum e_cond cond);

		uint16_t	mem_read(void *addr, int8_t size);
		void		mem_write(void *addr, uint16_t value, int8_t size);
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

		void		write_div(uint8_t value);
		void		write_lcdc(uint8_t value);
		void		write_stat(uint8_t value);
		void		write_scy(uint8_t value);
		void		write_scx(uint8_t value);
		void		write_ly(uint8_t value);
		void		write_lyc(uint8_t value);
		void		write_dma(uint8_t value);

		void		print_bg();
		void		print_tile(uint8_t *tile, int x, int y, bool h_flip, bool v_flip, uint8_t size);
		// void		print_tile(uint8_t *tile, int x, int y);
		void		print_all_tiles();
		void		dump_data_tiles();
		void		fill_input_from_key(SDL_Keycode sym, SDL_EventType t);
		uint8_t		bit_to_gray(uint8_t b);

		// static void	timer_thread(uint8_t *_RAM);

		void		sort_objs(struct s_oam_obj **objs);
		void		print_objs(struct s_oam_obj **objs);
		void		print_obj(struct s_oam_obj *objs);
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
