#ifndef OPCODE
# define OPCODE \
{0b00000000, "nop\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::nop, this)}, \
{0b00000001, "ld bc, $%02hX\n", 2, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_BC, &p_nn, 0, 2)}, \
{0b00000010, "ld [bc], a\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_BC_D1, &p_A, 0, 1)}, \
{0b00000011, "inc bc\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::inc, this, &p_BC)}, \
{0b00000100, "inc b\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_B)}, \
{0b00000101, "dec b\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_B)}, \
{0b00000110, "ld b, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_B, &p_n, 0, 1)}, \
{0b00000111, "rlc\n", 0, {SET, SET_0, SET_0, SET_0}, 1, std::bind(&Emulateur::rlca, this)}, \
{0b00001000, "ld [$%02hX], sp\n", 2, {_, _, _, _}, 5, std::bind(&Emulateur::ld, this, &p_nn_D2, &p_SP, 0, 2)}, \
{0b00001001, "add hl, bc\n", 0, {SET, SET, SET_0, _}, 2, std::bind(&Emulateur::add, this, &p_HL, &p_BC, 2)}, \
{0b00001010, "ld a, [bc]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_BC_D1, 0, 1)}, \
{0b00001011, "dec bc\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::dec, this, &p_BC)}, \
{0b00001100, "inc c\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_C)}, \
{0b00001101, "dec c\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_C)}, \
{0b00001110, "ld c, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_C, &p_n, 0, 1)}, \
{0b00001111, "rrc\n", 0, {SET, SET_0, SET_0, SET_0}, 1, std::bind(&Emulateur::rrca, this)}, \
{0b00010000, "stop, $%02hhX\n", 1, {_, _, _, _}, 1, std::bind(&Emulateur::stop, this, &p_n)}, \
{0b00010001, "ld de, $%02hX\n", 2, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_DE, &p_nn, 0, 2)}, \
{0b00010010, "ld [de], a\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_DE_D1, &p_A, 0, 1)}, \
{0b00010011, "inc de\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::inc, this, &p_DE)}, \
{0b00010100, "inc d\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_D)}, \
{0b00010101, "dec d\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_D)}, \
{0b00010110, "ld d, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_D, &p_n, 0, 1)}, \
{0b00010111, "rl\n", 0, {SET, SET_0, SET_0, SET_0}, 1, std::bind(&Emulateur::rla, this)}, \
{0b00011000, "jr $%02hhX\n", 1, {_, _, _, _}, 3, std::bind(&Emulateur::jr, this, &p_e)}, \
{0b00011001, "add hl, de\n", 0, {SET, SET, SET_0, _}, 2, std::bind(&Emulateur::add, this, &p_HL, &p_DE, 2)}, \
{0b00011010, "ld a, [de]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_DE_D1, 0, 1)}, \
{0b00011011, "dec de\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::dec, this, &p_DE)}, \
{0b00011100, "inc e\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_E)}, \
{0b00011101, "dec e\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_E)}, \
{0b00011110, "ld e, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_E, &p_n, 0, 1)}, \
{0b00011111, "rr\n", 0, {SET, SET_0, SET_0, SET_0}, 1, std::bind(&Emulateur::rra, this)}, \
{0b00100000, "jr nz, $%02hhX\n", 1, {_, _, _, _}, 0, std::bind(&Emulateur::jr, this, &p_e)}, \
{0b00100001, "ld hl, $%02hX\n", 2, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_HL, &p_nn, 0, 2)}, \
{0b00100010, "ld [hl+], a\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_A, 1, 1)}, \
{0b00100011, "inc hl\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::inc, this, &p_HL)}, \
{0b00100100, "inc h\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_H)}, \
{0b00100101, "dec h\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_H)}, \
{0b00100110, "ld h, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_H, &p_n, 0, 1)}, \
{0b00100111, "daa\n", 0, {SET, SET_0, _, SET}, 1, std::bind(&Emulateur::daa, this)}, \
{0b00101000, "jr z, $%02hhX\n", 1, {_, _, _, _}, 0, std::bind(&Emulateur::jr, this, &p_e)}, \
{0b00101001, "add hl, hl\n", 0, {SET, SET, SET_0, _}, 2, std::bind(&Emulateur::add, this, &p_HL, &p_HL, 2)}, \
{0b00101010, "ld a, [hl+]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_HL_D1, 1, 1)}, \
{0b00101011, "dec hl\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::dec, this, &p_HL)}, \
{0b00101100, "inc l\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_L)}, \
{0b00101101, "dec l\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_L)}, \
{0b00101110, "ld l, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_L, &p_n, 0, 1)}, \
{0b00101111, "cpl\n", 0, {_, SET_1, SET_1, _}, 1, std::bind(&Emulateur::cpl, this)}, \
{0b00110000, "jr nc, $%02hhX\n", 1, {_, _, _, _}, 0, std::bind(&Emulateur::jr, this, &p_e)}, \
{0b00110001, "ld sp, $%02hX\n", 2, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_SP, &p_nn, 0, 2)}, \
{0b00110010, "ld [hl-], a\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_A, -1, 1)}, \
{0b00110011, "inc sp\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::inc, this, &p_SP)}, \
{0b00110100, "inc [hl]\n", 0, {_, SET, SET_0, SET}, 3, std::bind(&Emulateur::inc, this, &p_HL_D1)}, \
{0b00110101, "dec [hl]\n", 0, {_, SET, SET_1, SET}, 3, std::bind(&Emulateur::dec, this, &p_HL_D1)}, \
{0b00110110, "ld [hl], $%02hhX\n", 1, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_n, 0, 1)}, \
{0b00110111, "scf\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::scf, this)}, \
{0b00111000, "jr c, $%02hhX\n", 1, {_, _, _, _}, 0, std::bind(&Emulateur::jr, this, &p_e)}, \
{0b00111001, "add hl, sp\n", 0, {SET, SET, SET_0, _}, 2, std::bind(&Emulateur::add, this, &p_HL, &p_SP, 2)}, \
{0b00111010, "ld a, [hl-]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_HL_D1, -1, 1)}, \
{0b00111011, "dec sp\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::dec, this, &p_SP)}, \
{0b00111100, "inc a\n", 0, {_, SET, SET_0, SET}, 1, std::bind(&Emulateur::inc, this, &p_A)}, \
{0b00111101, "dec a\n", 0, {_, SET, SET_1, SET}, 1, std::bind(&Emulateur::dec, this, &p_A)}, \
{0b00111110, "ld a, $%02hhX\n", 1, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_n, 0, 1)}, \
{0b00111111, "ccf\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ccf, this)}, \
{0b01000000, "ld b, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_B, 0, 1)}, \
{0b01000001, "ld b, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_C, 0, 1)}, \
{0b01000010, "ld b, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_D, 0, 1)}, \
{0b01000011, "ld b, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_E, 0, 1)}, \
{0b01000100, "ld b, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_H, 0, 1)}, \
{0b01000101, "ld b, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_L, 0, 1)}, \
{0b01000110, "ld b, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_B, &p_HL_D1, 0, 1)}, \
{0b01000111, "ld b, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_B, &p_A, 0, 1)}, \
{0b01001000, "ld c, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_B, 0, 1)}, \
{0b01001001, "ld c, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_C, 0, 1)}, \
{0b01001010, "ld c, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_D, 0, 1)}, \
{0b01001011, "ld c, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_E, 0, 1)}, \
{0b01001100, "ld c, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_H, 0, 1)}, \
{0b01001101, "ld c, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_L, 0, 1)}, \
{0b01001110, "ld c, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_C, &p_HL_D1, 0, 1)}, \
{0b01001111, "ld c, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_C, &p_A, 0, 1)}, \
{0b01010000, "ld d, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_B, 0, 1)}, \
{0b01010001, "ld d, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_C, 0, 1)}, \
{0b01010010, "ld d, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_D, 0, 1)}, \
{0b01010011, "ld d, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_E, 0, 1)}, \
{0b01010100, "ld d, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_H, 0, 1)}, \
{0b01010101, "ld d, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_L, 0, 1)}, \
{0b01010110, "ld d, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_D, &p_HL_D1, 0, 1)}, \
{0b01010111, "ld d, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_D, &p_A, 0, 1)}, \
{0b01011000, "ld e, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_B, 0, 1)}, \
{0b01011001, "ld e, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_C, 0, 1)}, \
{0b01011010, "ld e, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_D, 0, 1)}, \
{0b01011011, "ld e, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_E, 0, 1)}, \
{0b01011100, "ld e, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_H, 0, 1)}, \
{0b01011101, "ld e, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_L, 0, 1)}, \
{0b01011110, "ld e, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_E, &p_HL_D1, 0, 1)}, \
{0b01011111, "ld e, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_E, &p_A, 0, 1)}, \
{0b01100000, "ld h, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_B, 0, 1)}, \
{0b01100001, "ld h, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_C, 0, 1)}, \
{0b01100010, "ld h, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_D, 0, 1)}, \
{0b01100011, "ld h, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_E, 0, 1)}, \
{0b01100100, "ld h, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_H, 0, 1)}, \
{0b01100101, "ld h, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_L, 0, 1)}, \
{0b01100110, "ld h, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_H, &p_HL_D1, 0, 1)}, \
{0b01100111, "ld h, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_H, &p_A, 0, 1)}, \
{0b01101000, "ld l, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_B, 0, 1)}, \
{0b01101001, "ld l, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_C, 0, 1)}, \
{0b01101010, "ld l, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_D, 0, 1)}, \
{0b01101011, "ld l, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_E, 0, 1)}, \
{0b01101100, "ld l, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_H, 0, 1)}, \
{0b01101101, "ld l, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_L, 0, 1)}, \
{0b01101110, "ld l, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_L, &p_HL_D1, 0, 1)}, \
{0b01101111, "ld l, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_L, &p_A, 0, 1)}, \
{0b01110000, "ld [hl], b\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_B, 0, 1)}, \
{0b01110001, "ld [hl], c\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_C, 0, 1)}, \
{0b01110010, "ld [hl], d\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_D, 0, 1)}, \
{0b01110011, "ld [hl], e\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_E, 0, 1)}, \
{0b01110100, "ld [hl], h\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_H, 0, 1)}, \
{0b01110101, "ld [hl], l\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_L, 0, 1)}, \
{0b01110110, "halt\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::halt, this)}, \
{0b01110111, "ld [hl], a\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_A, 0, 1)}, \
{0b01111000, "ld a, b\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_B, 0, 1)}, \
{0b01111001, "ld a, c\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_C, 0, 1)}, \
{0b01111010, "ld a, d\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_D, 0, 1)}, \
{0b01111011, "ld a, e\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_E, 0, 1)}, \
{0b01111100, "ld a, h\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_H, 0, 1)}, \
{0b01111101, "ld a, l\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_L, 0, 1)}, \
{0b01111110, "ld a, [hl]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_HL_D1, 0, 1)}, \
{0b01111111, "ld a, a\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ld, this, &p_A, &p_A, 0, 1)}, \
{0b10000000, "add b\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_B, 1)}, \
{0b10000001, "add c\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_C, 1)}, \
{0b10000010, "add d\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_D, 1)}, \
{0b10000011, "add e\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_E, 1)}, \
{0b10000100, "add h\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_H, 1)}, \
{0b10000101, "add l\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_L, 1)}, \
{0b10000110, "add [hl]\n", 0, {SET, SET, SET_0, SET}, 2, std::bind(&Emulateur::add, this, &p_A, &p_HL_D1, 1)}, \
{0b10000111, "add a\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::add, this, &p_A, &p_A, 1)}, \
{0b10001000, "adc b\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_B)}, \
{0b10001001, "adc c\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_C)}, \
{0b10001010, "adc d\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_D)}, \
{0b10001011, "adc e\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_E)}, \
{0b10001100, "adc h\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_H)}, \
{0b10001101, "adc l\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_L)}, \
{0b10001110, "adc [hl]\n", 0, {SET, SET, SET_0, SET}, 2, std::bind(&Emulateur::adc, this, &p_HL_D1)}, \
{0b10001111, "adc a\n", 0, {SET, SET, SET_0, SET}, 1, std::bind(&Emulateur::adc, this, &p_A)}, \
{0b10010000, "sub b\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_B)}, \
{0b10010001, "sub c\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_C)}, \
{0b10010010, "sub d\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_D)}, \
{0b10010011, "sub e\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_E)}, \
{0b10010100, "sub h\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_H)}, \
{0b10010101, "sub l\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_L)}, \
{0b10010110, "sub [hl]\n", 0, {SET, SET, SET_1, SET}, 2, std::bind(&Emulateur::sub, this, &p_HL_D1)}, \
{0b10010111, "sub a\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sub, this, &p_A)}, \
{0b10011000, "sbc b\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_B)}, \
{0b10011001, "sbc c\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_C)}, \
{0b10011010, "sbc d\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_D)}, \
{0b10011011, "sbc e\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_E)}, \
{0b10011100, "sbc h\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_H)}, \
{0b10011101, "sbc l\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_L)}, \
{0b10011110, "sbc [hl]\n", 0, {SET, SET, SET_1, SET}, 2, std::bind(&Emulateur::sbc, this, &p_HL_D1)}, \
{0b10011111, "sbc a\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::sbc, this, &p_A)}, \
{0b10100000, "and b\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_B)}, \
{0b10100001, "and c\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_C)}, \
{0b10100010, "and d\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_D)}, \
{0b10100011, "and e\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_E)}, \
{0b10100100, "and h\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_H)}, \
{0b10100101, "and l\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_L)}, \
{0b10100110, "and [hl]\n", 0, {SET_0, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::_and, this, &p_HL_D1)}, \
{0b10100111, "and a\n", 0, {SET_0, SET_1, SET_0, SET}, 1, std::bind(&Emulateur::_and, this, &p_A)}, \
{0b10101000, "xor b\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_B)}, \
{0b10101001, "xor c\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_C)}, \
{0b10101010, "xor d\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_D)}, \
{0b10101011, "xor e\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_E)}, \
{0b10101100, "xor h\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_H)}, \
{0b10101101, "xor l\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_L)}, \
{0b10101110, "xor [hl]\n", 0, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_xor, this, &p_HL_D1)}, \
{0b10101111, "xor a\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_xor, this, &p_A)}, \
{0b10110000, "or b\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_B)}, \
{0b10110001, "or c\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_C)}, \
{0b10110010, "or d\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_D)}, \
{0b10110011, "or e\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_E)}, \
{0b10110100, "or h\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_H)}, \
{0b10110101, "or l\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_L)}, \
{0b10110110, "or [hl]\n", 0, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_or, this, &p_HL_D1)}, \
{0b10110111, "or a\n", 0, {SET_0, SET_0, SET_0, SET}, 1, std::bind(&Emulateur::_or, this, &p_A)}, \
{0b10111000, "cp b\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_B)}, \
{0b10111001, "cp c\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_C)}, \
{0b10111010, "cp d\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_D)}, \
{0b10111011, "cp e\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_E)}, \
{0b10111100, "cp h\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_H)}, \
{0b10111101, "cp l\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_L)}, \
{0b10111110, "cp [hl]\n", 0, {SET, SET, SET_1, SET}, 2, std::bind(&Emulateur::cp, this, &p_HL_D1)}, \
{0b10111111, "cp a\n", 0, {SET, SET, SET_1, SET}, 1, std::bind(&Emulateur::cp, this, &p_A)}, \
{0b11000000, "ret nz\n", 0, {_, _, _, _}, 0, std::bind(&Emulateur::ret, this)}, \
{0b11000001, "pop bc\n", 0, {_, _, _, _}, 3, std::bind(&Emulateur::pop, this, &p_BC)}, \
{0b11000010, "jp nz, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::jp, this, &p_nn)}, \
{0b11000011, "jp $%02hX\n", 2, {_, _, _, _}, 4, std::bind(&Emulateur::jp, this, &p_nn)}, \
{0b11000100, "call nz, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::call, this, &p_nn)}, \
{0b11000101, "push bc\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::push, this, &p_BC)}, \
{0b11000110, "add $%02hhX\n", 1, {SET, SET, SET_0, SET}, 2, std::bind(&Emulateur::add, this, &p_A, &p_n, 1)}, \
{0b11000111, "rst\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 0)}, \
{0b11001000, "ret z\n", 0, {_, _, _, _}, 0, std::bind(&Emulateur::ret, this)}, \
{0b11001001, "ret\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::ret, this)}, \
{0b11001010, "jp z, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::jp, this, &p_nn)}, \
{0b11001011, "op203\n", 0, {SET, SET, SET, SET}, 0, NULL}, \
{0b11001100, "call z, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::call, this, &p_nn)}, \
{0b11001101, "call $%02hX\n", 2, {_, _, _, _}, 6, std::bind(&Emulateur::call, this, &p_nn)}, \
{0b11001110, "adc $%02hhX\n", 1, {SET, SET, SET_0, SET}, 2, std::bind(&Emulateur::adc, this, &p_n)}, \
{0b11001111, "rst $08\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 1)}, \
{0b11010000, "ret nc\n", 0, {_, _, _, _}, 0, std::bind(&Emulateur::ret, this)}, \
{0b11010001, "pop de\n", 0, {_, _, _, _}, 3, std::bind(&Emulateur::pop, this, &p_DE)}, \
{0b11010010, "jp nc, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::jp, this, &p_nn)}, \
{0b11010011, "NOT AN INSTRUCTION [0b11010011]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11010100, "call nc, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::call, this, &p_nn)}, \
{0b11010101, "push de\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::push, this, &p_DE)}, \
{0b11010110, "sub $%02hhX\n", 1, {SET, SET, SET_1, SET}, 2, std::bind(&Emulateur::sub, this, &p_n)}, \
{0b11010111, "rst $10\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 2)}, \
{0b11011000, "ret c\n", 0, {_, _, _, _}, 0, std::bind(&Emulateur::ret, this)}, \
{0b11011001, "reti\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::reti, this)}, \
{0b11011010, "jp c, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::jp, this, &p_nn)}, \
{0b11011011, "NOT AN INSTRUCTION [0b11011011]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11011100, "call c, $%02hX\n", 2, {_, _, _, _}, 0, std::bind(&Emulateur::call, this, &p_nn)}, \
{0b11011101, "NOT AN INSTRUCTION [0b11011101]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11011110, "sbc $%02hhX\n", 1, {SET, SET, SET_1, SET}, 2, std::bind(&Emulateur::sbc, this, &p_n)}, \
{0b11011111, "rst $18\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 3)}, \
{0b11100000, "ld [$FF%02hhX], a\n", 1, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_n_D, &p_A, 0, 1)}, \
{0b11100001, "pop hl\n", 0, {_, _, _, _}, 3, std::bind(&Emulateur::pop, this, &p_HL)}, \
{0b11100010, "ld [c], a\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_C_D, &p_A, 0, 1)}, \
{0b11100011, "NOT AN INSTRUCTION [0b11100011]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11100100, "NOT AN INSTRUCTION [0b11100100]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11100101, "push hl\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::push, this, &p_HL)}, \
{0b11100110, "and $%02hhX\n", 1, {SET_0, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::_and, this, &p_n)}, \
{0b11100111, "rst $20\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 4)}, \
{0b11101000, "add sp, $%02hhX\n", 1, {SET, SET, SET_0, SET_0}, 4, std::bind(&Emulateur::add, this, &p_SP, &p_e, 1)}, \
{0b11101001, "jp hl\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::jp, this, &p_HL)}, \
{0b11101010, "ld [$%02hX], a\n", 2, {_, _, _, _}, 4, std::bind(&Emulateur::ld, this, &p_nn_D1, &p_A, 0, 1)}, \
{0b11101011, "NOT AN INSTRUCTION [0b11101011]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11101100, "NOT AN INSTRUCTION [0b11101100]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11101101, "NOT AN INSTRUCTION [0b11101101]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11101110, "xor $%02hhX\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_xor, this, &p_n)}, \
{0b11101111, "rst $28\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 5)}, \
{0b11110000, "ld a, [$FF%02hhX]\n", 1, {_, _, _, _}, 3, std::bind(&Emulateur::ld, this, &p_A, &p_n_D, 0, 1)}, \
{0b11110001, "pop af\n", 0, {_, _, _, _}, 3, std::bind(&Emulateur::pop, this, &p_AF)}, \
{0b11110010, "ld a, [c]\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_A, &p_C_D, 0, 1)}, \
{0b11110011, "di\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::di, this)}, \
{0b11110100, "NOT AN INSTRUCTION [0b11110100]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11110101, "push af\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::push, this, &p_AF)}, \
{0b11110110, "or $%02hhX\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_or, this, &p_n)}, \
{0b11110111, "rst $30\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 6)}, \
{0b11111000, "ldhl sp, $%02hhX\n", 1, {SET, SET, SET_0, SET_0}, 3, std::bind(&Emulateur::ldhl, this, &p_e)}, \
{0b11111001, "ld sp, hl\n", 0, {_, _, _, _}, 2, std::bind(&Emulateur::ld, this, &p_SP, &p_HL, 0, 2)}, \
{0b11111010, "ld a, [$%02hX]\n", 2, {_, _, _, _}, 4, std::bind(&Emulateur::ld, this, &p_A, &p_nn_D1, 0, 1)}, \
{0b11111011, "ei\n", 0, {_, _, _, _}, 1, std::bind(&Emulateur::ei, this)}, \
{0b11111100, "NOT AN INSTRUCTION [0b11111100]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11111101, "NOT AN INSTRUCTION [0b11111101]\n", 0, {_, _, _, _}, 1, NULL}, \
{0b11111110, "cp $%02hhX\n", 1, {SET, SET, SET_1, SET}, 2, std::bind(&Emulateur::cp, this, &p_n)}, \
{0b11111111, "rst $38\n", 0, {_, _, _, _}, 4, std::bind(&Emulateur::rst, this, 7)}

#define CYCLE_VARIABLE_OPCODE \
{0b00100000, "jr nz, e\n", 3, 2, NZ}, \
{0b00101000, "jr z, e\n", 3, 2, Z}, \
{0b00110000, "jr nc, e\n", 3, 2, NC}, \
{0b00111000, "jr c, e\n", 3, 2, C}, \
{0b11000000, "ret nz\n", 5, 2, NZ}, \
{0b11000010, "jp nz, $%02hX\n", 4, 3, NZ}, \
{0b11000100, "call nz, $%02hX\n", 6, 3, NZ}, \
{0b11001000, "ret z\n", 5, 2, Z}, \
{0b11001010, "jp z, $%02hX\n", 4, 3, Z}, \
{0b11001100, "call z, $%02hX\n", 6, 3, Z}, \
{0b11010000, "ret nc\n", 5, 2, NC}, \
{0b11010010, "jp nc, $%02hX\n", 4, 3, NC}, \
{0b11010100, "call nc, $%02hX\n", 6, 3, NC}, \
{0b11011000, "ret c\n", 5, 2, C}, \
{0b11011010, "jp c, $%02hX\n", 4, 3, C}, \
{0b11011100, "call c, $%02hX\n", 6, 3, C}
#endif
