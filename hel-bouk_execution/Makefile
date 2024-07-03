NAME = mini-shell
HEADER = mini-shelll.h
SRC =  env.c execution.c tools_list.c utilise_blt.c utilise.c mini_shell.c
OBJS = $(SRC:.c=.o)
CFLAGS = -g -fsanitize=address
LIBS = -L./libft -lft  -lreadline
CC  = cc
RM = rm -f

all: libft  $(NAME)

libft:
	make all -C ./libft
	make bonus -C ./libft
zbakks:
	make all -C ../zbakks_parsing

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C ./libft
	make clean -C ../zbakks_parsing
fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft
	make fclean -C ../zbakks_parsing

re : fclean all

.PHONY: libft
