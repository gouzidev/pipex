/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:28 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/28 01:34:21 by sgouzi           ###   ########.fr       */
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

char	**handle_cmd_str(t_node **gc, char *cmd)
{
	char **cmd_args;

	if (ft_strcmp(cmd, "") == 0)
	{
		write(2, "'': command not found\n", 22);
		gc_clear(gc);
		exit(127);
	}
	else if (ft_strcmp(cmd, ".") == 0)
	{
		write(2, ".: filename argument required\n", 30);
		gc_clear(gc);
		exit(127);
	}
	else
		cmd_args = ft_split(cmd, ' ', gc);
	return (cmd_args);
}

void handle_no_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	if (access(cmd_args[0], F_OK) == -1)
	{
		perror(cmd_args[0]);
		gc_clear(gc);
		exit(127);
	}
	else if (access(cmd_args[0], X_OK) == -1)
	{
		perror(cmd_args[0]);
		gc_clear(gc);
		exit(126);
	}
	else
	{
		handle_dup(pipex, i, gc);
		execve(cmd_args[0], cmd_args, pipex->env);
		perror("execve");
		gc_clear(gc);
		exit(127);
	}
}
void handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	handle_dup(pipex, i, gc);
	execve(cmd_args[0], cmd_args, pipex->env);
	perror(cmd_args[0]);
	gc_clear(gc);
	exit(127);
}


void	execute_cmd(t_pipex *pipex, int i, t_node **gc)
{
	char	**cmd_args;
	char	*env_path;
	char	*cmd_path;
	cmd_args = handle_cmd_str(gc, pipex->cmds[i]);
	if (!ft_strchr(pipex->cmds[i], '/')) // if the command is not a path
	{
		env_path = get_env_path(pipex->env);
		if (env_path)
		{
			cmd_path = find_cmd_path(env_path, cmd_args[0], gc);
			handle_dup(pipex, i, gc);
			execve(cmd_path, cmd_args, pipex->env);
			perror(cmd_args[0]);
			gc_clear(gc);
			exit(127);
		}
		else
			handle_no_path(pipex, i, gc, cmd_args);
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
