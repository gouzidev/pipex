CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

SRCS = pipex.c exec.c ./utils/split.c helper.c ./utils/path.c ./utils/str.c pipe.c ./utils/gc.c ./utils/gnl.c ./utils/printf.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC)  $^ -o $(NAME)
	rm -rf $(OBJS)

%o:%c
	$(CC)  -c $<
re:	fclean all

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)%