NAME = mini-shell
HEADER = mini-shelll.h
SRC = mini_shell.c env.c execution.c tools_list.c utilise_blt.c
OBJS = $(SRC:.c=.o)
CFLAGS = -g -fsanitize=address
LIBS = -L./libft -lft -lreadline
CC  = cc
RM = rm -f

all: libft $(NAME)

libft:
	make all -C ./libft
	make bonus -C ./libft

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C ./libft
fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re : fclean all

.PHONY: libft
