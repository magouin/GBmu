#ifndef DEBUGGER_HPP
# define DEBUGGER_HPP
# define DEB_CMD \
{"b", TWO, &Emulateur::cmd_breakpoint},\
{"break", TWO, &Emulateur::cmd_breakpoint},\
{"c", ONE, &Emulateur::cmd_continue},\
{"continue", ONE, &Emulateur::cmd_continue},\
{"d", TWO, &Emulateur::cmd_delete},\
{"delete", TWO, &Emulateur::cmd_delete},\
{"h", ONE, NULL},\
{"help", ONE, NULL},\
{"i", ONE, NULL},\
{"info", ONE, NULL},\
{"n", ONE, &Emulateur::cmd_next},\
{"next", ONE, &Emulateur::cmd_next},\
{"p", TWO, NULL},\
{"p/t", TWO, NULL},\
{"p/x", TWO, NULL},\
{"print", TWO, NULL},\
{"print/t", TWO, NULL},\
{"print/x", TWO, NULL},\
{"q", ONE, &Emulateur::cmd_quit},\
{"quit", ONE, &Emulateur::cmd_quit},\
{"reset", ONE, NULL},\
{"r/1", TWO, NULL},\
{"r/2", TWO, NULL},\
{"r/4", TWO, NULL},\
{"status", ONE, NULL},\
{"trace", TWO, NULL},\
{"w", TWO, NULL},\
{"w/1", THREE, NULL},\
{"w/2", THREE, NULL},\
{"w/r", THREE, NULL},\
{"w/4", THREE, NULL},\
{"watch", TWO, NULL},\
{"watch/r", TWO, NULL},\
{"watch/w", TWO, NULL},\
{"x/1", TWO | THREE, NULL},\
{"x/2", TWO | THREE, NULL},\
{"x/4", TWO | THREE, NULL}

#endif
