NAME = mini-shell
HEADER = mini-shell.h
SRC =  mini_shell.c env.c execution.c tools_list.c utilise_blt.c utilise.c
OBJS = $(SRC:.c=.o)
CFLAGS = -g -fsanitize=address
LDFLAGS = -fsanitize=address
LIBS = -lreadline ./libft/*.c ../parsing/*.c
RM = rm -f
CC = gcc

all: $(NAME)

libft:
	make all -C ./libft
	make bonus -C ./libft

parsing:
	make all -C ../parsing

$(NAME) : $(SRC)
	$(CC) $(LDFLAGS) $(LIBS) $(SRC) -o $(NAME)

# %.o : %.c $(HEADER)
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C ./libft
	make clean -C ../parsing

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft
	make fclean -C ../parsing

re : fclean all

.PHONY: libft parsing
