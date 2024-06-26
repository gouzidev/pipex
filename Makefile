CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = pipex

BNAME = pipex_bonus

SRCS = pipex.c handle.c helper.c helper1.c split.c path.c str.c pipe.c gc.c gnl.c

OBJS = $(SRCS:.c=.o)

BSRCS = ./bonus/pipex_bonus.c ./bonus/handle_bonus.c ./bonus/helper_bonus.c ./bonus/helper1_bonus.c ./bonus/split_bonus.c ./bonus/path_bonus.c ./bonus/str_bonus.c ./bonus/pipe_bonus.c ./bonus/gc_bonus.c ./bonus/gnl_bonus.c

BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

%o: %c
	$(CC) $(CFLAGS) -c $? -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(BOBJS)
	$(CC) $(CFLAGS) $^ -o $(BNAME)

re:	fclean all

clean:
	rm -rf $(OBJS)
	rm -rf $(BOBJS)

fclean:	clean
	rm -rf $(NAME)
	rm -rf $(BNAME)