CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

SRCS = pipex.c helper.c helper1.c path.c str.c pipe.c parse.c
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