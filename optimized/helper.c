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

void	setup_hd(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	int	**fds;
	int	i;
	char	*line;
	pipex->is_here_doc = 1;
	pipex->cmds = parse_commands(pipex, gc, ac, av);
	pipex->status = 0;
	printf("n_cmds: %d\n", pipex->n_cmds);
	printf("n_pips: %d\n", pipex->n_pips);
	pipex->pids = gc_malloc(gc, sizeof(int) * 2);
	pipex->status = 0;
	pipex->pipes = init_pipes(pipex, gc, pipex->n_cmds);
	pipex->outfile = av[ac - 1];
	pipex->infile = NULL;
	pipex->infile_fd = 0;
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_status(pipex, ac, av);

	pipe(pipex->here_doc_fd);
	line = get_next_line(0, gc);
	while (ft_strcmp(line, ft_strjoin(av[2], "\n", gc)) != 0)
	{
		write(pipex->here_doc_fd[1], line, len(line));
		line = get_next_line(0, gc);
	}
}

void	setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	t_node	*new_node;

	pipex->is_here_doc = 0;
	pipex->cmds = parse_commands(pipex, gc, ac, av);
	pipex->status = 0;
	pipex->pids = gc_malloc(gc, (pipex->n_cmds * sizeof(int)));
	pipex->pipes = init_pipes(pipex, gc, pipex->n_cmds);
	pipex->infile_fd = open(av[1], O_RDONLY);
	pipex->outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_status(pipex, ac, av);
}

void	handle_infile(t_pipex *pipex)
{
	int	fd_null;

	if (pipex->infile_fd == -1)
	{
		fd_null = open("/dev/null", O_RDONLY);
		if (fd_null == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(fd_null, 0);
		close(pipex->infile_fd);
		close(fd_null);
		pipex->status = 0;
	}
}

void	handle_status(t_pipex *pipex, int ac, char *av[])
{
	if (pipex->infile_fd == -1)
	{
		if (access(av[1], F_OK) == -1)
			perror(av[1]);
		else if (access(av[1], R_OK) == -1)
			perror(av[1]);
		pipex->status = 1;
	}
	if (pipex->outfile_fd == -1)
	{
		perror(av[ac - 1]);
		pipex->status = 1;
		exit(1);
	}
}
