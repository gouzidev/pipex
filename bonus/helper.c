/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:21 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 18:10:49 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	t_node	*new_node;

	pipex->status = 0;
	pipex->n_cmds = ac - 3;
	pipex->n_pips = pipex->n_cmds - 1;
	pipex->pids = gc_malloc(gc, (pipex->n_cmds * sizeof(int)));
	pipex->cmds = parse_commands(pipex, gc, ac, av);
	pipex->pipes = init_pipes(pipex, gc, pipex->n_cmds);
	pipex->infile = open(av[1], O_RDONLY);
	pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_status(pipex, ac, av);
}

void	handle_infile(t_pipex *pipex)
{
	int	fd_null;

	if (pipex->infile == -1)
	{
		fd_null = open("/dev/null", O_RDONLY);
		if (fd_null == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(fd_null, STDIN_FILENO);
		close(pipex->infile);
		close(fd_null);
		pipex->status = 0;
	}
}

void	handle_status(t_pipex *pipex, int ac, char *av[])
{
	if (pipex->infile == -1)
	{
		if (access(av[1], F_OK) == -1)
			perror(av[1]);
		else if (access(av[1], R_OK) == -1)
			perror(av[1]);
		pipex->status = 1;
	}
	if (pipex->outfile == -1)
	{
		perror(av[ac - 1]);
		pipex->status = 1;
		exit(1);
	}
}
