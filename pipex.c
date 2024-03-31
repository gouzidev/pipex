#include "pipex.h"

t_node *parse_cmds_linked_list(char **av, int ac)
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

void init_pipe(int	**pip)
{
	(*pip) = malloc(sizeof(int) * 2);
	(*pip)[0] = -1;
	(*pip)[1] = -1;
}

int	**pipes_arr(char **av, int ac)
{
	int	infile_fd = open(av[1], O_RDONLY);
	int	outfile_fd = open(av[ac - 1], O_WRONLY);
	int	**pipes;
	int	i;

	pipes = malloc((sizeof(int *)) * (ac));
	init_pipe(&pipes[0]);
	pipe(pipes[0]);
	dup2(infile_fd, pipes[0][0]);
	close(infile_fd);

	i = 1;
	while (i < ac)
	{
		init_pipe(&pipes[i]);
		pipe(pipes[i]);
		i++;
	}
	init_pipe(&pipes[i]);
	pipe(pipes[i]);
	dup2(outfile_fd, pipes[i][1]);
	close(outfile_fd);
	i++;
	printf("here\n");
	init_pipe(&pipes[i]);
	return pipes;
}



int main(int ac, char *av[], char *env[])
{

    int id;
	t_node	*head;
	t_node	*curr;
	char *path;
    char **cmd_args;
	int status;
    int **fds_arr;
	int i = 0;
	curr = parse_cmds_linked_list(av, ac);
	int	infile_fd = open(av[1], O_RDONLY);
	int	outfile_fd = open(av[ac - 1], O_WRONLY);
	fds_arr = pipes_arr(av, ac);
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
