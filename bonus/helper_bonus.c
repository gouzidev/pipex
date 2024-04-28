/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:21 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/28 01:33:41 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close(int fd, t_node **gc)
{
	int	r;

	if (fd < 0)
		return ;
	r = close(fd);
	if (r == -1)
	{
		perror("close");
		gc_clear(gc);
		exit(1);
	}
}

int	ft_dup2(int oldfd, int newfd, t_node **gc)
{
	int	r;

	r = dup2(oldfd, newfd);
	if (r == -1)
	{
		perror("dup2");
		gc_clear(gc);
		exit(1);
	}
	return (r);
}

void	read_hd(t_pipex *pipex, t_node **gc, char *av[])
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

void	check_n_setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	if (ac < 5)
		(write(2, "usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 52),
			exit(1));
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		setup_hd(pipex, gc, ac, av);
	else
		setup(pipex, gc, ac, av);
}
