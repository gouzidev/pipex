#include "pipex.h"



t_node *parse_cmds(char **av, int ac)
{
	t_node *head;
	t_node *curr;

	head = NULL;
	int	i;

	i = 2;
	while (i < ac - 1)
	{
		curr = new(av[i]);
		if (curr == NULL)
			exit_print("malloc failed\n");
		push(&head, curr);
		i++;
	}
	return head;
}

int is_path(t_node	*command)
{
	return (command->cmd[0] == '/' || command->cmd[0] == '.');
}

int main(int ac, char *av[], char *env[])
{
    int id;
	t_node	*head;
	t_node	*curr;
	char *path;
    char **cmd_args;
	int status;
    int i = 0;
	curr = parse_cmds(av, ac);
	while (curr)
	{
	    id = fork();
		if (id == 0)
		{
			if (!is_path(curr))
			{
				cmd_args = ft_split(curr->cmd, ' ');
				path = ft_strjoin("/bin/", cmd_args[0]);
				if (access(path, X_OK) == 0)
					execve(path, cmd_args, env);
			}
		}
		else
			wait(&status);
		curr = curr->next;
	}
}
