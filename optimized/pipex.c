/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:28 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/25 14:48:08 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_commands(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	char	**cmds;
	int		i;

	if (pipex->is_here_doc)
	{
		pipex->n_cmds = ac - 4;
		cmds = (char **)gc_malloc(gc, (ac - 3) * sizeof(char *));
		i = 2;
		while (++i < ac - 1)
			cmds[i - 3] = ft_strdup(av[i], gc);
		cmds[i - 3] = NULL;
	}
	else
	{
		pipex->n_cmds = ac - 3;
		cmds = (char **)gc_malloc(gc, (ac - 2) * sizeof(char *));
		i = 1;
		while (++i < ac - 1)
			cmds[i - 2] = ft_strdup(av[i], gc);
		cmds[i - 2] = NULL;
	}
	pipex->n_pips = pipex->n_cmds - 1;
	return (cmds);
}

int	main(int ac, char *av[], char *env[])
{
	struct s_pipex	pipex;
	t_node			*gc;
	int				i;
	int				id;

	if (ac < 5)
		(write(2, "usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 52), exit(1));
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		setup_hd(&pipex, &gc, ac, av);
	else
		setup(&pipex, &gc, ac, av);
	gc = gc_init();
	pipex.env = env;
	i = 0;
	while (i < pipex.n_cmds)
	{
		id = fork();
		if (id == 0)
			child(&pipex, i, &gc);
		else if (id == -1)
			(gc_clear(&gc), perror("fork"), exit(1));
		else
			pipex.pids[i] = id;		
		i++;
	}
	parent(&pipex, &gc);
	return (0);
}
