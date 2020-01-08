#ifndef CARTRIDGE

enum e_cartridge_type {
	CT_ROM,
	CT_MBC1,
	CT_MBC2,
	CT_MBC3,
	CT_MBC5,
	CT_MBC6,
	CT_MBC7,
	CT_MMM01,
	CT_POCKET_CAMERA,
	CT_BANDAI_TAMA5,
	CT_HUC1,
	CT_HUC3,
	CT_UNKNOWN
};

# define CTA_RAM		(1 << 0)
# define CTA_BATTERY	(1 << 1)
# define CTA_RUMBLE		(1 << 2)
# define CTA_SENSOR		(1 << 3)
# define CTA_TIMER		(1 << 4)

struct s_cartridge {
	uint8_t id;
	std::string to_str;
	enum e_cartridge_type type;
	uint8_t attribute;
};

# define CARTRIDGE_TYPE \
{0, std::string("ROM ONLY"), CT_ROM, 0}, \
{1, std::string("MBC1"), CT_MBC1, 0}, \
{2, std::string("MBC1+RAM"), CT_MBC1, CTA_RAM}, \
{3, std::string("MBC1+RAM+BATTERY"), CT_MBC1, CTA_RAM | CTA_BATTERY}, \
{5, std::string("MBC2"), CT_MBC2, 0}, \
{6, std::string("MBC2+BATTERY"), CT_MBC2, CTA_BATTERY}, \
{8, std::string("ROM+RAM"), CT_ROM, CTA_RAM}, \
{9, std::string("ROM+RAM+BATTERY"), CT_ROM, CTA_RAM | CTA_BATTERY}, \
{11, std::string("MMM01"), CT_MMM01, 0}, \
{12, std::string("MMM01+RAM"), CT_MMM01, CTA_RAM}, \
{13, std::string("MMM01+RAM+BATTERY"), CT_MMM01, CTA_RAM | CTA_BATTERY}, \
{15, std::string("MBC3+TIMER+BATTERY"), CT_MBC3, CTA_BATTERY | CTA_TIMER}, \
{16, std::string("MBC3+TIMER+RAM+BATTERY"), CT_MBC3, CTA_RAM | CTA_BATTERY | CTA_TIMER}, \
{17, std::string("MBC3"), CT_MBC3, 0}, \
{18, std::string("MBC3+RAM"), CT_MBC3, CTA_RAM}, \
{19, std::string("MBC3+RAM+BATTERY"), CT_MBC3, CTA_RAM | CTA_BATTERY}, \
{25, std::string("MBC5"), CT_MBC5, 0}, \
{26, std::string("MBC5+RAM"), CT_MBC5, CTA_RAM}, \
{27, std::string("MBC5+RAM+BATTERY"), CT_MBC5, CTA_RAM | CTA_BATTERY}, \
{28, std::string("MBC5+RUMBLE"), CT_MBC5, CTA_RUMBLE}, \
{29, std::string("MBC5+RUMBLE+RAM"), CT_MBC5, CTA_RAM | CTA_RUMBLE}, \
{30, std::string("MBC5+RUMBLE+RAM+BATTERY"), CT_MBC5, CTA_RAM | CTA_BATTERY | CTA_RUMBLE}, \
{32, std::string("MBC6"), CT_MBC6, 0}, \
{34, std::string("MBC7+SENSOR+RUMBLE+RAM+BATTERY"), CT_MBC6, CTA_RAM | CTA_BATTERY | CTA_RUMBLE | CTA_SENSOR}, \
{252, std::string("POCKET CAMERA"), CT_POCKET_CAMERA, 0}, \
{253, std::string("BANDAI TAMA5"), CT_BANDAI_TAMA5, 0}, \
{254, std::string("HuC3"), CT_HUC3, 0}, \
{255, std::string("HuC1+RAM+BATTERY"), CT_HUC1, CTA_RAM | CTA_BATTERY}


#endif
