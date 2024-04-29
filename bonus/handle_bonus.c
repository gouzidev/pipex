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

void	handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	if (access(cmd_args[0], F_OK) == -1)
	{
		perror(cmd_args[0]);
		gc_clear(gc);
		if (errno == 13)
			exit(126);
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
		perror(cmd_args[0]);
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

void	handle_unkown_cmd(char **cmd_args, int i, t_node **gc)
{
	if (access(cmd_args[0], F_OK) == 0)
	{
		
	}
	if (i != 0)
	{
		write(2, "command not found: ", 20);
		write(2, cmd_args[0], len(cmd_args[0]));
		write(2, "\n", 1);
	}
	else
	{
		
	}
	gc_clear(gc);
	exit(127);
}

void	handle_dup(t_pipex *pipex, int i, t_node **gc)
{
	if (i == 0)
	{
		if (pipex->infile_fd < 0)
		{
			perror(pipex->infile);
			exit(1);
		}
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
		pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		check_outfile(pipex);
		ft_dup2(pipex->outfile_fd, 1, gc);
		ft_dup2(pipex->pipes[i - 1][0], 0, gc);
	}
}
