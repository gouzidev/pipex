#include "pipex.h"

t_node *new (char *cmd)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == 0)
		return (0);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->cmd = cmd;
	return (new_node);
}

void	push(t_node **head, t_node *new)
{
    t_node *curr;

    if (!new || !head)
        return;
    curr = *head;
    if (*head)
    {
        while (curr->next)
            curr = curr->next;
        curr->next = new;
		new->prev = curr;
    }
    else
    {
        new->next = *head;
		if (*head)
			(*head)->prev = new;
        *head = new;
    }
}

void	pop(t_node **head)
{
	t_node	*temp;

	if (!*head)
		return ;
	temp = *head;
	*head = (*head)->next;
	free(temp);
}

int	size(t_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_node	*duplicate(t_node *node)
{
	t_node	*temp;

	if (!node)
		return (NULL);
	temp = new (node->cmd);
	if (temp == NULL)
		return NULL;
	return (temp);
}

t_node	*last(t_node *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	clear(t_node **head)
{
	t_node	*curr;
	t_node	*temp;

	curr = *head;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}
