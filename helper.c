/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:21 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/25 13:44:48 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_close(int fd, t_node **gc)
{
	if (fd < 0)
		return ;
	int	r;

	r = close(fd);
	if (r == -1)
	{
		perror("close");
		gc_clear(gc);
		exit(1);
	}
}

void read_hd(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	char	*line;
	int		r;

	r = pipe(pipex->here_doc_fd);
	if (r == -1)
	{
		gc_clear(gc);
		perror("pipe");
		exit(1);
	}
	line = get_next_line(0, gc);
	while (ft_strcmp(line, ft_strjoin(av[2], "\n", gc)) != 0)
	{
		write(pipex->here_doc_fd[1], line, len(line));
		line = get_next_line(0, gc);
	}
}

void	setup_hd(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	pipex->is_here_doc = 1;
	pipex->outfile = av[ac - 1];
	pipex->infile = NULL;
	pipex->cmds = parse_commands(pipex, gc, ac, av);
	pipex->pids = gc_malloc(gc, (pipex->n_cmds * sizeof(int)));
	pipex->pipes = init_pipes(pipex, gc, pipex->n_cmds);
	pipex->status = 0;
	pipex->outfile_fd = -2;
	read_hd(pipex, gc, ac, av);
	pipex->infile_fd = dup2(pipex->here_doc_fd[0], 0);
}

void	setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	t_node	*new_node;

	pipex->is_here_doc = 0;
	pipex->outfile = av[ac - 1];
	pipex->infile = av[1];
	pipex->cmds = parse_commands(pipex, gc, ac, av);
	pipex->pids = gc_malloc(gc, (pipex->n_cmds * sizeof(int)));
	pipex->pipes = init_pipes(pipex, gc, pipex->n_cmds);
	pipex->status = 0;
	pipex->infile_fd = open(av[1], O_RDONLY);
	handle_infile(pipex, gc);
	pipex->outfile_fd = -2;
	pipex->here_doc_fd[0] = -2;
	pipex->here_doc_fd[1] = -2;
}

void	handle_infile(t_pipex *pipex, t_node **gc)
{
	int	fd_null;

	if (pipex->infile_fd == -1)
	{
		perror(pipex->infile);
		fd_null = open("/dev/null", O_RDONLY);
		if (fd_null == -1)
		{
			perror("open");
			gc_clear(gc);
			exit(1);
		}
		dup2(fd_null, 0);
		pipex->infile_fd = fd_null;
	}
}

void	check_infile(t_pipex *pipex)
{
	if (pipex->infile_fd == -1)
	{
		if (access(pipex->infile, F_OK) == -1)
			perror(pipex->infile);
		else if (access(pipex->infile, R_OK) == -1)
			perror(pipex->infile);
	}
}

void	check_outfile(t_pipex *pipex)
{
	if (pipex->outfile_fd == -1)
	{
		perror(pipex->outfile);
		exit(1);
	}
}