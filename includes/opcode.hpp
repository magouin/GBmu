#ifndef OPCODE
# define OPCODE \
{0b00000000, "NOP", 0, {_, _, _, _}, std::bind(&Emulateur::nop, this, 1)}, \
{0b00000001, "LD BC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_BC, &p_nn, 0, 2, 3)}, \
{0b00000010, "LD (BC), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_BC_D1, &p_A, 0, 1, 2)}, \
{0b00000011, "INC BC", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &p_BC, 2)}, \
{0b00000100, "INC B", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_B, 1)}, \
{0b00000101, "DEC B", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_B, 1)}, \
{0b00000110, "LD B, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_n, 0, 1, 2)}, \
{0b00000111, "RLCA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rlca, this, 1)}, \
{0b00001000, "LD (nn), SP", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_nn_D2, &p_SP, 0, 2, 5)}, \
{0b00001001, "ADD HL, BC", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &p_HL, &p_BC, 2, 2)}, \
{0b00001010, "LD A, (BC)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_BC_D1, 0, 1, 2)}, \
{0b00001011, "DEC BC", 0, {_, _, _, _}, std::bind(&Emulateur::dec, this, &p_BC, 2)}, \
{0b00001100, "INC C", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_C, 1)}, \
{0b00001101, "DEC C", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_C, 1)}, \
{0b00001110, "LD C, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_n, 0, 1, 2)}, \
{0b00001111, "RRCA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rrca, this, 1)}, \
{0b00010000, "STOP", 1, {_, _, _, _}, std::bind(&Emulateur::stop, this, 1)}, \
{0b00010001, "LD DE, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_DE, &p_nn, 0, 2, 3)}, \
{0b00010010, "LD (DE), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_DE_D1, &p_A, 0, 1, 2)}, \
{0b00010011, "INC DE", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &p_DE, 2)}, \
{0b00010100, "INC D", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_D, 1)}, \
{0b00010101, "DEC D", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_D, 1)}, \
{0b00010110, "LD D, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_n, 0, 1, 2)}, \
{0b00010111, "RLA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rla, this, 1)}, \
{0b00011000, "JR e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, &p_e, EMPTY)}, \
{0b00011001, "ADD HL, DE", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &p_HL, &p_DE, 2, 2)}, \
{0b00011010, "LD A, (DE)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_DE_D1, 0, 1, 2)}, \
{0b00011011, "DEC DE", 0, {_, _, _, _}, std::bind(&Emulateur::dec, this, &p_DE, 2)}, \
{0b00011100, "INC E", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_E, 1)}, \
{0b00011101, "DEC E", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_E, 1)}, \
{0b00011110, "LD E, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_n, 0, 1, 2)}, \
{0b00011111, "RRA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rra, this, 1)}, \
{0b00100000, "JR NZ, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, &p_e, NZ)}, \
{0b00100001, "LD HL, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL, &p_nn, 0, 2, 3)}, \
{0b00100010, "LD (HLI), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_A, 1, 1, 2)}, \
{0b00100011, "INC HL", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &p_HL, 2)}, \
{0b00100100, "INC H", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_H, 1)}, \
{0b00100101, "DEC H", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_H, 1)}, \
{0b00100110, "LD H, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_n, 0, 1, 2)}, \
{0b00100111, "DAA", 0, {SET, SET_0, _, SET}, std::bind(&Emulateur::daa, this, 1)}, \
{0b00101000, "JR Z, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, &p_e, Z)}, \
{0b00101001, "ADD HL, HL", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &p_HL, &p_HL, 2, 2)}, \
{0b00101010, "LD A, (HLI)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_HL_D1, 1, 1, 2)}, \
{0b00101011, "DEC HL", 0, {_, _, _, _}, std::bind(&Emulateur::dec, this, &p_HL, 2)}, \
{0b00101100, "INC L", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_L, 1)}, \
{0b00101101, "DEC L", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_L, 1)}, \
{0b00101110, "LD L, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_n, 0, 1, 2)}, \
{0b00101111, "CPL", 0, {_, SET_1, SET_1, _}, std::bind(&Emulateur::cpl, this, 1)}, \
{0b00110000, "JR NC, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, &p_e, NC)}, \
{0b00110001, "LD SP, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_SP, &p_nn, 0, 2, 3)}, \
{0b00110010, "LD (HLD), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_A, -1, 1, 2)}, \
{0b00110011, "INC SP", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &p_SP, 2)}, \
{0b00110100, "INC (HL)", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_HL_D1, 3)}, \
{0b00110101, "DEC (HL)", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_HL_D1, 3)}, \
{0b00110110, "LD (HL), n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_n, 0, 1, 3)}, \
{0b00110111, "SCF", 0, {_, _, _, _}}, \
{0b00111000, "JR C, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, &p_e, C)}, \
{0b00111001, "ADD HL, SP", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &p_HL, &p_SP, 2, 2)}, \
{0b00111010, "LD A, (HLD)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_HL_D1, -1, 1, 2)}, \
{0b00111011, "DEC SP", 0, {_, _, _, _}, std::bind(&Emulateur::dec, this, &p_SP, 2)}, \
{0b00111100, "INC A", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &p_A, 1)}, \
{0b00111101, "DEC A", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::dec, this, &p_A, 1)}, \
{0b00111110, "LD A, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_n, 0, 1, 2)}, \
{0b00111111, "CCF", 0, {_, _, _, _}, std::bind(&Emulateur::ccf, this, 0)}, \
{0b01000000, "LD B, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_B, 0, 1, 1)}, \
{0b01000001, "LD B, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_C, 0, 1, 1)}, \
{0b01000010, "LD B, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_D, 0, 1, 1)}, \
{0b01000011, "LD B, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_E, 0, 1, 1)}, \
{0b01000100, "LD B, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_H, 0, 1, 1)}, \
{0b01000101, "LD B, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_L, 0, 1, 1)}, \
{0b01000110, "LD B, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_HL_D1, 0, 1, 2)}, \
{0b01000111, "LD B, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_B, &p_A, 0, 1, 1)}, \
{0b01001000, "LD C, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_B, 0, 1, 1)}, \
{0b01001001, "LD C, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_C, 0, 1, 1)}, \
{0b01001010, "LD C, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_D, 0, 1, 1)}, \
{0b01001011, "LD C, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_E, 0, 1, 1)}, \
{0b01001100, "LD C, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_H, 0, 1, 1)}, \
{0b01001101, "LD C, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_L, 0, 1, 1)}, \
{0b01001110, "LD C, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_HL_D1, 0, 1, 2)}, \
{0b01001111, "LD C, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C, &p_A, 0, 1, 1)}, \
{0b01010000, "LD D, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_B, 0, 1, 1)}, \
{0b01010001, "LD D, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_C, 0, 1, 1)}, \
{0b01010010, "LD D, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_D, 0, 1, 1)}, \
{0b01010011, "LD D, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_E, 0, 1, 1)}, \
{0b01010100, "LD D, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_H, 0, 1, 1)}, \
{0b01010101, "LD D, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_L, 0, 1, 1)}, \
{0b01010110, "LD D, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_HL_D1, 0, 1, 2)}, \
{0b01010111, "LD D, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_D, &p_A, 0, 1, 1)}, \
{0b01011000, "LD E, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_B, 0, 1, 1)}, \
{0b01011001, "LD E, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_C, 0, 1, 1)}, \
{0b01011010, "LD E, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_D, 0, 1, 1)}, \
{0b01011011, "LD E, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_E, 0, 1, 1)}, \
{0b01011100, "LD E, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_H, 0, 1, 1)}, \
{0b01011101, "LD E, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_L, 0, 1, 1)}, \
{0b01011110, "LD E, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_HL_D1, 0, 1, 2)}, \
{0b01011111, "LD E, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_E, &p_A, 0, 1, 1)}, \
{0b01100000, "LD H, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_B, 0, 1, 1)}, \
{0b01100001, "LD H, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_C, 0, 1, 1)}, \
{0b01100010, "LD H, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_D, 0, 1, 1)}, \
{0b01100011, "LD H, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_E, 0, 1, 1)}, \
{0b01100100, "LD H, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_H, 0, 1, 1)}, \
{0b01100101, "LD H, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_L, 0, 1, 1)}, \
{0b01100110, "LD H, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_HL_D1, 0, 1, 2)}, \
{0b01100111, "LD H, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_H, &p_A, 0, 1, 1)}, \
{0b01101000, "LD L, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_B, 0, 1, 1)}, \
{0b01101001, "LD L, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_C, 0, 1, 1)}, \
{0b01101010, "LD L, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_D, 0, 1, 1)}, \
{0b01101011, "LD L, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_E, 0, 1, 1)}, \
{0b01101100, "LD L, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_H, 0, 1, 1)}, \
{0b01101101, "LD L, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_L, 0, 1, 1)}, \
{0b01101110, "LD L, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_HL_D1, 0, 1, 2)}, \
{0b01101111, "LD L, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_L, &p_A, 0, 1, 1)}, \
{0b01110000, "LD (HL), B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_B, 0, 1, 2)}, \
{0b01110001, "LD (HL), C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_C, 0, 1, 2)}, \
{0b01110010, "LD (HL), D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_D, 0, 1, 2)}, \
{0b01110011, "LD (HL), E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_E, 0, 1, 2)}, \
{0b01110100, "LD (HL), H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_H, 0, 1, 2)}, \
{0b01110101, "LD (HL), L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_L, 0, 1, 2)}, \
{0b01110110, "HALT", 0, {_, _, _, _}, std::bind(&Emulateur::halt, this, 1)}, \
{0b01110111, "LD (HL), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_HL_D1, &p_A, 0, 1, 2)}, \
{0b01111000, "LD A, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_B, 0, 1, 1)}, \
{0b01111001, "LD A, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_C, 0, 1, 1)}, \
{0b01111010, "LD A, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_D, 0, 1, 1)}, \
{0b01111011, "LD A, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_E, 0, 1, 1)}, \
{0b01111100, "LD A, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_H, 0, 1, 1)}, \
{0b01111101, "LD A, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_L, 0, 1, 1)}, \
{0b01111110, "LD A, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_HL_D1, 0, 1, 2)}, \
{0b01111111, "LD A, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_A, 0, 1, 1)}, \
{0b10000000, "ADD A, B", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_B, 1, 1)}, \
{0b10000001, "ADD A, C", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_C, 1, 1)}, \
{0b10000010, "ADD A, D", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_D, 1, 1)}, \
{0b10000011, "ADD A, E", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_E, 1, 1)}, \
{0b10000100, "ADD A, H", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_H, 1, 1)}, \
{0b10000101, "ADD A, L", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_L, 1, 1)}, \
{0b10000110, "ADD A, (HL)", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_HL_D1, 1, 2)}, \
{0b10000111, "ADD A, A", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_A, 1, 1)}, \
{0b10001000, "ADC A, B", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_B, 1)}, \
{0b10001001, "ADC A, C", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_C, 1)}, \
{0b10001010, "ADC A, D", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_D, 1)}, \
{0b10001011, "ADC A, E", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_E, 1)}, \
{0b10001100, "ADC A, H", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_H, 1)}, \
{0b10001101, "ADC A, L", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_L, 1)}, \
{0b10001110, "ADC A, (HL)", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_HL_D1, 2)}, \
{0b10001111, "ADC A, A", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_A, 1)}, \
{0b10010000, "SUB B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_B, 1)}, \
{0b10010001, "SUB C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_C, 1)}, \
{0b10010010, "SUB D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_D, 1)}, \
{0b10010011, "SUB E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_E, 1)}, \
{0b10010100, "SUB H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_H, 1)}, \
{0b10010101, "SUB L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_L, 1)}, \
{0b10010110, "SUB (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_HL_D1, 2)}, \
{0b10010111, "SUB A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_A, 1)}, \
{0b10011000, "SBC B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_B, 1)}, \
{0b10011001, "SBC C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_C, 1)}, \
{0b10011010, "SBC D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_D, 1)}, \
{0b10011011, "SBC E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_E, 1)}, \
{0b10011100, "SBC H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_H, 1)}, \
{0b10011101, "SBC L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_L, 1)}, \
{0b10011110, "SBC (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_HL_D1, 2)}, \
{0b10011111, "SBC A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_A, 1)}, \
{0b10100000, "AND B", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_B, 1)}, \
{0b10100001, "AND C", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_C, 1)}, \
{0b10100010, "AND D", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_D, 1)}, \
{0b10100011, "AND E", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_E, 1)}, \
{0b10100100, "AND H", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_H, 1)}, \
{0b10100101, "AND L", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_L, 1)}, \
{0b10100110, "AND (HL)", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_HL_D1, 2)}, \
{0b10100111, "AND A", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_A, 1)}, \
{0b10101000, "XOR B", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_B, 1)}, \
{0b10101001, "XOR C", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_C, 1)}, \
{0b10101010, "XOR D", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_D, 1)}, \
{0b10101011, "XOR E", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_E, 1)}, \
{0b10101100, "XOR H", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_H, 1)}, \
{0b10101101, "XOR L", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_L, 1)}, \
{0b10101110, "XOR (HL)", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_HL_D1, 2)}, \
{0b10101111, "XOR A", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_A, 1)}, \
{0b10110000, "OR B", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_B, 1)}, \
{0b10110001, "OR C", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_C, 1)}, \
{0b10110010, "OR D", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_D, 1)}, \
{0b10110011, "OR E", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_E, 1)}, \
{0b10110100, "OR H", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_H, 1)}, \
{0b10110101, "OR L", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_L, 1)}, \
{0b10110110, "OR (HL)", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_HL_D1, 2)}, \
{0b10110111, "OR A", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_A, 1)}, \
{0b10111000, "CP B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_B, 1)}, \
{0b10111001, "CP C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_C, 1)}, \
{0b10111010, "CP D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_D, 1)}, \
{0b10111011, "CP E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_E, 1)}, \
{0b10111100, "CP H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_H, 1)}, \
{0b10111101, "CP L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_L, 1)}, \
{0b10111110, "CP (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_HL_D1, 2)}, \
{0b10111111, "CP A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_A, 1)}, \
{0b11000000, "RET NZ", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, NZ)}, \
{0b11000001, "POP BC", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &p_BC, 3)}, \
{0b11000010, "JP NZ, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, &p_nn, NZ)}, \
{0b11000011, "JP nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, &p_nn, EMPTY)}, \
{0b11000100, "CALL NZ, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, &p_nn, NZ)}, \
{0b11000101, "PUSH BC", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &p_BC, 4)}, \
{0b11000110, "ADD A, n", 1, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &p_A, &p_n, 1, 2)}, \
{0b11000111, "RST 0", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 0, 4)}, \
{0b11001000, "RET Z", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, Z)}, \
{0b11001001, "RET", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, EMPTY)}, \
{0b11001010, "JP Z, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, &p_nn, Z)}, \
{0b11001011, "op203", 0, {SET, SET, SET, SET}, std::bind(&Emulateur::op203, this)}, \
{0b11001100, "CALL Z, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, &p_nn, Z)}, \
{0b11001101, "CALL nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, &p_nn, EMPTY)}, \
{0b11001110, "ADC A, n", 1, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &p_n, 2)}, \
{0b11001111, "RST 1", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 1, 4)}, \
{0b11010000, "RET NC", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, NC)}, \
{0b11010001, "POP DE", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &p_DE, 3)}, \
{0b11010010, "JP NC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, &p_nn, NC)}, \
{0b11010011, "NOT AN INSTRUCTION (0b11010011)", 0, {_, _, _, _}}, \
{0b11010100, "CALL NC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, &p_nn, NC)}, \
{0b11010101, "PUSH DE", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &p_DE, 4)}, \
{0b11010110, "SUB n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &p_n, 2)}, \
{0b11010111, "RST 2", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 2, 4)}, \
{0b11011000, "RET C", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, C)}, \
{0b11011001, "RETI", 0, {_, _, _, _}, std::bind(&Emulateur::reti, this, 4)}, \
{0b11011010, "JP C, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, &p_nn, C)}, \
{0b11011011, "NOT AN INSTRUCTION (0b11011011)", 0, {_, _, _, _}}, \
{0b11011100, "CALL C, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, &p_nn, C)}, \
{0b11011101, "NOT AN INSTRUCTION (0b11011101)", 0, {_, _, _, _}}, \
{0b11011110, "SBC n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &p_n, 2)}, \
{0b11011111, "RST 3", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 3, 4)}, \
{0b11100000, "LD (n), A", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_n_D, &p_A, 0, 1, 3)}, \
{0b11100001, "POP HL", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &p_HL, 3)}, \
{0b11100010, "LD (C), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_C_D, &p_A, 0, 1, 2)}, \
{0b11100011, "NOT AN INSTRUCTION (0b11100011)", 0, {_, _, _, _}}, \
{0b11100100, "NOT AN INSTRUCTION (0b11100100)", 0, {_, _, _, _}}, \
{0b11100101, "PUSH HL", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &p_HL, 4)}, \
{0b11100110, "AND n", 1, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &p_n, 2)}, \
{0b11100111, "RST 4", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 4, 4)}, \
{0b11101000, "ADD SP, e", 1, {SET, SET, SET_0, SET_0}, std::bind(&Emulateur::add, this, &p_SP, &p_e, 2, 4)}, \
{0b11101001, "JP HL", 0, {_, _, _, _}, std::bind(&Emulateur::jp, this, &p_HL, EMPTY)}, \
{0b11101010, "LD (nn), A", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_nn_D1, &p_A, 0, 1, 4)}, \
{0b11101011, "NOT AN INSTRUCTION (0b11101011)", 0, {_, _, _, _}}, \
{0b11101100, "NOT AN INSTRUCTION (0b11101100)", 0, {_, _, _, _}}, \
{0b11101101, "NOT AN INSTRUCTION (0b11101101)", 0, {_, _, _, _}}, \
{0b11101110, "XOR n", 1, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &p_n, 2)}, \
{0b11101111, "RST 5", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 5, 4)}, \
{0b11110000, "LD A, (n)", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_n_D, 0, 1, 3)}, \
{0b11110001, "POP AF", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &p_AF, 3)}, \
{0b11110010, "LD A, (C)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_C_D, 0, 1, 2)}, \
{0b11110011, "DI", 0, {_, _, _, _}, std::bind(&Emulateur::di, this, 1)}, \
{0b11110100, "NOT AN INSTRUCTION (0b11110100)", 0, {_, _, _, _}}, \
{0b11110101, "PUSH AF", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &p_AF, 4)}, \
{0b11110110, "OR n", 1, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &p_n, 2)}, \
{0b11110111, "RST 6", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 6, 4)}, \
{0b11111000, "LDHL SP, e", 1, {SET, SET, SET_0, SET_0}, std::bind(&Emulateur::ldhl, this, &p_e, 3)}, \
{0b11111001, "LD SP, HL", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_SP, &p_HL, 0, 2, 2)}, \
{0b11111010, "LD A, (nn)", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, &p_A, &p_nn_D1, 0, 1, 4)}, \
{0b11111011, "EI", 0, {_, _, _, _}, std::bind(&Emulateur::ei, this, 1)}, \
{0b11111100, "NOT AN INSTRUCTION (0b11111100)", 0, {_, _, _, _}}, \
{0b11111101, "NOT AN INSTRUCTION (0b11111101)", 0, {_, _, _, _}}, \
{0b11111110, "CP n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &p_n, 2)}, \
{0b11111111, "RST 7", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 7, 4)}
#endif
