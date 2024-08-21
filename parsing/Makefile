CC =cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = parsing.a
SRC = change_var_ulit.c get_inp.c print_list.c set_speace_line.c \
	change_var.c check_errors.c get_args2.c get_out.c scan_errore.c split_args.c \
	change_var_one.c clear_list.c get_env_realine.c set_list.c split_pip.c check_errors_var.c

all: $(NAME)

$(NAME):$(OBJ)
	ar rc $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o

fclean:clean
	$(RM) $(NAME) 
re: fclean all

.PHONY: all clean fclean re