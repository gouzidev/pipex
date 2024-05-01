/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:21 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/28 01:33:41 by sgouzi           ###   ########.fr       */
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

void	perror_clear_exit(char *str, t_node **gc, int exit_code)
{
	perror(str);
	gc_clear(gc);
	exit(exit_code);
}

void	check_n_setup(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	if (ac != 5)
		(write(2, "usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 51),
			exit(1));
	setup(pipex, gc, ac, av);
}
