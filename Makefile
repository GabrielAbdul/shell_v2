CC=gcc
SRC=src/shell.c src/builtins/getenv.c src/builtins/env.c src/builtins/cd.c src/builtins/exit.c src/builtins/sigint_handler.c src/builtins/help.c src/command_list/create_command_list.c src/command_list/parse_command_list.c src/command_list/execute_command_list.c src/command_list/free_commands.c src/command_list/helpers.c src/command_list/strings.c
OBJ= $(SRC:.c=.o)
NAME=hsh
RM=rm -f
CFLAGS=-Wall -Werror -Wextra -pedantic -g

.PHONY: all $(NAME) fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) *~ $(NAME)

oclean:
	$(RM) $(OBJ)

fclean: clean oclean

re: oclean all