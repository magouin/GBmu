#ifndef DEBUGGER_HPP
# define DEBUGGER_HPP

# define DEB_CMD \
{"b", TWO, bind(&Emulateur::cmd_breakpoint, this, placeholders::_1)},\
{"break", TWO, bind(&Emulateur::cmd_breakpoint, this, placeholders::_1)},\
{"c", ONE, bind(&Emulateur::cmd_continue, this, placeholders::_1)},\
{"continue", ONE, bind(&Emulateur::cmd_continue, this, placeholders::_1)},\
{"d", TWO, bind(&Emulateur::cmd_delete, this, placeholders::_1)},\
{"delete", TWO, bind(&Emulateur::cmd_delete, this, placeholders::_1)},\
{"h", ONE, bind(&Emulateur::cmd_help, this, placeholders::_1)},\
{"help", ONE, bind(&Emulateur::cmd_help, this, placeholders::_1)},\
{"i", ONE, bind(&Emulateur::cmd_info, this, placeholders::_1)},\
{"info", ONE, bind(&Emulateur::cmd_info, this, placeholders::_1)},\
{"n", ONE, bind(&Emulateur::cmd_next, this, placeholders::_1)},\
{"next", ONE, bind(&Emulateur::cmd_next, this, placeholders::_1)},\
{"p", TWO, bind(&Emulateur::cmd_print, this, placeholders::_1, 10)},\
{"p/t", TWO, bind(&Emulateur::cmd_print, this, placeholders::_1, 2)},\
{"p/x", TWO, bind(&Emulateur::cmd_print, this, placeholders::_1, 16)},\
{"print", TWO, bind(&Emulateur::cmd_print, this, placeholders::_1, 10)},\
{"print/t", TWO, bind(&Emulateur::cmd_print, this, placeholders::_1, 2)},\
{"print/x", TWO, bind(&Emulateur::cmd_print, this, placeholders::_1, 16)},\
{"q", ONE, bind(&Emulateur::cmd_quit, this, placeholders::_1)},\
{"quit", ONE, bind(&Emulateur::cmd_quit, this, placeholders::_1)},\
{"reset", ONE, bind(&Emulateur::cmd_reset, this, placeholders::_1)},\
{"r/1", TWO, bind(&Emulateur::cmd_read, this, placeholders::_1, 1)},\
{"r/2", TWO, bind(&Emulateur::cmd_read, this, placeholders::_1, 2)},\
{"r/4", TWO, bind(&Emulateur::cmd_read, this, placeholders::_1, 4)},\
{"status", ONE, bind(&Emulateur::cmd_info, this, placeholders::_1)},\
{"trace", TWO, bind(&Emulateur::cmd_trace, this, placeholders::_1)},\
{"w", TWO, bind(&Emulateur::cmd_watchpoint, this, placeholders::_1, RDWR)},\
{"w/1", THREE, bind(&Emulateur::cmd_write, this, placeholders::_1, 1)},\
{"w/2", THREE, bind(&Emulateur::cmd_write, this, placeholders::_1, 2)},\
{"watch", TWO, bind(&Emulateur::cmd_watchpoint, this, placeholders::_1, RDWR)},\
{"watch/r", TWO, bind(&Emulateur::cmd_watchpoint, this, placeholders::_1, RD)},\
{"watch/w", TWO, bind(&Emulateur::cmd_watchpoint, this, placeholders::_1, WR)},\
{"x/1", TWO | THREE, bind(&Emulateur::cmd_examine, this, placeholders::_1, 1)},\
{"x/2", TWO | THREE, bind(&Emulateur::cmd_examine, this, placeholders::_1, 2)},\
{"x/4", TWO | THREE, bind(&Emulateur::cmd_examine, this, placeholders::_1, 4)}, \
{"second", ONE, bind(&Emulateur::cmd_second, this, placeholders::_1)}, \
{"frame", ONE, bind(&Emulateur::cmd_frame, this, placeholders::_1)}

# define USAGE "Generic commands:\n\
b          Set a breakpoint\n\
break      Set a breakpoint\n\
c          Continue execution\n\
continue   Continue execution\n\
d          Delete a breakpoint or watchpoint\n\
delete     Delete a breakpoint or watchpoint\n\
h          Print help\n\
help       Print help\n\
i          Print the current status\n\
info       Print the current status\n\
n          Execute next instruction\n\
next       Execute next instruction\n\
p          Print a value\n\
p/t        Print a value as binary\n\
p/x        Print a value as hexadecimal\n\
print      Print a value\n\
print/t    Print a value as binary\n\
print/x    Print a value as hexadecimal\n\
q          Quit the emulator\n\
quit       Quit the emulator\n\
reset      Reset the emulation\n\
r/1        Read a byte from a specified offset\n\
r/2        Read a halfword from a specified offset\n\
r/4        Read a word from a specified offset\n\
status     Print the current status\n\
trace      Trace a fixed number of instructions\n\
w          Set a watchpoint\n\
w/1        Write a byte at a specified offset\n\
w/2        Write a halfword at a specified offset\n\
watch      Set a watchpoint\n\
watch/r    Set a read watchpoint\n\
watch/w    Set a write watchpoint\n\
x/1        Examine bytes at a specified offset\n\
x/2        Examine halfwords at a specified offset\n\
x/4        Examine words at a specified offset\n\
second     Second advance\n\
frame      Frame advance\n"

#endif

