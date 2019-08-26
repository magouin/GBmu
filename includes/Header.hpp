#ifndef HEADER_HPP
# define HEADER_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include <cstdint>

# include <inline_utils.hpp>

using namespace std;

class Header {
	static const string cartridge_types[0xFF + 1];

	private:
		struct __attribute__((__packed__)) s_header
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
		};
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
};

#endif

