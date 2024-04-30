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
