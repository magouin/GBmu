MEM_CTRL_PATH = Memory_controller

SRC_NAME =	main.cpp \
			$(MEM_CTRL_PATH)/Memory_controller.cpp \
			$(MEM_CTRL_PATH)/Memory_controller_MBC1.cpp \
			$(MEM_CTRL_PATH)/Memory_controller_MBC2.cpp \
			$(MEM_CTRL_PATH)/Memory_controller_MBC3.cpp \
			$(MEM_CTRL_PATH)/Memory_controller_MBC5.cpp \
			Header.cpp \
			instructions.cpp \
			Emulateur.cpp \
			sdl.cpp \
			lcd.cpp \
			init.cpp \
			debugger.cpp

INC_PATH = ../incs/
OBJ_PATH = ./obj/

NAME = ./GBmu

CC = /usr/bin/clang++

CFLAGS =  -std=c++11 -Wall -Wextra -Werror
# DFLAGS = -g -Wno-missing-field-initializers -Wno-unused-parameter

ROOT = ${CURDIR}

LIB_PATH = $(ROOT)/libs

SDL2_PATH		= $(LIB_PATH)/SDL2-2.0.10
SDL2			= $(SDL2_PATH)/build/.libs/libSDL2.a
SDL2_ARCHIVE 	= SDL2-2.0.10.tar.gz
LIBFLAGS		= `$(SDL2_PATH)/sdl2-config --static-libs | cut -f3- -d ' '`
# LIBFLAGS		= -L $(SDL2_PATH)/build/.libs ./libs/SDL2-2.0.10/build/.libs/libSDL2-2.0.0.dylib
# libSDL2-2.0.0.dylib
# libSDL2.dylib

SRC_PATH = ../srcs/

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(SDL2) $(NAME)

$(SDL2):
	mkdir -p $(LIB_PATH)
	curl 'https://www.libsdl.org/release/SDL2-2.0.10.tar.gz' -o $(LIB_PATH)/$(SDL2_ARCHIVE)
	tar -C $(LIB_PATH) -xf $(LIB_PATH)/$(SDL2_ARCHIVE)
	cp -rf $(SDL2_PATH)/include $(INC_PATH)/SDL2
	cd $(SDL2_PATH) && ./configure --prefix=`pwd` && make -j8 && make install
	rm -rf $(LIB_PATH)/$(SDL2_ARCHIVE)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/$(MEM_CTRL_PATH) 2> /dev/null || echo "" > /dev/null

	$(CC) $(CFLAGS) $(DFLAGS) $(INC) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) $(INC) $(SDL2) $(LIBFLAGS) $^ -o $@

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all

clean-lib:
	rm -rf $(LIB_PATH)

.PHONY : all clean fclean re
