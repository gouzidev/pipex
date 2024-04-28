/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:21 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/27 22:48:34 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
void check_before_run(t_pipex *pipex, int i, t_node **gc)
{
	if (ft_strcmp(pipex->cmds[i], "") == 0)
	{
		write(2, "permission denied: \n", 21);
		gc_clear(gc);
		exit(126);
	}
	if (ft_strcmp(pipex->cmds[i], ".") == 0)
	{
		write(2, "not enough arguments: .\n", 25);
		gc_clear(gc);
		exit(1);
	}
}

void	check_n_setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	if (ac != 5)
		(write(2, "usage: ./pipex file1 cmd1 cmd2 file2\n", 38),
			exit(1));
	setup(pipex, gc, ac, av);
}
