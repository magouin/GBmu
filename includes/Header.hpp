#ifndef HEADER_HPP
# define HEADER_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include <cstdint>
using namespace std;

class Header {
	static const string cartridge_types[0xFF + 1];

	private:
		struct s_header
		{
			uint32_t	entrypoint;
			uint8_t		nin_logo[48];
			uint8_t		title[16];
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
		const string & _file;
		const struct s_header *_header;

	public:
		Header(const string & file);
		Header(const Header & cp);
		~Header();
		Header & operator=(const Header & cp);
};

#endif

