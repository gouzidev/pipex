CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

SRCS = pipex.c helper.c linked_list.c path.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC)  $^ libft.a -o $(NAME)
	rm -rf $(OBJS)

%o:%c
	$(CC)  -c $<
re:	fclean all

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)%