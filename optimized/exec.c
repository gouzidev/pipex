/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:08:21 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 22:33:58 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
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
		handle_dup(pipex, i);
		execve(cmd_args[0], cmd_args, pipex->env);
		perror("execve");
		gc_clear(gc);
		exit(127);
	}
}

void	handle_unset_path(t_pipex *pipex, int i, t_node **gc)
{
	write(2, "command not found: ", 20);
	write(2, pipex->cmds[i], len(pipex->cmds[i]));
	write(2, "\n", 1);
	gc_clear(gc);
	exit(127);
}

void	handle_unkown_cmd(t_pipex *pipex, char **cmd_args, int i, t_node **gc)
{
	perror(cmd_args[0]);
	gc_clear(gc);
	exit(127);
}

void	handle_dup(t_pipex *pipex, int i)
{
	printf("cmd %d  => %s\n", i, pipex->cmds[i]);
	printf("infile_fd %d\n", pipex->infile_fd);
	printf("cmds %i\n", pipex->n_cmds);
	if (i == 0)
	{
		if (pipex->infile_fd == -1)
			handle_infile(pipex);
		dup2(pipex->infile_fd, STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	else if (i != pipex->n_cmds - 1)
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	else
	{
		printf("outfile_fd %d\n", pipex->outfile_fd);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
	}
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
				(handle_dup(pipex, i), execve(cmd_path, cmd_args, pipex->env));
			else
				handle_unkown_cmd(pipex, cmd_args, i, gc);
		}
		else
			handle_unset_path(pipex, i, gc);
	}
	else
		handle_cmd_path(pipex, i, gc, cmd_args);
}
