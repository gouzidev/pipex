#include "pipex.h"

void gc_push(t_node **gc, void *data)
{
	t_node *new_node;

	if (data == NULL)
	{
		gc_clear(gc);
		perror("malloc\n");
		exit(1);
	}
	new_node = malloc(sizeof(t_node));
	if (new_node == 0)
	{
		gc_clear(gc);
		perror("malloc\n");
		exit(1);
	}
	new_node->data = data;
	new_node->next = *gc;
	*gc = new_node;
}

void *gc_malloc (t_node **gc, size_t size)
{
	t_node	*new_node;
	void *ptr;

	ptr = malloc(size);
	if (ptr == 0)
	{
		gc_clear(gc);
		perror("malloc\n");
		exit(1);
	}
	new_node = malloc(sizeof(t_node));
	if (new_node == 0)
	{
		gc_clear(gc);
		perror("malloc\n");
		exit(1);
	}
	new_node->data = ptr;
	new_node->next = *gc;
	*gc = new_node;
	return (ptr);
}

t_node* gc_init()
{
    return NULL; // Initialize the garbage collector (linked list) as empty
}

void	gc_clear(t_node **gc)
{
	t_node	*curr;
	t_node	*temp;

	curr = *gc;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
        free(temp->data);
		free(temp);
	}
}

