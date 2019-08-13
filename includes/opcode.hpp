#ifndef OPCODE
# define OPCODE \
{0b00000000, "NOP", 0, {_, _, _, _}, std::bind(&Emulateur::nop, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00000001, "LD DE, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.BC, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)}, \
{0b00000010, "LD (BC), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.BC, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b00000011, "INC BC", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &regs.bc.BC, (struct s_params){ADDR_x64, ADDR_x64, true, false, 2}, 2)}, \
{0b00000100, "INC B", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.bc.bc.B, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00000101, "DEC B", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.bc.bc.B, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00000110, "LD B, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00000111, "RLCA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rlca, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00001000, "LD (nn), SP", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, (void*)NULL, &regs.SP, (struct s_params){UDIRECT, ADDR_x64, true, false, 2}, 5)}, \
{0b00001001, "ADD HL, BC", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &regs.hl.HL, &regs.bc.BC, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)}, \
{0b00001010, "LD A, (BC)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.bc.BC, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b00001011, "DEC BC", 0, {_, _, _, _}, std::bind(&Emulateur::decr, this, &regs.bc.BC, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00001100, "INC C", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.bc.bc.C, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00001101, "DEC C", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.bc.bc.C, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00001110, "LD C, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00001111, "RRCA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rrca, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00010000, "STOP", 1, {_, _, _, _}, std::bind(&Emulateur::stop, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00010001, "LD DE, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.DE, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)}, \
{0b00010010, "LD (DE), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.DE, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b00010011, "INC DE", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00010100, "INC D", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.de.de.D, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00010101, "DEC D", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.de.de.D, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00010110, "LD D, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00010111, "RLA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rla, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00011000, "JR e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, EMPTY, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 3)}, \
{0b00011001, "ADD HL, DE", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &regs.hl.HL, &regs.de.DE, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)}, \
{0b00011010, "LD A, (DE)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.de.DE, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b00011011, "DEC DE", 0, {_, _, _, _}, std::bind(&Emulateur::decr, this, &regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00011100, "INC E", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.de.de.E, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00011101, "DEC E", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.de.de.E, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00011110, "LD E, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00011111, "RRA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rra, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00100000, "JR NZ, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, NZ, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)}, \
{0b00100001, "LD HL, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)}, \
{0b00100010, "LD (HLI), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 1, &regs.hl.HL, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b00100011, "INC HL", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00100100, "INC H", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.hl.hl.H, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00100101, "DEC H", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.hl.hl.H, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00100110, "LD H, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00100111, "DAA", 0, {SET, SET_0, _, SET}, std::bind(&Emulateur::daa, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00101000, "JR Z, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, Z, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)}, \
{0b00101001, "ADD HL, HL", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &regs.hl.HL, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)}, \
{0b00101010, "LD A, (HLI)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 1, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b00101011, "DEC HL", 0, {_, _, _, _}, std::bind(&Emulateur::decr, this, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00101100, "INC L", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.hl.hl.L, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00101101, "DEC L", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.hl.hl.L, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00101110, "LD L, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00101111, "CPL", 0, {_, SET_1, SET_1, _}, std::bind(&Emulateur::cpl, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b00110000, "JR NC, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, NC, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)}, \
{0b00110001, "LD SP, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.SP, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)}, \
{0b00110010, "LD (HLD), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, -1, &regs.hl.HL, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b00110011, "INC SP", 0, {_, _, _, _}, std::bind(&Emulateur::inc, this, &regs.SP, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00110100, "INC (HL)", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, true, false, 1}, 3)}, \
{0b00110101, "DEC (HL)", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, true, false, 1}, 3)}, \
{0b00110110, "LD (HL), n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, true, false, 1}, 3)}, \
{0b00110111, "NOT AN INSTRUCTION (0b00110111)", 0, {_, _, _, _}}, \
{0b00111000, "JR C, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, this, C, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)}, \
{0b00111001, "ADD HL, SP", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, this, &regs.hl.HL, &regs.SP, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)}, \
{0b00111010, "LD A, (HLD)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, -1, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b00111011, "DEC SP", 0, {_, _, _, _}, std::bind(&Emulateur::decr, this, &regs.SP, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)}, \
{0b00111100, "INC A", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, this, &regs.af.af.A, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00111101, "DEC A", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, this, &regs.af.af.A, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)}, \
{0b00111110, "LD A, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b00111111, "NOT AN INSTRUCTION (0b00111111)", 0, {_, _, _, _}}, \
{0b01000000, "LD B, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01000001, "LD B, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01000010, "LD B, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01000011, "LD B, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01000100, "LD B, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01000101, "LD B, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01000110, "LD B, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01000111, "LD B, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.B, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001000, "LD C, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001001, "LD C, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001010, "LD C, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001011, "LD C, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001100, "LD C, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001101, "LD C, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01001110, "LD C, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01001111, "LD C, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010000, "LD D, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010001, "LD D, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010010, "LD D, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010011, "LD D, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010100, "LD D, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010101, "LD D, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01010110, "LD D, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01010111, "LD D, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.D, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011000, "LD E, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011001, "LD E, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011010, "LD E, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011011, "LD E, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011100, "LD E, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011101, "LD E, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01011110, "LD E, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01011111, "LD E, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.de.de.E, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100000, "LD H, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100001, "LD H, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100010, "LD H, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100011, "LD H, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100100, "LD H, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100101, "LD H, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01100110, "LD H, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01100111, "LD H, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.H, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101000, "LD L, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101001, "LD L, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101010, "LD L, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101011, "LD L, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101100, "LD L, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101101, "LD L, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01101110, "LD L, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01101111, "LD L, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.hl.L, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01110000, "LD (HL), B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01110001, "LD (HL), C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01110010, "LD (HL), D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01110011, "LD (HL), E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01110100, "LD (HL), H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01110101, "LD (HL), L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01110110, "HALT", 0, {_, _, _, _}, std::bind(&Emulateur::halt, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)}, \
{0b01110111, "LD (HL), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.hl.HL, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)}, \
{0b01111000, "LD A, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01111001, "LD A, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01111010, "LD A, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01111011, "LD A, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01111100, "LD A, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01111101, "LD A, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b01111110, "LD A, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b01111111, "LD A, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000000, "ADD A, B", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000001, "ADD A, C", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000010, "ADD A, D", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000011, "ADD A, E", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000100, "ADD A, H", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000101, "ADD A, L", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10000110, "ADD A, (HL)", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10000111, "ADD A, A", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001000, "ADC A, B", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001001, "ADC A, C", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001010, "ADC A, D", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001011, "ADC A, E", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001100, "ADC A, H", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001101, "ADC A, L", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10001110, "ADC A, (HL)", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10001111, "ADC A, A", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010000, "SUB B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010001, "SUB C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010010, "SUB D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010011, "SUB E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010100, "SUB H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010101, "SUB L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10010110, "SUB (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10010111, "SUB A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011000, "SBC B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011001, "SBC C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011010, "SBC D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011011, "SBC E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011100, "SBC H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011101, "SBC L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10011110, "SBC (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10011111, "SBC A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100000, "AND B", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100001, "AND C", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100010, "AND D", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100011, "AND E", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100100, "AND H", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100101, "AND L", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10100110, "AND (HL)", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10100111, "AND A", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101000, "XOR B", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101001, "XOR C", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101010, "XOR D", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101011, "XOR E", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101100, "XOR H", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101101, "XOR L", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10101110, "XOR (HL)", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10101111, "XOR A", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110000, "OR B", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110001, "OR C", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110010, "OR D", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110011, "OR E", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110100, "OR H", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110101, "OR L", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10110110, "OR (HL)", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10110111, "OR A", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111000, "CP B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111001, "CP C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111010, "CP D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111011, "CP E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111100, "CP H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111101, "CP L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b10111110, "CP (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)}, \
{0b10111111, "CP A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, &regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)}, \
{0b11000000, "RET NZ", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, NZ, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)}, \
{0b11000001, "POP BC", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &regs.bc.BC, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)}, \
{0b11000010, "JP NZ, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, NZ, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11000011, "JP nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, EMPTY, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 4)}, \
{0b11000100, "CALL NZ, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, NZ, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11000101, "PUSH BC", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &regs.bc.BC, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)}, \
{0b11000110, "ADD A, n", 1, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, this, &regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11000111, "RST 0", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 0, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11001000, "RET Z", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, Z, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)}, \
{0b11001001, "RET", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, EMPTY, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11001010, "JP Z, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, Z, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11001011, "op203", 0, {SET, SET, SET, SET}, std::bind(&Emulateur::op203, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)}, \
{0b11001100, "CALL Z, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, Z, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11001101, "CALL nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, EMPTY, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 6)}, \
{0b11001110, "ADC A, n", 1, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, this, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11001111, "RST 1", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 1, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11010000, "RET NC", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, NC, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)}, \
{0b11010001, "POP DE", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)}, \
{0b11010010, "JP NC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, NC, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11010011, "NOT AN INSTRUCTION (0b11010011)", 0, {_, _, _, _}}, \
{0b11010100, "CALL NC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, NC, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11010101, "PUSH DE", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)}, \
{0b11010110, "SUB n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, this, &regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11010111, "RST 2", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 2, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11011000, "RET C", 0, {_, _, _, _}, std::bind(&Emulateur::ret, this, C, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)}, \
{0b11011001, "RETI", 0, {_, _, _, _}, std::bind(&Emulateur::reti, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11011010, "JP C, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, this, C, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11011011, "NOT AN INSTRUCTION (0b11011011)", 0, {_, _, _, _}}, \
{0b11011100, "CALL C, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, this, C, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)}, \
{0b11011101, "NOT AN INSTRUCTION (0b11011101)", 0, {_, _, _, _}}, \
{0b11011110, "SBC n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, this, &regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11011111, "RST 3", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 3, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11100000, "LD (n), A", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, (void *)NULL, &regs.af.af.A, (struct s_params){MEM_gb, ADDR_x64, false, false, 1}, 3)}, \
{0b11100001, "POP HL", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)}, \
{0b11100010, "LD (C), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.bc.bc.C, &regs.af.af.A, (struct s_params){MEM_gb, ADDR_x64, false, false, 1}, 2)}, \
{0b11100011, "NOT AN INSTRUCTION (0b11100011)", 0, {_, _, _, _}}, \
{0b11100100, "NOT AN INSTRUCTION (0b11100100)", 0, {_, _, _, _}}, \
{0b11100101, "PUSH HL", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)}, \
{0b11100110, "AND n", 1, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, this, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11100111, "RST 4", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 4, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11101000, "ADD SP, e", 1, {SET, SET, SET_0, SET_0}, std::bind(&Emulateur::add, this, &regs.SP, (void *)NULL, (struct s_params){ADDR_x64, DIRECT, false, false, 1}, 4)}, \
{0b11101001, "JP (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::jp, this, EMPTY, &regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, true, false, 2}, 1)}, \
{0b11101010, "LD (nn), A", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, (void*)NULL, &regs.af.af.A, (struct s_params){UDIRECT, ADDR_x64, true, false, 2}, 4)}, \
{0b11101011, "NOT AN INSTRUCTION (0b11101011)", 0, {_, _, _, _}}, \
{0b11101100, "NOT AN INSTRUCTION (0b11101100)", 0, {_, _, _, _}}, \
{0b11101101, "NOT AN INSTRUCTION (0b11101101)", 0, {_, _, _, _}}, \
{0b11101110, "XOR n", 1, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, this, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11101111, "RST 5", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 5, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11110000, "LD A, (n)", 1, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, MEM_gb, false, false, 1}, 3)}, \
{0b11110001, "POP AF", 0, {_, _, _, _}, std::bind(&Emulateur::pop, this, &regs.af.AF, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)}, \
{0b11110010, "LD A, (C)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, &regs.bc.bc.C, (struct s_params){ADDR_x64, MEM_gb, false, false, 1}, 2)}, \
{0b11110011, "DI", 0, {_, _, _, _}, std::bind(&Emulateur::di, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11110100, "NOT AN INSTRUCTION (0b11110100)", 0, {_, _, _, _}}, \
{0b11110101, "PUSH AF", 0, {_, _, _, _}, std::bind(&Emulateur::push, this, &regs.af.AF, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)}, \
{0b11110110, "OR n", 1, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, this, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11110111, "RST 6", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 6, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11111000, "LDHL SP, e", 1, {SET, SET, SET_0, SET_0}, std::bind(&Emulateur::ldhl, this, &regs.SP, (void*)NULL, (struct s_params){ADDR_x64, DIRECT, false, false, 1}, 3)}, \
{0b11111001, "LD SP, HL", 0, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.SP, &regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)}, \
{0b11111010, "LD A, (nn)", 2, {_, _, _, _}, std::bind(&Emulateur::ld, this, 0, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, true, 1}, 4)}, \
{0b11111011, "EI", 0, {_, _, _, _}, std::bind(&Emulateur::ei, this, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}, \
{0b11111100, "NOT AN INSTRUCTION (0b11111100)", 0, {_, _, _, _}}, \
{0b11111101, "NOT AN INSTRUCTION (0b11111101)", 0, {_, _, _, _}}, \
{0b11111110, "CP n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, this, &regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)}, \
{0b11111111, "RST 7", 0, {_, _, _, _}, std::bind(&Emulateur::rst, this, 7, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}
#endif
