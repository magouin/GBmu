#ifndef REGISTERS_HPP
# define REGISTERS_HPP

# include <cstdint>

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

# define REG_SCY	0xff42
# define REG_SCX	0xff43

# define REG_LY		0xff44
# define REG_LYC	0xff45

# define REG_WY		0xff4a
# define REG_WX		0xff4b


// CGB only
# define REG_SVBK	0xff70
# define REG_KEY1	0xff4d
# define REG_HDMA1	0xff51
# define REG_HDMA2	0xff52
# define REG_HDMA3	0xff53
# define REG_HDMA4	0xff54
# define REG_HDMA5	0xff55

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
	bool	IME;
};

struct user_input
{
	uint8_t p15;
	uint8_t p14;
};

# define INIT_GB_REGS *reinterpret_cast<struct s_p1 *>(RAM + 0xff00), \
*reinterpret_cast<uint8_t *>(RAM + 0xff04), \
*reinterpret_cast<uint8_t *>(RAM + 0xff05), \
*reinterpret_cast<struct s_tac *>(RAM + 0xff07), \
*reinterpret_cast<struct s_inter *>(RAM + 0xff0f), \
*reinterpret_cast<struct s_inter *>(RAM + 0xffff), \
*reinterpret_cast<struct s_lcdc *>(RAM + 0xff40), \
*reinterpret_cast<struct s_stat *>(RAM + 0xff41), \
*reinterpret_cast<uint8_t *>(RAM + 0xff42), \
*reinterpret_cast<uint8_t *>(RAM + 0xff43), \
*reinterpret_cast<uint8_t *>(RAM + 0xff44), \
*reinterpret_cast<uint8_t *>(RAM + 0xff45), \
*reinterpret_cast<uint8_t *>(RAM + 0xff4a), \
*reinterpret_cast<uint8_t *>(RAM + 0xff4b), \
*reinterpret_cast<uint8_t *>(RAM + 0xff70), \
*reinterpret_cast<struct s_vbk *>(RAM + 0xff4f), \
*reinterpret_cast<uint8_t *>(RAM + 0xff4d), \
*reinterpret_cast<uint8_t *>(RAM + 0xff51), \
*reinterpret_cast<uint8_t *>(RAM + 0xff52), \
*reinterpret_cast<uint8_t *>(RAM + 0xff53), \
*reinterpret_cast<uint8_t *>(RAM + 0xff54), \
*reinterpret_cast<uint8_t *>(RAM + 0xff55), \
*reinterpret_cast<struct s_cps *>(RAM + 0xff68), \
*reinterpret_cast<uint8_t *>(RAM + 0xff69), \
*reinterpret_cast<struct s_cps *>(RAM + 0xff6a), \
*reinterpret_cast<uint8_t *>(RAM + 0xff6b)


#endif
