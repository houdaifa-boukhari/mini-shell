CC =cc
CFLAGS = #-Wall -Wextra -Werror
RM = rm -f
NAME = parsing.a
SRC = get_args2.c set_list.c split_args.c split_pip.c \
	clear_list.c get_env_realine.c print_list.c change_var.c

all: $(NAME)

$(NAME):$(OBJ)
	@ar rc $(NAME) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o

fclean:clean
	$(RM) $(NAME) 
re: fclean all

.PHONY: all clean fclean re