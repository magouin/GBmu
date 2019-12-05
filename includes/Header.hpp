#ifndef HEADER_HPP
# define HEADER_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include <cstdint>

# include <inline_utils.hpp>
# include <cartridge.hpp>

#ifdef __GNUC__
# define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
# define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

using namespace std;

class Header {
	static const struct s_cartridge cartridge_types[0xFF];

	private:
		PACK(struct s_header
		{
			uint32_t	entrypoint;
			uint8_t		nin_logo[48];
			uint8_t		title[11];
			uint32_t	game_code;
			uint8_t		cgb_supp_code;
			uint16_t	license_code;
			uint8_t		sgb_flag;
			uint8_t		cartridge;
			uint8_t		rom_size;
			uint8_t		ram_size;
			uint8_t		dest_code;
			uint8_t		old_license_code;
			uint8_t		mask_rom_version;
			uint8_t		header_checksum;
			uint16_t	global_checksum;
		});
		const string _file;
		struct s_header _header;



	public:
		Header();
		Header(const string & file);
		Header(const Header & cp);
		~Header();
		void read_instr(size_t offset);
		Header & operator=(const Header & cp);
		size_t get_ram_size(void) const;
		const struct s_cartridge &get_cartridge_type() const;
};

#endif

