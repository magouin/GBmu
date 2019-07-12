SRC_NAME =	main.cpp \
			Header.cpp \
			notes.cpp \
			two_bytes_instr.cpp \
			Disassembler.cpp \
			instructions.cpp \
			Emulateur.cpp

INC_PATH = ./includes/
OBJ_PATH = ./obj/

NAME = ./GBmu

CC = /usr/bin/clang++

#CFLAGS = -Wall -Werror -Wextra -g
CFLAGS =  -std=c++11 -Wall -Wextra
DFLAGS = -g -Wno-missing-field-initializers -Wno-unused-parameter -fsanitize=address -DDEBUG

SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $(INC) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) $(INC) $^ -o $@

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re
