NAME = minishell
HEADER = mini-shell.h
SRC =  ./execution/mini_shell.c ./execution/env.c ./execution/execution.c ./execution/tools_list.c \
	./execution/utilise_blt1.c ./execution/utilise2.c ./execution/utilise3.c ./execution/herdoc.c \
	./execution/utilise_blt.c ./execution/utilise.c utilise1.c \
	./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
	./parsing/change_var_ulit.c ./parsing/get_inp.c ./parsing/set_speace_line.c \
	./parsing/change_var.c ./parsing/check_errors.c ./parsing/get_args2.c ./parsing/get_out.c \
	./parsing/change_var_one.c ./parsing/clear_list.c ./parsing/get_env_realine.c ./parsing/set_list.c \
	./parsing/split_pip.c ./parsing/check_errors_var.c ./parsing/scan_errore.c ./parsing/split_args.c \

OBG = $(SRC:.c=.o)
READLINE = -lreadline -L/goinfre/$(USER)/homebrew/opt/readline/lib -I/goinfre/$(USER)/homebrew/opt/readline/include
CFLAGS = -Wall -Wextra -Werror
DEBAGS = -g -fsanitize=address
LIBS =  ./libft/*.c
RM = rm -f
CC = cc

all: $(NAME) libft

libft:
	make all -C ./libft
	make bonus -C ./libft

$(NAME) : $(SRC)
	$(CC)  $(CFLAGS) $(LIBS) $(SRC) $(READLINE) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re : fclean all

.PHONY: libft
