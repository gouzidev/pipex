CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = pipex

SRCS = ./bonus/pipex_bonus.c ./bonus/handle_bonus.c ./bonus/helper_bonus.c ./bonus/helper1_bonus.c ./bonus/split_bonus.c ./bonus/path_bonus.c ./bonus/str_bonus.c ./bonus/pipe_bonus.c ./bonus/gc_bonus.c ./bonus/gnl_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%o: %c
	$(CC) $(CFLAGS) -c $? -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

re:	fclean all

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)