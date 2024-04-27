/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:28 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/27 22:17:20 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**parse_commands(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	char	**cmds;
	int		i;

	if (pipex->is_here_doc)
	{
		pipex->n_cmds = ac - 4;
		cmds = (char **)gc_malloc(gc, (ac - 3) * sizeof(char *));
		i = 2;
		while (++i < ac - 1)
			cmds[i - 3] = ft_strdup(av[i], gc);
		cmds[i - 3] = NULL;
	}
	else
	{
		pipex->n_cmds = ac - 3;
		cmds = (char **)gc_malloc(gc, (ac - 2) * sizeof(char *));
		i = 1;
		while (++i < ac - 1)
			cmds[i - 2] = ft_strdup(av[i], gc);
		cmds[i - 2] = NULL;
	}
	pipex->n_pips = pipex->n_cmds - 1;
	return (cmds);
}

void	execute_cmd(t_pipex *pipex, int i, t_node **gc)
{
	char	**cmd_args;
	char	*env_path;
	char	*cmd_path;

	if (ft_strcmp(pipex->cmds[i], "") == 0)
		(write(2, "permission denied: \n", 21), exit(126));
	cmd_args = ft_split(pipex->cmds[i], ' ', gc);
	if (!ft_strchr(cmd_args[0], '/'))
	{
		env_path = get_env_path(pipex->env);
		if (env_path)
		{
			cmd_path = find_cmd_path(env_path, cmd_args[0], gc);
			if (cmd_path)
				(handle_dup(pipex, i, gc), execve(cmd_path, cmd_args,
						pipex->env));
			else
				handle_unkown_cmd(cmd_args, gc);
		}
		else
			handle_unset_path(pipex, i, gc);
	}
	else
		handle_cmd_path(pipex, i, gc, cmd_args);
}

void	child(t_pipex *pipex, int i, t_node **gc)
{
	close_unused_pipes(pipex, i, gc);
	close_unused_files(i, pipex, gc);
	close_here_doc_fd(pipex, gc);
	execute_cmd(pipex, i, gc);
}

void	parent(t_pipex *pipex, t_node **gc)
{
	int	i;
	int	status;
	int	terminated_pid;

	close_allthe_pipes(pipex, pipex->pipes, gc);
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

int	main(int ac, char *av[], char *env[])
{
	struct s_pipex	pipex;
	t_node			*gc;
	int				i;
	int				id;

	gc = gc_init();
	check_n_setup(&pipex, &gc, ac, av);
	pipex.env = env;
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
	parent(&pipex, &gc);
	return (0);
}
