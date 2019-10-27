#ifndef EMULATEUR_HPP
# define EMULATEUR_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>

using namespace std;

# include <strings.h>
# include <string.h>
# include <instructions.hpp>
# include <Header.hpp>
# include <thread>
# include <sdl.hpp>
# include <vector>
# include <list>
# include <SDL2/SDL.h>
# include <csignal>
# include <sys/stat.h>

# include <time.h>
# include <sys/time.h> 
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>

# include <algorithm>
# include <iterator>
# include <regex>

# include <registers.hpp>
# include <ram_regs.hpp>
# include <Memory_controller.hpp>

# define TYPE_FROM_SIZE(size) (size == 1 ? (uint8_t) : (uint16_t))


struct s_param_info
{
	void				*param;
	enum e_param_type	type;
	bool				deref;
	uint16_t			*rez;
	uint16_t			e;
};

struct __attribute__((__packed__)) s_oam_obj
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

enum e_tile_type
{
	BG,
	OBJ
};

enum e_nb_param {
	ONE = 1,
	TWO = 2,
	THREE = 4
};

typedef std::function<void(vector<string> param)> t_deb_func;

struct s_deb_cmd {
	string			cmd;
	uint8_t			nb_param;
	t_deb_func		f;
};

struct s_break {
	uint32_t		id;
	uint16_t		addr;
};

struct s_watch {
	uint32_t		id;
	uint16_t		addr;
	enum e_right	right;
};

struct s_cgb {
	bool on;
	bool mode_double_speed;
};

enum e_select {
	NOT = 0,
	P14 = 1,
	P15 = 2,
	ALL = 3
};

struct __attribute__((__packed__)) s_tac {
	uint8_t			clock_select : 2;
	bool			on : 1;
	uint8_t			unused : 5;
};

struct __attribute__((__packed__)) s_p1 {
	uint8_t			out : 4;
	enum e_select	select : 2;
	uint8_t			unused : 2;
};

struct __attribute__((__packed__)) s_inter {
	bool			vblank : 1;
	bool			lcdc : 1;
	bool			timer : 1;
	bool			serial : 1;
	bool			io : 1;
	uint8_t			unused : 3;
};

struct __attribute__((__packed__)) s_lcdc {
	bool			bg_display : 1;
	bool			obj_display : 1;
	bool			obj_size : 1; // 3
	bool			bg_code_addr : 1;
	bool			bg_data_addr : 1; // 5
	bool			window : 1;
	bool			window_code_addr : 1; // 7
	bool			on : 1;
};

struct __attribute__((__packed__)) s_stat {
	bool			mode : 2;
	bool			match_ly : 1;
	bool			imode0 : 1;
	bool			imode1 : 1;
	bool			imode2 : 1;
	bool			imatch_ly : 1;
	bool			unused : 1;
};

struct __attribute__((__packed__)) s_vbk {
	bool			bank : 1;
	uint8_t			unused : 7;
};

struct __attribute__((__packed__)) s_cps {
	union {
		struct {
			bool	hl : 1;
			uint8_t	pal_data_nb : 2;
			uint8_t	pal_nb : 3;
		};
		uint8_t		pal_addr : 6;
	};
	bool			unused : 1;
	bool			inc : 1;
};

struct s_gb_regs {
	struct s_p1		&p1;
	uint8_t			&div;
	uint8_t			&tima;
	struct s_tac	&tac;
	struct s_inter	&iflag;
	struct s_inter	&ie;
	struct s_lcdc	&lcdc;
	struct s_stat	&stat;
	uint8_t			&scy;
	uint8_t			&scx;
	uint8_t			&ly;
	uint8_t			&lyc;
	uint8_t			&wy;
	uint8_t			&wx;
	uint8_t			&svbk;
	struct s_vbk	&vbk;
	uint8_t			&key1;
	uint8_t			&hdma1;
	uint8_t			&hdma2;
	uint8_t			&hdma3;
	uint8_t			&hdma4;
	uint8_t			&hdma5;
	struct s_cps	&bcps;
	uint8_t			&bcpd;
	struct s_cps	&ocps;
	uint8_t			&ocpd;

};

struct __attribute__((__packed__)) s_bg_atrb
{
	uint8_t				pal_nb : 3;
	bool				bank_nb : 1;
	bool				unused : 1;
	bool				hflip : 1;
	bool				vflip : 1;
	bool				prio : 1;
};

class Emulateur {
	public:
		static int create_main_thread(void *ptr);

		// For memory_controller
		uint8_t					RAM[0x10000];
		struct s_regs 			regs;
		struct user_input		input;
		std::string				ROM;
		std::string				save_name;
		struct s_cgb			cgb;
		const struct s_gb_regs	gb_regs;

		Emulateur(std::string file, bool debug=false);
		~Emulateur(/* args */);
		Emulateur & operator=(const Emulateur & cp);

		void	emu_start();
		bool	check_watchpoint(uint8_t *addr, enum e_right right, uint8_t size);
		bool	check_breakpoint();

	private:
		const vector<struct s_instr_params>	_op203;
		const vector<struct s_instr_params>	_opcode;
		const vector<struct s_cv_instr> 	_cv_instrs;
		const vector<struct s_deb_cmd>		_deb_cmd;

		const Header			_header;
		std::string				_file_name;
		static const uint8_t	_dmg_bios[];

		list<struct s_watch>	_watchpoints;
		list<struct s_break>	_breakpoints;
		uint32_t				_id_break;
		bool					_step_by_step;
		bool					_debug_mode;

		uint64_t	_cycle;
		uint32_t	_lcd_cycle;

		const s_instr_params	*_instr;

		uint8_t		_current_instr_cycle;
		uint8_t		_interrupt_cycle;
		bool		_exec_current_instr;
		bool		_debug;

		const struct s_cartridge 	&_cartridge;
		Memory_controller 			&_MBC;

		SDL_Window*		_window;
		SDL_Renderer*	_renderer;
		SDL_Surface*	_surface;
		uint32_t		_pixels_map[GB_WINDOW_SIZE_X * GB_WINDOW_SIZE_Y];

		SDL_Thread		*_main_thread;

		uint32_t								_frequency; // in Hetz
		bool									_tima_delay_interrupt;
		std::chrono::system_clock::time_point	_start_time;

		bool		_halt_status;
		bool		_stop_status;
		bool		_isatty;
		bool		_reset;
		int			_test;
		uint16_t	_trace;

		struct s_param	p_A = {REG, &regs.A, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_B = {REG, &regs.B, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_C = {REG, &regs.C, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_D = {REG, &regs.D, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_E = {REG, &regs.E, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_F = {REG, &regs.F, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_H = {REG, &regs.H, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_L = {REG, &regs.L, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_C_D = {REG, &regs.C, NULL, UNSIGN, true, 1, 1};
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
		struct s_param	p_HL_D2 = {REG, &regs.HL, NULL, UNSIGN, true, 2, 2};
		struct s_param	p_n = {DIR, NULL, NULL, UNSIGN, false, 1, 1};
		struct s_param	p_nn = {DIR, NULL, NULL, UNSIGN, false, 2, 2};
		struct s_param	p_e = {DIR, NULL, NULL, SIGN, false, 1, 1};
		struct s_param	p_n_D = {DIR, NULL, NULL, UNSIGN, true, 1, 1};
		struct s_param	p_nn_D1 = {DIR, NULL, NULL, UNSIGN, true, 2, 1};
		struct s_param	p_nn_D2 = {DIR, NULL, NULL, UNSIGN, true, 2, 2};

		Emulateur();

		void	emu_init();
		const struct s_cv_instr *get_cv_infos(uint8_t opcode) const;
		void exec_instr();
		void update_lcd();
		void update_tima();
		void cadence();

		void	set_rom(std::string rom);
		void	print_regs(void);
		Memory_controller 	&get_memory_controller();

		void	get_instr();
		void	debug_mode();
		void	print_instr(void);

		void	nop();
		void	ld(struct s_param *p1, struct s_param *p2, int8_t inc, int size);
		void	inc(struct s_param *p);
		void	dec(struct s_param *p);
		void	rrca();
		void	rlca();
		void	rla();
		void	rra();
		void	daa();
		void	cpl();
		void	stop();
		void	halt();
		void	_and(struct s_param *p);
		void	_or(struct s_param *p);
		void	_xor(struct s_param *p);
		void	cp(struct s_param *p);
		void	add(struct s_param *p1, struct s_param *p2, int size);
		void	adc(struct s_param *p);
		void	sub(struct s_param *p);
		void	sbc(struct s_param *p);
		void	jr(struct s_param *p);
		void	ret();
		void	reti();
		void	pop(struct s_param *p);
		void	jp(struct s_param *p);
		void	call(struct s_param *p);
		void	push(struct s_param *p);
		void	rst(uint8_t nb);
		void	ldhl(struct s_param *p);
		void	rlc(struct s_param *p);
		void	rrc(struct s_param *p);
		void	rl(struct s_param *p);
		void	rr(struct s_param *p);
		void	sla(struct s_param *p);
		void	sra(struct s_param *p);
		void	srl(struct s_param *p);
		void	_swap(struct s_param *p);
		void	bit(struct s_param *p, uint8_t bit);
		void	res(struct s_param *p, uint8_t bit);
		void	set(struct s_param *p, uint8_t bit);
		void	di();
		void	ei();
		void	ccf();
		void	scf();
		void	get_param(struct s_param *p);
		void	op203();

		Emulateur(const Emulateur & cp);
		void		init_registers(void);
		bool		check_rules(enum e_cond cond);

		void		*cpu_regs(void *addr);
		void		*read_gb_regs(uint8_t *addr);
		void		*write_gb_regs(uint8_t *addr, uint8_t value, int8_t size);
		void		*read_ROM_RAM_regs(uint8_t *addr);
		bool		write_ROM_regs(uint8_t *addr, uint8_t value, int8_t sizek);
		bool		write_RAM_regs(uint8_t *addr, uint16_t value, int8_t size);
		void		*gb_mem(void *addr);

		void		sdl_init();

		void		interrupt(void);
		void		interrupt_func(short addr, uint8_t iflag);


		void		print_line(uint64_t ly, uint64_t start, struct s_oam_obj **objs);

		bool		update();
		void		render();

		void		set_pixel(uint32_t pixel, uint16_t x, uint16_t y);
		uint8_t		color_htor(uint32_t color);
		uint8_t		color_htog(uint32_t color);
		uint8_t		color_htob(uint32_t color);
		uint8_t		color_htoa(uint32_t color);
		uint32_t 	color_5_to_8(uint16_t gb_color);

		void		read_p1();

		void		write_div(uint8_t value);
		void		write_lcdc(uint8_t value);
		void		write_stat(uint8_t value);
		void		write_scy(uint8_t value);
		void		write_scx(uint8_t value);
		void		write_ly(uint8_t value);
		void		write_lyc(uint8_t value);
		void		write_dma(uint8_t value);
		void		write_tac(uint8_t value);

		void		print_bg();
		void		print_tile(uint8_t *tile, int x, int y, bool h_flip, bool v_flip, uint8_t size, uint16_t pal_addr);
		// void		print_tile(uint8_t *tile, int x, int y);
		void		print_all_tiles();
		void		dump_data_tiles();
		void		fill_input_from_key(SDL_Keycode sym, SDL_EventType t);
		uint32_t	bit_to_gray(uint8_t b, uint16_t pal_addr);
		uint8_t		gray_to_bit(uint32_t grey, uint16_t pal_addr);
		uint8_t		search_bg_pix(int x, int y);

		// static void	timer_thread(uint8_t *_RAM);
		int			main_thread();
		void		quit();

		void		sort_objs(struct s_oam_obj **objs);
		void		print_objs(struct s_oam_obj **objs);
		void		print_obj(struct s_oam_obj *objs);
		void		print_bg_tile_line(const uint8_t *tile, int x, int y, int h);
		void		print_obj_tile_line(const uint8_t *tile, struct s_oam_obj *obj, uint8_t size, int h);
		void		line_round(uint64_t line_cycle, uint8_t ly, bool print);
		void		vblank_round(uint64_t line_cycle, uint8_t ly, bool print);

		void		print_bg_tile_line_cgb(const uint8_t *tile, const struct s_bg_atrb &bg, int x, int y, int off);
		uint32_t	bit_to_color(uint8_t b, uint16_t *pal_addr);


		void		print_bg_line(int y);
		void		print_window_line(int y);
		void		print_obj_line(struct s_oam_obj *obj, int off, int size);
		void		print_objs_line(int y);

		bool		check_cpu_reg(string param, uint16_t * &addr, uint16_t &val);
		bool		get_number(string param, uint16_t * &addr, uint16_t &val);
		void		print_trace();
		void		cmd_breakpoint(vector<string> param);
		void		cmd_continue(vector<string> param);
		void		cmd_next(vector<string> param);
		void		cmd_delete(vector<string> param);
		void		cmd_quit(vector<string> param);
		void		cmd_help(vector<string> param);
		void		cmd_info(vector<string> param);
		void		cmd_print(vector<string> param, uint8_t base);
		void		cmd_reset(vector<string> param);
		void		cmd_read(vector<string> param, uint8_t size);
		void		cmd_trace(vector<string> param);
		void		cmd_watchpoint(vector<string> param, enum e_right right);
		void		cmd_write(vector<string> param, uint8_t size);
		void		cmd_examine(vector<string> param, uint8_t size);

};

#endif
