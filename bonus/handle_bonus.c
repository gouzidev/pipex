/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:14:53 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/28 01:11:20 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**handle_cmd_str(t_pipex *pipex, int i, t_node **gc, char *cmd)
{
	char	**cmd_args;

	if (ft_strcmp(cmd, "") == 0)
	{
		if (ft_strcmp(pipex->infile, "") == 0)
			perror(pipex->infile);
		exit(0);
		gc_clear(gc);
	}
	else if (ft_strcmp(cmd, ".") == 0)
	{
		handle_dup(pipex, i, gc);
		write(2, ".: filename argument required\n", 30);
		gc_clear(gc);
		exit(2);
	}
	else
		cmd_args = ft_split(cmd, " \t\n\v\f\r", gc);
	return (cmd_args);
}

void	handle_no_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	handle_dup(pipex, i, gc);
	if (access(cmd_args[0], F_OK) == -1)
		perror_clear_exit(cmd_args[0], gc, 127);
	else if (access(cmd_args[0], X_OK) == -1)
		perror_clear_exit(cmd_args[0], gc, 126);
	else
	{
		handle_dup(pipex, i, gc);
		execve(cmd_args[0], cmd_args, pipex->env);
		perror_clear_exit(cmd_args[0], gc, 127);
	}
}

void	handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	handle_dup(pipex, i, gc);
	if (access(cmd_args[0], F_OK) == -1)
		perror_clear_exit(cmd_args[0], gc, 127);
	else if (access(cmd_args[0], X_OK) == -1)
		perror_clear_exit(cmd_args[0], gc, 126);
	else
	{
		execve(cmd_args[0], cmd_args, pipex->env);
		if (errno == 13)
			perror_clear_exit(cmd_args[0], gc, 126);
		else
			perror_clear_exit(cmd_args[0], gc, 127);
	}
}

void	handle_fail(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	handle_dup(pipex, i, gc);
	write(2, cmd_args[0], len(cmd_args[0]));
	write(2, ": command not found\n", 21);
	gc_clear(gc);
	exit(127);
}

void	handle_dup(t_pipex *pipex, int i, t_node **gc)
{
	if (i == 0)
	{
		check_infile(pipex, gc);
		ft_dup2(pipex->infile_fd, 0, gc);
		ft_dup2(pipex->pipes[i][1], 1, gc);
	}
	else if (i != pipex->n_cmds - 1)
	{
		ft_dup2(pipex->pipes[i - 1][0], 0, gc);
		ft_dup2(pipex->pipes[i][1], 1, gc);
	}
	else
	{
		check_outfile(pipex, gc);
		ft_dup2(pipex->outfile_fd, 1, gc);
		ft_dup2(pipex->pipes[i - 1][0], 0, gc);
	}
}
