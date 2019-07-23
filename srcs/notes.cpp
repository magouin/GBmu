#include <gbmu.hpp>
#include <functional>
#include <instructions.hpp>
#include <Emulateur.hpp>

extern Emulateur emu;

using namespace std::placeholders;
const struct s_instruction_params Emulateur::g_opcode[256] = {
{0b00000000, "NOP", 0, {_, _, _, _}, std::bind(&Emulateur::nop, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)},
{0b00000001, "NOT AN INSTRUCTION (0b00000001)", 0, {_, _, _, _}},
{0b00000010, "LD (BC), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.BC, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b00000011, "INC BC", 0, {_, _, _, _}, std::bind(&Emulateur::inc, &emu, &emu.regs.bc.BC, (struct s_params){ADDR_x64, ADDR_x64, true, false, 2}, 2)},
{0b00000100, "INC B", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00000101, "DEC B", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00000110, "LD B, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00000111, "RLCA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rlca, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00001000, "LD (nn), SP", 2, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, (void*)NULL, &emu.regs.SP, (struct s_params){UDIRECT, ADDR_x64, true, false, 2}, 5)},
{0b00001001, "ADD HL, BC", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, &emu, &emu.regs.hl.HL, &emu.regs.bc.BC, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)},
{0b00001010, "LD A, (BC)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.bc.BC, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b00001011, "DEC BC", 0, {_, _, _, _}, std::bind(&Emulateur::decr, &emu, &emu.regs.bc.BC, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00001100, "INC C", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00001101, "DEC C", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00001110, "LD C, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00001111, "RRCA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rrca, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00010000, "STOP", 1, {_, _, _, _}, std::bind(&Emulateur::stop, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00010001, "LD DE, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.DE, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)},
{0b00010010, "LD (DE), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.DE, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b00010011, "INC DE", 0, {_, _, _, _}, std::bind(&Emulateur::inc, &emu, &emu.regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00010100, "INC D", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.de.de.D, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00010101, "DEC D", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.de.de.D, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00010110, "LD D, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00010111, "RLA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rla, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00011000, "JR e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, &emu, EMPTY, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 3)},
{0b00011001, "ADD HL, DE", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, &emu, &emu.regs.hl.HL, &emu.regs.de.DE, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)},
{0b00011010, "LD A, (DE)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.de.DE, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b00011011, "DEC DE", 0, {_, _, _, _}, std::bind(&Emulateur::decr, &emu, &emu.regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00011100, "INC E", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.de.de.E, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00011101, "DEC E", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.de.de.E, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00011110, "LD E, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00011111, "RRA", 0, {SET, SET_0, SET_0, SET_0}, std::bind(&Emulateur::rra, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00100000, "JR NZ, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, &emu, NZ, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)},
{0b00100001, "LD HL, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)},
{0b00100010, "LD (HLI), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 1, &emu.regs.hl.HL, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b00100011, "INC HL", 0, {_, _, _, _}, std::bind(&Emulateur::inc, &emu, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00100100, "INC H", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00100101, "DEC H", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00100110, "LD H, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00100111, "DAA", 0, {SET, SET_0, _, SET}, std::bind(&Emulateur::daa, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00101000, "JR Z, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, &emu, Z, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)},
{0b00101001, "ADD HL, HL", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, &emu, &emu.regs.hl.HL, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)},
{0b00101010, "LD A, (HLI)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 1, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b00101011, "DEC HL", 0, {_, _, _, _}, std::bind(&Emulateur::decr, &emu, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00101100, "INC L", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00101101, "DEC L", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00101110, "LD L, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00101111, "CPL", 0, {_, SET_1, SET_1, _}, std::bind(&Emulateur::cpl, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b00110000, "JR NC, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, &emu, NC, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)},
{0b00110001, "LD SP, nn", 2, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.SP, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 2}, 3)},
{0b00110010, "LD (HLD), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, -1, &emu.regs.hl.HL, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b00110011, "INC SP", 0, {_, _, _, _}, std::bind(&Emulateur::inc, &emu, &emu.regs.SP, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00110100, "INC (HL)", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, true, false, 1}, 3)},
{0b00110101, "DEC (HL)", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, true, false, 1}, 3)},
{0b00110110, "LD (HL), n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, true, false, 1}, 3)},
{0b00110111, "NOT AN INSTRUCTION (0b00110111)", 0, {_, _, _, _}},
{0b00111000, "JR C, e", 1, {_, _, _, _}, std::bind(&Emulateur::jr, &emu, C, (struct s_params){DIRECT, NO_PARAM, false, false, 1}, 0)},
{0b00111001, "ADD HL, SP", 0, {SET, SET, SET_0, _}, std::bind(&Emulateur::add, &emu, &emu.regs.hl.HL, &emu.regs.SP, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)},
{0b00111010, "LD A, (HLD)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, -1, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b00111011, "DEC SP", 0, {_, _, _, _}, std::bind(&Emulateur::decr, &emu, &emu.regs.SP, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 2)},
{0b00111100, "INC A", 0, {_, SET, SET_0, SET}, std::bind(&Emulateur::inc, &emu, &emu.regs.af.af.A, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00111101, "DEC A", 0, {_, SET, SET_1, SET}, std::bind(&Emulateur::decr, &emu, &emu.regs.af.af.A, (struct s_params){ADDR_x64, NO_PARAM, false, false, 1}, 1)},
{0b00111110, "LD A, n", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b00111111, "NOT AN INSTRUCTION (0b00111111)", 0, {_, _, _, _}},
{0b01000000, "LD B, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01000001, "LD B, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01000010, "LD B, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01000011, "LD B, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01000100, "LD B, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01000101, "LD B, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01000110, "LD B, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01000111, "LD B, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.B, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001000, "LD C, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001001, "LD C, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001010, "LD C, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001011, "LD C, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001100, "LD C, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001101, "LD C, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01001110, "LD C, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01001111, "LD C, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010000, "LD D, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010001, "LD D, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010010, "LD D, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010011, "LD D, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010100, "LD D, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010101, "LD D, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01010110, "LD D, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01010111, "LD D, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.D, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011000, "LD E, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011001, "LD E, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011010, "LD E, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011011, "LD E, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011100, "LD E, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011101, "LD E, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01011110, "LD E, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01011111, "LD E, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.de.de.E, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100000, "LD H, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100001, "LD H, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100010, "LD H, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100011, "LD H, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100100, "LD H, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100101, "LD H, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01100110, "LD H, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01100111, "LD H, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.H, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101000, "LD L, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101001, "LD L, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101010, "LD L, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101011, "LD L, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101100, "LD L, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101101, "LD L, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01101110, "LD L, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01101111, "LD L, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.hl.L, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01110000, "LD (HL), B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01110001, "LD (HL), C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01110010, "LD (HL), D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01110011, "LD (HL), E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01110100, "LD (HL), H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01110101, "LD (HL), L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01110110, "HALT", 0, {_, _, _, _}, std::bind(&Emulateur::halt, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 1)},
{0b01110111, "LD (HL), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.hl.HL, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, true, false, 1}, 2)},
{0b01111000, "LD A, B", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01111001, "LD A, C", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01111010, "LD A, D", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01111011, "LD A, E", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01111100, "LD A, H", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01111101, "LD A, L", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b01111110, "LD A, (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b01111111, "LD A, A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000000, "ADD A, B", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000001, "ADD A, C", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000010, "ADD A, D", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000011, "ADD A, E", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000100, "ADD A, H", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000101, "ADD A, L", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10000110, "ADD A, (HL)", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10000111, "ADD A, A", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001000, "ADC A, B", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001001, "ADC A, C", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001010, "ADC A, D", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001011, "ADC A, E", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001100, "ADC A, H", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001101, "ADC A, L", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10001110, "ADC A, (HL)", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10001111, "ADC A, A", 0, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010000, "SUB B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010001, "SUB C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010010, "SUB D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010011, "SUB E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010100, "SUB H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010101, "SUB L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10010110, "SUB (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10010111, "SUB A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011000, "SBC B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011001, "SBC C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011010, "SBC D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011011, "SBC E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011100, "SBC H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011101, "SBC L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10011110, "SBC (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10011111, "SBC A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100000, "AND B", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100001, "AND C", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100010, "AND D", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100011, "AND E", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100100, "AND H", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100101, "AND L", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10100110, "AND (HL)", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10100111, "AND A", 0, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101000, "XOR B", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101001, "XOR C", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101010, "XOR D", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101011, "XOR E", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101100, "XOR H", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101101, "XOR L", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10101110, "XOR (HL)", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10101111, "XOR A", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110000, "OR B", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110001, "OR C", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110010, "OR D", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110011, "OR E", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110100, "OR H", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110101, "OR L", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10110110, "OR (HL)", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10110111, "OR A", 0, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111000, "CP B", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.B, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111001, "CP C", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111010, "CP D", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.de.de.D, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111011, "CP E", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.de.de.E, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111100, "CP H", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.H, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111101, "CP L", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.hl.hl.L, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b10111110, "CP (HL)", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, true, 1}, 2)},
{0b10111111, "CP A", 0, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, &emu.regs.af.af.A, (struct s_params){ADDR_x64, ADDR_x64, false, false, 1}, 1)},
{0b11000000, "RET NZ", 0, {_, _, _, _}, std::bind(&Emulateur::ret, &emu, NZ, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)},
{0b11000001, "POP BC", 0, {_, _, _, _}, std::bind(&Emulateur::pop, &emu, &emu.regs.bc.BC, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)},
{0b11000010, "JP NZ, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, &emu, NZ, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11000011, "JP nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, &emu, EMPTY, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 4)},
{0b11000100, "CALL NZ, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, &emu, NZ, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11000101, "PUSH BC", 0, {_, _, _, _}, std::bind(&Emulateur::push, &emu, &emu.regs.bc.BC, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)},
{0b11000110, "ADD A, n", 1, {SET, SET, SET_0, SET}, std::bind(&Emulateur::add, &emu, &emu.regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11000111, "RST 0", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 0, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11001000, "RET Z", 0, {_, _, _, _}, std::bind(&Emulateur::ret, &emu, Z, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)},
{0b11001001, "RET", 0, {_, _, _, _}, std::bind(&Emulateur::ret, &emu, EMPTY, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11001010, "JP Z, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, &emu, Z, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11001011, "op203", 0, {SET, SET, SET, SET}, std::bind(&Emulateur::op203, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)},
{0b11001100, "CALL Z, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, &emu, Z, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11001101, "CALL nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, &emu, EMPTY, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 6)},
{0b11001110, "ADC A, n", 1, {SET, SET, SET_0, SET}, std::bind(&Emulateur::adc, &emu, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11001111, "RST 1", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 1, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11010000, "RET NC", 0, {_, _, _, _}, std::bind(&Emulateur::ret, &emu, NC, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)},
{0b11010001, "POP DE", 0, {_, _, _, _}, std::bind(&Emulateur::pop, &emu, &emu.regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)},
{0b11010010, "JP NC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, &emu, NC, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11010011, "NOT AN INSTRUCTION (0b11010011)", 0, {_, _, _, _}},
{0b11010100, "CALL NC, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, &emu, NC, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11010101, "PUSH DE", 0, {_, _, _, _}, std::bind(&Emulateur::push, &emu, &emu.regs.de.DE, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)},
{0b11010110, "SUB n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sub, &emu, &emu.regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11010111, "RST 2", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 2, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11011000, "RET C", 0, {_, _, _, _}, std::bind(&Emulateur::ret, &emu, C, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 0)},
{0b11011001, "RETI", 0, {_, _, _, _}, std::bind(&Emulateur::reti, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11011010, "JP C, nn", 2, {_, _, _, _}, std::bind(&Emulateur::jp, &emu, C, (void*)NULL, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11011011, "NOT AN INSTRUCTION (0b11011011)", 0, {_, _, _, _}},
{0b11011100, "CALL C, nn", 2, {_, _, _, _}, std::bind(&Emulateur::call, &emu, C, (struct s_params){UDIRECT, NO_PARAM, false, false, 2}, 0)},
{0b11011101, "NOT AN INSTRUCTION (0b11011101)", 0, {_, _, _, _}},
{0b11011110, "SBC n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::sbc, &emu, &emu.regs.af.af.A, (void *)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11011111, "RST 3", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 3, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11100000, "LD (n), A", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, (void *)NULL, &emu.regs.af.af.A, (struct s_params){MEM_gb, ADDR_x64, true, false, 1}, 3)},
{0b11100001, "POP HL", 0, {_, _, _, _}, std::bind(&Emulateur::pop, &emu, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)},
{0b11100010, "LD (C), A", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.bc.bc.C, &emu.regs.af.af.A, (struct s_params){MEM_gb, ADDR_x64, true, false, 1}, 2)},
{0b11100011, "NOT AN INSTRUCTION (0b11100011)", 0, {_, _, _, _}},
{0b11100100, "NOT AN INSTRUCTION (0b11100100)", 0, {_, _, _, _}},
{0b11100101, "PUSH HL", 0, {_, _, _, _}, std::bind(&Emulateur::push, &emu, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)},
{0b11100110, "AND n", 1, {SET_0, SET_1, SET_0, SET}, std::bind(&Emulateur::_and, &emu, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11100111, "RST 4", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 4, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11101000, "ADD SP, e", 1, {SET, SET, SET_0, SET_0}, std::bind(&Emulateur::add, &emu, &emu.regs.SP, (void *)NULL, (struct s_params){ADDR_x64, DIRECT, false, false, 1}, 4)},
{0b11101001, "JP (HL)", 0, {_, _, _, _}, std::bind(&Emulateur::jp, &emu, EMPTY, &emu.regs.hl.HL, (struct s_params){ADDR_x64, NO_PARAM, true, false, 2}, 1)},
{0b11101010, "LD A, (nn)", 2, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, true, 1}, 4)},
{0b11101011, "NOT AN INSTRUCTION (0b11101011)", 0, {_, _, _, _}},
{0b11101100, "NOT AN INSTRUCTION (0b11101100)", 0, {_, _, _, _}},
{0b11101101, "NOT AN INSTRUCTION (0b11101101)", 0, {_, _, _, _}},
{0b11101110, "XOR n", 1, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_xor, &emu, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11101111, "RST 5", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 5, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11110000, "LD A, (n)", 1, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, MEM_gb, false, false, 1}, 3)},
{0b11110001, "POP AF", 0, {_, _, _, _}, std::bind(&Emulateur::pop, &emu, &emu.regs.af.AF, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 3)},
{0b11110010, "LD A, (C)", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.af.af.A, &emu.regs.bc.bc.C, (struct s_params){ADDR_x64, MEM_gb, false, true, 1}, 2)},
{0b11110011, "DI", 0, {_, _, _, _}, std::bind(&Emulateur::di, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11110100, "NOT AN INSTRUCTION (0b11110100)", 0, {_, _, _, _}},
{0b11110101, "PUSH AF", 0, {_, _, _, _}, std::bind(&Emulateur::push, &emu, &emu.regs.af.AF, (struct s_params){ADDR_x64, NO_PARAM, false, false, 2}, 4)},
{0b11110110, "OR n", 1, {SET_0, SET_0, SET_0, SET}, std::bind(&Emulateur::_or, &emu, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11110111, "RST 6", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 6, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11111000, "LDHL SP, e", 1, {SET, SET, SET_0, SET_0}, std::bind(&Emulateur::ldhl, &emu, &emu.regs.SP, (void*)NULL, (struct s_params){ADDR_x64, DIRECT, false, false, 1}, 3)},
{0b11111001, "LD SP, HL", 0, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, &emu.regs.SP, &emu.regs.hl.HL, (struct s_params){ADDR_x64, ADDR_x64, false, false, 2}, 2)},
{0b11111010, "LD (nn), A", 2, {_, _, _, _}, std::bind(&Emulateur::ld, &emu, 0, (void*)NULL, &emu.regs.af.af.A, (struct s_params){UDIRECT, ADDR_x64, true, false, 1}, 4)},
{0b11111011, "EI", 0, {_, _, _, _}, std::bind(&Emulateur::di, &emu, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)},
{0b11111100, "NOT AN INSTRUCTION (0b11111100)", 0, {_, _, _, _}},
{0b11111101, "NOT AN INSTRUCTION (0b11111101)", 0, {_, _, _, _}},
{0b11111110, "CP n", 1, {SET, SET, SET_1, SET}, std::bind(&Emulateur::cp, &emu, &emu.regs.af.af.A, (void*)NULL, (struct s_params){ADDR_x64, UDIRECT, false, false, 1}, 2)},
{0b11111111, "RST 7", 0, {_, _, _, _}, std::bind(&Emulateur::rst, &emu, 7, (struct s_params){NO_PARAM, NO_PARAM, false, false, 0}, 4)}};

const vector<enum e_right> Emulateur::g_ram_reg = {
	RDWR,	RDWR,	RDWR,	PROHIB,	RDWR,	RDWR,	RDWR,	RDWR,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	RDWR,
	RDWR,	RDWR,	RDWR,	WR,		RDWR,	PROHIB,	RDWR,	RDWR,	WR,		RDWR,	RDWR,	RDWR,	RDWR,	WR,		RDWR,	PROHIB,	
	RDWR,	RDWR,	WR,		RDWR,	RDWR,	RDWR,	RDWR,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	
	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	
	RDWR,	RDWR,	RDWR,	RDWR,	RD,		RDWR,	WR,		WR,		WR,		WR,		RDWR,	RDWR,	PROHIB,	RDWR,	PROHIB,	RDWR,	
	PROHIB,	WR,		WR,		WR,		WR,		WR,		RDWR,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	
	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	RDWR,	RDWR,	RDWR,	RDWR,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	
	RDWR,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB,	PROHIB
};


/*

0xff00, RDWR // P1
0xff01, RDWR // SB
0xff02, RDWR // SC
0xff03, PROHIBITED
0xff04, RDWR // DIV
0xff05, RDWR // TIMA
0xff06, RDWR // TMA 
0xff07, RDWR // TAC
0xff08, PROHIBITED
0xff09, PROHIBITED
0xff0a, PROHIBITED
0xff0b, PROHIBITED
0xff0c, PROHIBITED
0xff0d, PROHIBITED
0xff0e, PROHIBITED
0xff0f, RDWR // IF
0xff10, RDWR // NR10
0xff11, RDWR // NR11
0xff12, RDWR // NR12
0xff13, WR // NR13
0xff14, RDWR // NR14
0xff15, PROHIBITED
0xff16, RDWR // NR21
0xff17, RDWR // NR22
0xff18, WR // NR23
0xff19, RDWR // NR24
0xff1a, RDWR // NR30
0xff1b, RDWR // NR31
0xff1c, RDWR // NR32
0xff1d, WR // NR33
0xff1e, RDWR // NR34
0xff1f, PROHIBITED
0xff20, RDWR // NR41
0xff21, RDWR // NR42
0xff22, WR // NR43
0xff23, RDWR // NR44
0xff24, RDWR // NR50
0xff25, RDWR // NR51
0xff26, RDWR // NR52
0xff27, PROHIBITED
0xff28, PROHIBITED
0xff29, PROHIBITED
0xff2a, PROHIBITED
0xff2b, PROHIBITED
0xff2c, PROHIBITED
0xff2d, PROHIBITED
0xff2e, PROHIBITED
0xff2f, PROHIBITED
0xff30, PROHIBITED
0xff31, PROHIBITED
0xff32, PROHIBITED
0xff33, PROHIBITED
0xff34, PROHIBITED
0xff35, PROHIBITED
0xff36, PROHIBITED
0xff37, PROHIBITED
0xff38, PROHIBITED
0xff39, PROHIBITED
0xff3a, PROHIBITED
0xff3b, PROHIBITED
0xff3c, PROHIBITED
0xff3d, PROHIBITED
0xff3e, PROHIBITED
0xff3f, PROHIBITED
0xff40, RDWR // LCDC
0xff41, RDWR // STAT
0xff42, RDWR // SCY
0xff43, RDWR // SCX
0xff44, RD // LY
0xff45, RDWR // LYC
0xff46, WR // DMA
0xff47, WR // BGP
0xff48, WR // OBPO
0xff49, WR // OBP1
0xff4a, RDWR // WY
0xff4b, RDWR // WX
0xff4c, PROHIBITED
0xff4d, RDWR // KEY1
0xff4e, PROHIBITED
0xff4f, RDWR // VBK
0xff50, PROHIBITED
0xff51, WR // HDMA1
0xff52, WR // HDMA2
0xff53, WR // HDMA3
0xff54, WR // HDMA4
0xff55, WR // HDMA5
0xff56, RDWR // RP
0xff57, PROHIBITED
0xff58, PROHIBITED
0xff59, PROHIBITED
0xff5a, PROHIBITED
0xff5b, PROHIBITED
0xff5c, PROHIBITED
0xff5d, PROHIBITED
0xff5e, PROHIBITED
0xff5f, PROHIBITED
0xff60, PROHIBITED
0xff61, PROHIBITED
0xff62, PROHIBITED
0xff63, PROHIBITED
0xff64, PROHIBITED
0xff65, PROHIBITED
0xff66, PROHIBITED
0xff67, PROHIBITED
0xff68, RDWR // BCPS
0xff69, RDWR // BCPD
0xff6a, RDWR // OCPS
0xff6b, RDWR // OCPD
0xff6c, PROHIBITED
0xff6d, PROHIBITED
0xff6e, PROHIBITED
0xff6f, PROHIBITED
0xff70, RDWR // SVBK
0xff71, PROHIBITED
0xff72, PROHIBITED
0xff73, PROHIBITED
0xff74, PROHIBITED
0xff75, PROHIBITED
0xff76, PROHIBITED
0xff77, PROHIBITED
0xff78, PROHIBITED
0xff79, PROHIBITED
0xff7a, PROHIBITED
0xff7b, PROHIBITED
0xff7c, PROHIBITED
0xff7d, PROHIBITED
0xff7e, PROHIBITED
0xff7f, PROHIBITED

0xffff, RDWR // IE

*/