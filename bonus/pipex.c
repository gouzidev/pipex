/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:28 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 18:09:29 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_commands(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	char	**cmds;
	int		i;
	int		n_cmds;

	n_cmds = ac - 3;
	cmds = (char **)gc_malloc(gc, (ac - 2) * sizeof(char *));
	i = 2;
	while (i < ac - 1)
	{
		cmds[i - 2] = ft_strdup(av[i], gc);
		i++;
	}
	cmds[i - 2] = NULL;
	return (cmds);
}

void	execute_here_doc_cmd(t_pipex *pipex, int i, t_node **gc)
{
	char	**cmd_args;
	char	*env_path;
	char	*cmd_path;

	cmd_args = ft_split(pipex->cmds[i], ' ', gc);
	if (!ft_strchr(cmd_args[0], '/'))
	{
		env_path = get_env_path(pipex->env);
		if (env_path)
		{
			cmd_path = find_cmd_path(env_path, cmd_args[0], gc);
			if (cmd_path)
			{
				handle_dup(pipex, i);
				execve(cmd_path, cmd_args, pipex->env);
			}
			else
				handle_unkown_cmd(pipex, cmd_args, i, gc);
		}
		else
			handle_unset_path(pipex, i, gc);
	}
	else
		handle_cmd_path(pipex, i, gc, cmd_args);
}

void	child(t_pipex *pipex, int i, t_node **gc)
{
	close_unused_pipes(pipex->pipes, i, pipex->n_pips);
	if (i == 0) // first child
	{
		close(pipex->outfile);
	}
	else if (i == pipex->n_cmds - 1) // last child
	{
		if (pipex->infile != -1)
			close(pipex->infile);
	}
	else
	{
		if (pipex->infile != -1)
			close(pipex->infile);
		if (pipex->outfile != -1)
			close(pipex->outfile);
	}
	execute_cmd(pipex, i, gc);
}

void	parent(t_pipex *pipex, t_node **gc, int hd_flag)
{
	int	i;
	int	status;
	int	terminated_pid;

	if (!hd_flag)
	{
		if (pipex->outfile != -1)
			close(pipex->outfile);
		close_allthe_pipes(pipex->pipes);
	}
	i = 0;
	while (i < pipex->n_cmds)
	{
		terminated_pid = waitpid(pipex->pids[i], &status, 0);
		if (terminated_pid < 0)
		{
			perror("waitpid");
			gc_clear(gc);
			exit(1);
		}
		pipex->status = status >> 8;
		i++;
	}
	gc_clear(gc);
	exit(pipex->status);
}

int	is_here_doc(int ac, char *av[])
{
	return (ac == 6 && ft_strncmp(av[1], "here_doc", 9) == 0);
}

int	main(int ac, char *av[], char *env[])
{
	struct s_pipex pipex;
	t_node *gc;
	int i;
	int id;

	if (ac < 5)
		(write(2, "usage: ./pipex infile cmd1 cmd2 outfile\n", 41), exit(1));
	gc = gc_init();
	if (is_here_doc(ac, av))
		(handle_here_doc(ac, av, env, &gc), exit(0));
	pipex.env = env;
	setup(&pipex, &gc, ac, av);
	i = 0;
	while (i < pipex.n_cmds)
	{
		id = fork();
		if (id == 0)
			child(&pipex, i, &gc);
		else if (id == -1)
			(gc_clear(&gc), perror("fork"), exit(1));
		else
			pipex.pids[i] = id;
		i++;
	}
	parent(&pipex, &gc, 0);
	return (0);
}