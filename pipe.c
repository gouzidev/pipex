/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:27 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/25 02:48:46 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**init_pipes(t_pipex *pipex, t_node **gc, int n_cmds)
{
	int	i;
	int	**pipes;

	pipes = gc_malloc(gc, n_cmds * sizeof(int *));
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes[i] = gc_malloc(gc, 2 * sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			gc_clear(gc);
			perror("pipe");
			exit(1);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

void	close_allthe_pipes(t_pipex *pipex, int **pipes, t_node **gc)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		ft_close(pipes[i][0], gc);
		ft_close(pipes[i][1], gc);
		i++;
	}
	close_here_doc_fd(pipex, gc);
	ft_close(pipex->infile_fd, gc);
}

void close_here_doc_fd(t_pipex *pipex, t_node **gc)
{
	if (pipex->is_here_doc)
	{
		close(pipex->here_doc_fd[0]);
		close(pipex->here_doc_fd[1]);
	}
}

void	close_unused_pipes(t_pipex *pipex, int **pipes, int process_index, t_node **gc)
{
	int	p;

	p = 0;
	while (p < pipex->n_pips)
	{
		if (process_index == 0)
		{
			if (p != 0)
				close(pipes[p][1]);
			close(pipes[p][0]);
			close_here_doc_fd(pipex, gc);
		}
		else if (process_index != pipex->n_pips)
		{
			if (process_index != p + 1)
				close(pipes[p][0]);
			if (process_index != p)
				close(pipes[p][1]);
			close_here_doc_fd(pipex, gc);
		}
		else
		{
			if (p != process_index - 1)
				close(pipes[p][0]);
			close(pipes[p][1]);
			close_here_doc_fd(pipex, gc);
		}
		p++;
	}
}

void close_unused_files(int i, t_pipex *pipex, t_node **gc)
{
	if (i == 0)
	{
		// close(pipex->outfile_fd);
	}
	else if (i == pipex->n_cmds - 1)
	{
		if (pipex->infile_fd > -1)
			ft_close(pipex->infile_fd, gc);
	}
	else
	{
		if (pipex->infile_fd > -1)
			ft_close(pipex->infile_fd, gc);
		if (pipex->outfile_fd > -1)
			ft_close(pipex->outfile_fd, gc);
	}
}

