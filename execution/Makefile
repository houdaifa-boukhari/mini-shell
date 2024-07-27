NAME = mini-shell
HEADER = mini-shell.h
SRC =  mini_shell.c env.c execution.c tools_list.c utilise_blt.c utilise.c utilise1.c\
	 ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c herdoc.c
CFLAGS =
LDFLAGS = -g
LIBS =  ./libft/*.c ../parsing/*.c
RM = rm -f
CC = gcc

all: $(NAME)

libft:
	make all -C ./libft
	make bonus -C ./libft

parsing:
	make all -C ../parsing

$(NAME) : $(SRC)
	$(CC)  $(LDFLAGS) $(LIBS) $(SRC) -lreadline  -o $(NAME)

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
