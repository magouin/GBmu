#ifndef OP203
# define OP203 \
{0b00000000, "RLC B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_B)}, \
{0b00000001, "RLC C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_C)}, \
{0b00000010, "RLC D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_D)}, \
{0b00000011, "RLC E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_E)}, \
{0b00000100, "RLC H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_H)}, \
{0b00000101, "RLC L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_L)}, \
{0b00000110, "RLC (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rlc, this, &p_HL_D1)}, \
{0b00000111, "RLC A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rlc, this, &p_A)}, \
{0b00001000, "RRC B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_B)}, \
{0b00001001, "RRC C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_C)}, \
{0b00001010, "RRC D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_D)}, \
{0b00001011, "RRC E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_E)}, \
{0b00001100, "RRC H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_H)}, \
{0b00001101, "RRC L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_L)}, \
{0b00001110, "RRC (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rrc, this, &p_HL_D1)}, \
{0b00001111, "RRC A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rrc, this, &p_A)}, \
{0b00010000, "RL B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_B)}, \
{0b00010001, "RL C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_C)}, \
{0b00010010, "RL D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_D)}, \
{0b00010011, "RL E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_E)}, \
{0b00010100, "RL H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_H)}, \
{0b00010101, "RL L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_L)}, \
{0b00010110, "RL (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rl, this, &p_HL_D1)}, \
{0b00010111, "RL A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rl, this, &p_A)}, \
{0b00011000, "RR B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_B)}, \
{0b00011001, "RR C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_C)}, \
{0b00011010, "RR D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_D)}, \
{0b00011011, "RR E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_E)}, \
{0b00011100, "RR H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_H)}, \
{0b00011101, "RR L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_L)}, \
{0b00011110, "RR (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::rr, this, &p_HL_D1)}, \
{0b00011111, "RR A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::rr, this, &p_A)}, \
{0b00100000, "SLA B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_B)}, \
{0b00100001, "SLA C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_C)}, \
{0b00100010, "SLA D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_D)}, \
{0b00100011, "SLA E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_E)}, \
{0b00100100, "SLA H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_H)}, \
{0b00100101, "SLA L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_L)}, \
{0b00100110, "SLA (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::sla, this, &p_HL_D1)}, \
{0b00100111, "SLA A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sla, this, &p_A)}, \
{0b00101000, "SRA B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_B)}, \
{0b00101001, "SRA C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_C)}, \
{0b00101010, "SRA D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_D)}, \
{0b00101011, "SRA E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_E)}, \
{0b00101100, "SRA H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_H)}, \
{0b00101101, "SRA L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_L)}, \
{0b00101110, "SRA (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::sra, this, &p_HL_D1)}, \
{0b00101111, "SRA A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::sra, this, &p_A)}, \
{0b00110000, "SWAP B", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_B)}, \
{0b00110001, "SWAP C", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_C)}, \
{0b00110010, "SWAP D", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_D)}, \
{0b00110011, "SWAP E", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_E)}, \
{0b00110100, "SWAP H", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_H)}, \
{0b00110101, "SWAP L", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_L)}, \
{0b00110110, "SWAP (HL)", 1, {SET_0, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::_swap, this, &p_HL_D1)}, \
{0b00110111, "SWAP A", 1, {SET_0, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::_swap, this, &p_A)}, \
{0b00111000, "SRL B", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_B)}, \
{0b00111001, "SRL C", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_C)}, \
{0b00111010, "SRL D", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_D)}, \
{0b00111011, "SRL E", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_E)}, \
{0b00111100, "SRL H", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_H)}, \
{0b00111101, "SRL L", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_L)}, \
{0b00111110, "SRL (HL)", 1, {SET, SET_0, SET_0, SET}, 4, std::bind(&Emulateur::srl, this, &p_HL_D1)}, \
{0b00111111, "SRL A", 1, {SET, SET_0, SET_0, SET}, 2, std::bind(&Emulateur::srl, this, &p_A)}, \
{0b01000000, "BIT 0, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 0)}, \
{0b01000001, "BIT 0, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 0)}, \
{0b01000010, "BIT 0, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 0)}, \
{0b01000011, "BIT 0, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 0)}, \
{0b01000100, "BIT 0, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 0)}, \
{0b01000101, "BIT 0, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 0)}, \
{0b01000110, "BIT 0, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 0)}, \
{0b01000111, "BIT 0, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 0)}, \
{0b01001000, "BIT 1, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 1)}, \
{0b01001001, "BIT 1, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 1)}, \
{0b01001010, "BIT 1, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 1)}, \
{0b01001011, "BIT 1, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 1)}, \
{0b01001100, "BIT 1, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 1)}, \
{0b01001101, "BIT 1, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 1)}, \
{0b01001110, "BIT 1, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 1)}, \
{0b01001111, "BIT 1, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 1)}, \
{0b01010000, "BIT 2, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 2)}, \
{0b01010001, "BIT 2, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 2)}, \
{0b01010010, "BIT 2, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 2)}, \
{0b01010011, "BIT 2, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 2)}, \
{0b01010100, "BIT 2, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 2)}, \
{0b01010101, "BIT 2, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 2)}, \
{0b01010110, "BIT 2, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 2)}, \
{0b01010111, "BIT 2, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 2)}, \
{0b01011000, "BIT 3, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 3)}, \
{0b01011001, "BIT 3, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 3)}, \
{0b01011010, "BIT 3, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 3)}, \
{0b01011011, "BIT 3, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 3)}, \
{0b01011100, "BIT 3, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 3)}, \
{0b01011101, "BIT 3, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 3)}, \
{0b01011110, "BIT 3, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 3)}, \
{0b01011111, "BIT 3, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 3)}, \
{0b01100000, "BIT 4, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 4)}, \
{0b01100001, "BIT 4, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 4)}, \
{0b01100010, "BIT 4, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 4)}, \
{0b01100011, "BIT 4, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 4)}, \
{0b01100100, "BIT 4, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 4)}, \
{0b01100101, "BIT 4, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 4)}, \
{0b01100110, "BIT 4, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 4)}, \
{0b01100111, "BIT 4, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 4)}, \
{0b01101000, "BIT 5, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 5)}, \
{0b01101001, "BIT 5, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 5)}, \
{0b01101010, "BIT 5, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 5)}, \
{0b01101011, "BIT 5, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 5)}, \
{0b01101100, "BIT 5, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 5)}, \
{0b01101101, "BIT 5, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 5)}, \
{0b01101110, "BIT 5, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 5)}, \
{0b01101111, "BIT 5, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 5)}, \
{0b01110000, "BIT 6, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 6)}, \
{0b01110001, "BIT 6, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 6)}, \
{0b01110010, "BIT 6, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 6)}, \
{0b01110011, "BIT 6, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 6)}, \
{0b01110100, "BIT 6, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 6)}, \
{0b01110101, "BIT 6, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 6)}, \
{0b01110110, "BIT 6, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 6)}, \
{0b01110111, "BIT 6, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 6)}, \
{0b01111000, "BIT 7, B", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_B, 7)}, \
{0b01111001, "BIT 7, C", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_C, 7)}, \
{0b01111010, "BIT 7, D", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_D, 7)}, \
{0b01111011, "BIT 7, E", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_E, 7)}, \
{0b01111100, "BIT 7, H", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_H, 7)}, \
{0b01111101, "BIT 7, L", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_L, 7)}, \
{0b01111110, "BIT 7, (HL)", 1, {_, SET_1, SET_0, SET}, 3, std::bind(&Emulateur::bit, this, &p_HL_D1, 7)}, \
{0b01111111, "BIT 7, A", 1, {_, SET_1, SET_0, SET}, 2, std::bind(&Emulateur::bit, this, &p_A, 7)}, \
{0b10000000, "RES 0, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 0)}, \
{0b10000001, "RES 0, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 0)}, \
{0b10000010, "RES 0, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 0)}, \
{0b10000011, "RES 0, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 0)}, \
{0b10000100, "RES 0, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 0)}, \
{0b10000101, "RES 0, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 0)}, \
{0b10000110, "RES 0, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 0)}, \
{0b10000111, "RES 0, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 0)}, \
{0b10001000, "RES 1, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 1)}, \
{0b10001001, "RES 1, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 1)}, \
{0b10001010, "RES 1, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 1)}, \
{0b10001011, "RES 1, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 1)}, \
{0b10001100, "RES 1, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 1)}, \
{0b10001101, "RES 1, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 1)}, \
{0b10001110, "RES 1, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 1)}, \
{0b10001111, "RES 1, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 1)}, \
{0b10010000, "RES 2, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 2)}, \
{0b10010001, "RES 2, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 2)}, \
{0b10010010, "RES 2, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 2)}, \
{0b10010011, "RES 2, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 2)}, \
{0b10010100, "RES 2, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 2)}, \
{0b10010101, "RES 2, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 2)}, \
{0b10010110, "RES 2, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 2)}, \
{0b10010111, "RES 2, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 2)}, \
{0b10011000, "RES 3, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 3)}, \
{0b10011001, "RES 3, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 3)}, \
{0b10011010, "RES 3, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 3)}, \
{0b10011011, "RES 3, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 3)}, \
{0b10011100, "RES 3, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 3)}, \
{0b10011101, "RES 3, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 3)}, \
{0b10011110, "RES 3, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 3)}, \
{0b10011111, "RES 3, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 3)}, \
{0b10100000, "RES 4, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 4)}, \
{0b10100001, "RES 4, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 4)}, \
{0b10100010, "RES 4, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 4)}, \
{0b10100011, "RES 4, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 4)}, \
{0b10100100, "RES 4, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 4)}, \
{0b10100101, "RES 4, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 4)}, \
{0b10100110, "RES 4, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 4)}, \
{0b10100111, "RES 4, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 4)}, \
{0b10101000, "RES 5, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 5)}, \
{0b10101001, "RES 5, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 5)}, \
{0b10101010, "RES 5, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 5)}, \
{0b10101011, "RES 5, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 5)}, \
{0b10101100, "RES 5, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 5)}, \
{0b10101101, "RES 5, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 5)}, \
{0b10101110, "RES 5, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 5)}, \
{0b10101111, "RES 5, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 5)}, \
{0b10110000, "RES 6, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 6)}, \
{0b10110001, "RES 6, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 6)}, \
{0b10110010, "RES 6, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 6)}, \
{0b10110011, "RES 6, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 6)}, \
{0b10110100, "RES 6, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 6)}, \
{0b10110101, "RES 6, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 6)}, \
{0b10110110, "RES 6, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 6)}, \
{0b10110111, "RES 6, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 6)}, \
{0b10111000, "RES 7, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_B, 7)}, \
{0b10111001, "RES 7, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_C, 7)}, \
{0b10111010, "RES 7, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_D, 7)}, \
{0b10111011, "RES 7, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_E, 7)}, \
{0b10111100, "RES 7, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_H, 7)}, \
{0b10111101, "RES 7, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_L, 7)}, \
{0b10111110, "RES 7, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::res, this, &p_HL_D1, 7)}, \
{0b10111111, "RES 7, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::res, this, &p_A, 7)}, \
{0b11000000, "SET 0, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 0)}, \
{0b11000001, "SET 0, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 0)}, \
{0b11000010, "SET 0, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 0)}, \
{0b11000011, "SET 0, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 0)}, \
{0b11000100, "SET 0, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 0)}, \
{0b11000101, "SET 0, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 0)}, \
{0b11000110, "SET 0, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 0)}, \
{0b11000111, "SET 0, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 0)}, \
{0b11001000, "SET 1, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 1)}, \
{0b11001001, "SET 1, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 1)}, \
{0b11001010, "SET 1, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 1)}, \
{0b11001011, "SET 1, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 1)}, \
{0b11001100, "SET 1, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 1)}, \
{0b11001101, "SET 1, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 1)}, \
{0b11001110, "SET 1, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 1)}, \
{0b11001111, "SET 1, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 1)}, \
{0b11010000, "SET 2, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 2)}, \
{0b11010001, "SET 2, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 2)}, \
{0b11010010, "SET 2, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 2)}, \
{0b11010011, "SET 2, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 2)}, \
{0b11010100, "SET 2, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 2)}, \
{0b11010101, "SET 2, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 2)}, \
{0b11010110, "SET 2, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 2)}, \
{0b11010111, "SET 2, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 2)}, \
{0b11011000, "SET 3, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 3)}, \
{0b11011001, "SET 3, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 3)}, \
{0b11011010, "SET 3, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 3)}, \
{0b11011011, "SET 3, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 3)}, \
{0b11011100, "SET 3, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 3)}, \
{0b11011101, "SET 3, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 3)}, \
{0b11011110, "SET 3, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 3)}, \
{0b11011111, "SET 3, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 3)}, \
{0b11100000, "SET 4, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 4)}, \
{0b11100001, "SET 4, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 4)}, \
{0b11100010, "SET 4, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 4)}, \
{0b11100011, "SET 4, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 4)}, \
{0b11100100, "SET 4, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 4)}, \
{0b11100101, "SET 4, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 4)}, \
{0b11100110, "SET 4, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 4)}, \
{0b11100111, "SET 4, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 4)}, \
{0b11101000, "SET 5, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 5)}, \
{0b11101001, "SET 5, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 5)}, \
{0b11101010, "SET 5, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 5)}, \
{0b11101011, "SET 5, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 5)}, \
{0b11101100, "SET 5, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 5)}, \
{0b11101101, "SET 5, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 5)}, \
{0b11101110, "SET 5, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 5)}, \
{0b11101111, "SET 5, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 5)}, \
{0b11110000, "SET 6, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 6)}, \
{0b11110001, "SET 6, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 6)}, \
{0b11110010, "SET 6, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 6)}, \
{0b11110011, "SET 6, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 6)}, \
{0b11110100, "SET 6, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 6)}, \
{0b11110101, "SET 6, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 6)}, \
{0b11110110, "SET 6, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 6)}, \
{0b11110111, "SET 6, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 6)}, \
{0b11111000, "SET 7, B", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_B, 7)}, \
{0b11111001, "SET 7, C", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_C, 7)}, \
{0b11111010, "SET 7, D", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_D, 7)}, \
{0b11111011, "SET 7, E", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_E, 7)}, \
{0b11111100, "SET 7, H", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_H, 7)}, \
{0b11111101, "SET 7, L", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_L, 7)}, \
{0b11111110, "SET 7, (HL)", 1, {_, SET_1, SET_0, _}, 4, std::bind(&Emulateur::set, this, &p_HL_D1, 7)}, \
{0b11111111, "SET 7, A", 1, {_, SET_1, SET_0, _}, 2, std::bind(&Emulateur::set, this, &p_A, 7)}
#endif
