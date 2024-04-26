CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

SRCS = pipex.c exec.c split.c helper.c path.c str.c pipe.c gc.c gnl.c printf.c
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