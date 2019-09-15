#ifndef OP203
# define OP203 \
{0b00000000, "rlc b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_B)}, \
{0b00000001, "rlc c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_C)}, \
{0b00000010, "rlc d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_D)}, \
{0b00000011, "rlc e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_E)}, \
{0b00000100, "rlc h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_H)}, \
{0b00000101, "rlc l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_L)}, \
{0b00000110, "rlc [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rlc, this, &p_HL_D1)}, \
{0b00000111, "rlc a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_A)}, \
{0b00001000, "rrc b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_B)}, \
{0b00001001, "rrc c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_C)}, \
{0b00001010, "rrc d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_D)}, \
{0b00001011, "rrc e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_E)}, \
{0b00001100, "rrc h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_H)}, \
{0b00001101, "rrc l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_L)}, \
{0b00001110, "rrc [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rrc, this, &p_HL_D1)}, \
{0b00001111, "rrc a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_A)}, \
{0b00010000, "rl b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_B)}, \
{0b00010001, "rl c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_C)}, \
{0b00010010, "rl d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_D)}, \
{0b00010011, "rl e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_E)}, \
{0b00010100, "rl h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_H)}, \
{0b00010101, "rl l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_L)}, \
{0b00010110, "rl [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rl, this, &p_HL_D1)}, \
{0b00010111, "rl a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_A)}, \
{0b00011000, "rr b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_B)}, \
{0b00011001, "rr c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_C)}, \
{0b00011010, "rr d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_D)}, \
{0b00011011, "rr e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_E)}, \
{0b00011100, "rr h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_H)}, \
{0b00011101, "rr l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_L)}, \
{0b00011110, "rr [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rr, this, &p_HL_D1)}, \
{0b00011111, "rr a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_A)}, \
{0b00100000, "sla b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_B)}, \
{0b00100001, "sla c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_C)}, \
{0b00100010, "sla d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_D)}, \
{0b00100011, "sla e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_E)}, \
{0b00100100, "sla h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_H)}, \
{0b00100101, "sla l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_L)}, \
{0b00100110, "sla [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::sla, this, &p_HL_D1)}, \
{0b00100111, "sla a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_A)}, \
{0b00101000, "sra b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_B)}, \
{0b00101001, "sra c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_C)}, \
{0b00101010, "sra d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_D)}, \
{0b00101011, "sra e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_E)}, \
{0b00101100, "sra h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_H)}, \
{0b00101101, "sra l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_L)}, \
{0b00101110, "sra [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::sra, this, &p_HL_D1)}, \
{0b00101111, "sra a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_A)}, \
{0b00110000, "swap b\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_B)}, \
{0b00110001, "swap c\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_C)}, \
{0b00110010, "swap d\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_D)}, \
{0b00110011, "swap e\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_E)}, \
{0b00110100, "swap h\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_H)}, \
{0b00110101, "swap l\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_L)}, \
{0b00110110, "swap [hl]\n", 1, {SET_0, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::_swap, this, &p_HL_D1)}, \
{0b00110111, "swap a\n", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_A)}, \
{0b00111000, "srl b\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_B)}, \
{0b00111001, "srl c\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_C)}, \
{0b00111010, "srl d\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_D)}, \
{0b00111011, "srl e\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_E)}, \
{0b00111100, "srl h\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_H)}, \
{0b00111101, "srl l\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_L)}, \
{0b00111110, "srl [hl]\n", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::srl, this, &p_HL_D1)}, \
{0b00111111, "srl a\n", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_A)}, \
{0b01000000, "bit $00, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 0)}, \
{0b01000001, "bit $00, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 0)}, \
{0b01000010, "bit $00, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 0)}, \
{0b01000011, "bit $00, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 0)}, \
{0b01000100, "bit $00, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 0)}, \
{0b01000101, "bit $00, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 0)}, \
{0b01000110, "bit $00, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 0)}, \
{0b01000111, "bit $00, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 0)}, \
{0b01001000, "bit $01, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 1)}, \
{0b01001001, "bit $01, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 1)}, \
{0b01001010, "bit $01, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 1)}, \
{0b01001011, "bit $01, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 1)}, \
{0b01001100, "bit $01, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 1)}, \
{0b01001101, "bit $01, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 1)}, \
{0b01001110, "bit $01, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 1)}, \
{0b01001111, "bit $01, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 1)}, \
{0b01010000, "bit $02, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 2)}, \
{0b01010001, "bit $02, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 2)}, \
{0b01010010, "bit $02, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 2)}, \
{0b01010011, "bit $02, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 2)}, \
{0b01010100, "bit $02, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 2)}, \
{0b01010101, "bit $02, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 2)}, \
{0b01010110, "bit $02, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 2)}, \
{0b01010111, "bit $02, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 2)}, \
{0b01011000, "bit $03, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 3)}, \
{0b01011001, "bit $03, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 3)}, \
{0b01011010, "bit $03, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 3)}, \
{0b01011011, "bit $03, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 3)}, \
{0b01011100, "bit $03, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 3)}, \
{0b01011101, "bit $03, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 3)}, \
{0b01011110, "bit $03, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 3)}, \
{0b01011111, "bit $03, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 3)}, \
{0b01100000, "bit $04, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 4)}, \
{0b01100001, "bit $04, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 4)}, \
{0b01100010, "bit $04, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 4)}, \
{0b01100011, "bit $04, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 4)}, \
{0b01100100, "bit $04, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 4)}, \
{0b01100101, "bit $04, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 4)}, \
{0b01100110, "bit $04, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 4)}, \
{0b01100111, "bit $04, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 4)}, \
{0b01101000, "bit $05, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 5)}, \
{0b01101001, "bit $05, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 5)}, \
{0b01101010, "bit $05, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 5)}, \
{0b01101011, "bit $05, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 5)}, \
{0b01101100, "bit $05, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 5)}, \
{0b01101101, "bit $05, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 5)}, \
{0b01101110, "bit $05, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 5)}, \
{0b01101111, "bit $05, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 5)}, \
{0b01110000, "bit $06, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 6)}, \
{0b01110001, "bit $06, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 6)}, \
{0b01110010, "bit $06, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 6)}, \
{0b01110011, "bit $06, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 6)}, \
{0b01110100, "bit $06, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 6)}, \
{0b01110101, "bit $06, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 6)}, \
{0b01110110, "bit $06, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 6)}, \
{0b01110111, "bit $06, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 6)}, \
{0b01111000, "bit $07, b\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 7)}, \
{0b01111001, "bit $07, c\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 7)}, \
{0b01111010, "bit $07, d\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 7)}, \
{0b01111011, "bit $07, e\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 7)}, \
{0b01111100, "bit $07, h\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 7)}, \
{0b01111101, "bit $07, l\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 7)}, \
{0b01111110, "bit $07, [hl]\n", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 7)}, \
{0b01111111, "bit $07, a\n", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 7)}, \
{0b10000000, "res $00, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 0)}, \
{0b10000001, "res $00, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 0)}, \
{0b10000010, "res $00, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 0)}, \
{0b10000011, "res $00, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 0)}, \
{0b10000100, "res $00, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 0)}, \
{0b10000101, "res $00, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 0)}, \
{0b10000110, "res $00, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 0)}, \
{0b10000111, "res $00, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 0)}, \
{0b10001000, "res $01, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 1)}, \
{0b10001001, "res $01, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 1)}, \
{0b10001010, "res $01, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 1)}, \
{0b10001011, "res $01, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 1)}, \
{0b10001100, "res $01, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 1)}, \
{0b10001101, "res $01, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 1)}, \
{0b10001110, "res $01, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 1)}, \
{0b10001111, "res $01, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 1)}, \
{0b10010000, "res $02, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 2)}, \
{0b10010001, "res $02, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 2)}, \
{0b10010010, "res $02, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 2)}, \
{0b10010011, "res $02, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 2)}, \
{0b10010100, "res $02, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 2)}, \
{0b10010101, "res $02, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 2)}, \
{0b10010110, "res $02, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 2)}, \
{0b10010111, "res $02, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 2)}, \
{0b10011000, "res $03, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 3)}, \
{0b10011001, "res $03, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 3)}, \
{0b10011010, "res $03, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 3)}, \
{0b10011011, "res $03, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 3)}, \
{0b10011100, "res $03, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 3)}, \
{0b10011101, "res $03, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 3)}, \
{0b10011110, "res $03, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 3)}, \
{0b10011111, "res $03, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 3)}, \
{0b10100000, "res $04, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 4)}, \
{0b10100001, "res $04, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 4)}, \
{0b10100010, "res $04, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 4)}, \
{0b10100011, "res $04, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 4)}, \
{0b10100100, "res $04, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 4)}, \
{0b10100101, "res $04, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 4)}, \
{0b10100110, "res $04, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 4)}, \
{0b10100111, "res $04, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 4)}, \
{0b10101000, "res $05, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 5)}, \
{0b10101001, "res $05, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 5)}, \
{0b10101010, "res $05, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 5)}, \
{0b10101011, "res $05, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 5)}, \
{0b10101100, "res $05, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 5)}, \
{0b10101101, "res $05, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 5)}, \
{0b10101110, "res $05, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 5)}, \
{0b10101111, "res $05, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 5)}, \
{0b10110000, "res $06, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 6)}, \
{0b10110001, "res $06, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 6)}, \
{0b10110010, "res $06, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 6)}, \
{0b10110011, "res $06, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 6)}, \
{0b10110100, "res $06, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 6)}, \
{0b10110101, "res $06, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 6)}, \
{0b10110110, "res $06, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 6)}, \
{0b10110111, "res $06, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 6)}, \
{0b10111000, "res $07, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 7)}, \
{0b10111001, "res $07, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 7)}, \
{0b10111010, "res $07, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 7)}, \
{0b10111011, "res $07, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 7)}, \
{0b10111100, "res $07, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 7)}, \
{0b10111101, "res $07, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 7)}, \
{0b10111110, "res $07, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 7)}, \
{0b10111111, "res $07, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 7)}, \
{0b11000000, "set $00, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 0)}, \
{0b11000001, "set $00, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 0)}, \
{0b11000010, "set $00, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 0)}, \
{0b11000011, "set $00, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 0)}, \
{0b11000100, "set $00, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 0)}, \
{0b11000101, "set $00, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 0)}, \
{0b11000110, "set $00, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 0)}, \
{0b11000111, "set $00, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 0)}, \
{0b11001000, "set $01, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 1)}, \
{0b11001001, "set $01, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 1)}, \
{0b11001010, "set $01, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 1)}, \
{0b11001011, "set $01, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 1)}, \
{0b11001100, "set $01, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 1)}, \
{0b11001101, "set $01, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 1)}, \
{0b11001110, "set $01, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 1)}, \
{0b11001111, "set $01, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 1)}, \
{0b11010000, "set $02, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 2)}, \
{0b11010001, "set $02, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 2)}, \
{0b11010010, "set $02, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 2)}, \
{0b11010011, "set $02, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 2)}, \
{0b11010100, "set $02, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 2)}, \
{0b11010101, "set $02, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 2)}, \
{0b11010110, "set $02, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 2)}, \
{0b11010111, "set $02, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 2)}, \
{0b11011000, "set $03, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 3)}, \
{0b11011001, "set $03, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 3)}, \
{0b11011010, "set $03, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 3)}, \
{0b11011011, "set $03, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 3)}, \
{0b11011100, "set $03, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 3)}, \
{0b11011101, "set $03, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 3)}, \
{0b11011110, "set $03, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 3)}, \
{0b11011111, "set $03, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 3)}, \
{0b11100000, "set $04, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 4)}, \
{0b11100001, "set $04, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 4)}, \
{0b11100010, "set $04, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 4)}, \
{0b11100011, "set $04, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 4)}, \
{0b11100100, "set $04, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 4)}, \
{0b11100101, "set $04, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 4)}, \
{0b11100110, "set $04, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 4)}, \
{0b11100111, "set $04, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 4)}, \
{0b11101000, "set $05, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 5)}, \
{0b11101001, "set $05, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 5)}, \
{0b11101010, "set $05, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 5)}, \
{0b11101011, "set $05, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 5)}, \
{0b11101100, "set $05, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 5)}, \
{0b11101101, "set $05, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 5)}, \
{0b11101110, "set $05, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 5)}, \
{0b11101111, "set $05, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 5)}, \
{0b11110000, "set $06, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 6)}, \
{0b11110001, "set $06, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 6)}, \
{0b11110010, "set $06, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 6)}, \
{0b11110011, "set $06, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 6)}, \
{0b11110100, "set $06, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 6)}, \
{0b11110101, "set $06, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 6)}, \
{0b11110110, "set $06, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 6)}, \
{0b11110111, "set $06, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 6)}, \
{0b11111000, "set $07, b\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 7)}, \
{0b11111001, "set $07, c\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 7)}, \
{0b11111010, "set $07, d\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 7)}, \
{0b11111011, "set $07, e\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 7)}, \
{0b11111100, "set $07, h\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 7)}, \
{0b11111101, "set $07, l\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 7)}, \
{0b11111110, "set $07, [hl]\n", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 7)}, \
{0b11111111, "set $07, a\n", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 7)}
#endif
