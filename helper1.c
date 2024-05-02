/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:14:59 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/27 22:20:48 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	pipex->outfile = av[ac - 1];
	pipex->infile = av[1];
	pipex->cmds = parse_commands(pipex, gc, ac, av);
	pipex->pids = gc_malloc(gc, (pipex->n_cmds * sizeof(int)));
	pipex->pipes = init_pipes(gc, pipex->n_cmds);
	pipex->status = 0;
	pipex->infile_fd = open(av[1], O_RDONLY);
	pipex->outfile_fd = -2;
}

void	check_infile(t_pipex *pipex, t_node **gc)
{
	if (ft_strcmp(pipex->infile, "") == 0)
	{
		write(2, "No such file or directory\n", 26);
		gc_clear(gc);
		exit(1);
	}
	if (pipex->infile_fd == -1)
	{
		if (access(pipex->infile, F_OK) == -1)
		{
			perror(pipex->infile);
			gc_clear(gc);
			exit(1);
		}
		else if (access(pipex->infile, R_OK) == -1)
		{
			perror(pipex->infile);
			gc_clear(gc);
			exit(1);
		}
	}
}

void	check_outfile(t_pipex *pipex, t_node **gc)
{
	if (ft_strcmp(pipex->outfile, "") == 0)
	{
		write(2, "No such file or directory\n", 26);
		gc_clear(gc);
		exit(1);
	}
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (pipex->outfile_fd == -1)
	{
		perror(pipex->outfile);
		gc_clear(gc);
		exit(1);
	}
}
