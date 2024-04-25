/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:22 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/24 23:33:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_dup_hd(t_pipex *pipex, int i)
{
	int	**fds;

	fds = pipex->pipes;
	if (i == 0)
	{
		dup2(fds[0][0], STDIN_FILENO);
		dup2(fds[1][1], STDOUT_FILENO);
		close(fds[0][1]);
		close(fds[1][0]);
	}
	else if (i == 1)
	{
		pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile_fd == -1 && access(pipex->outfile, X_OK) == -1)
			(ft_printf("permission denied: %s\n", pipex->outfile), exit(1));
		dup2(fds[1][0], STDIN_FILENO);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(fds[0][1]);
		close(fds[0][0]);
		close(fds[1][1]);
		close(pipex->outfile_fd);
	}
}

void	handle_cmd_path_hd(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
	if (access(cmd_args[0], F_OK) == -1)
	{
		ft_printf("no such file or directory: %s\n", cmd_args[0]);
		gc_clear(gc);
		exit(127);
	}
	else if (access(cmd_args[0], X_OK) == -1)
	{
		ft_printf("permission denied: %s\n", cmd_args[0]);
		gc_clear(gc);
		exit(126);
	}
	else
	{
		handle_dup_hd(pipex, i);
		execve(cmd_args[0], cmd_args, pipex->env);
		ft_printf("execve failed: %s\n", cmd_args[0]);
		gc_clear(gc);
		exit(127);
	}
}

void	execute_cmd_hd(t_pipex *pipex, int i, t_node **gc)
{
	char	**cmd_args;
	char	*env_path;
	char	*cmd_path;

	cmd_args = ft_split(pipex->cmds[i], ' ', gc);
	if (!ft_strchr(cmd_args[0], '/'))
	{
		env_path = get_env_path(pipex->env);
		if (env_path)
		{
			cmd_path = find_cmd_path(env_path, cmd_args[0], gc);
			if (cmd_path)
			{
				handle_dup_hd(pipex, i);
				execve(cmd_path, cmd_args, pipex->env);
				(gc_clear(gc), perror("execve"), exit(1));
			}
			else
				handle_unkown_cmd(pipex, cmd_args, i, gc);
		}
		else
			handle_unset_path(pipex, i, gc);
	}
	else
		handle_cmd_path_hd(pipex, i, gc, cmd_args);
}

void	setup_hd(t_pipex *pipex, t_node **gc, int ac, char *av[])
{
	int	**fds;
	int	i;

	pipex->n_cmds = ac - 4;
	pipex->cmds = gc_malloc(gc, (sizeof(char *) * pipex->n_cmds));
	pipex->cmds[0] = ft_strdup(av[3], gc);
	pipex->cmds[1] = ft_strdup(av[4], gc);
	pipex->pids = gc_malloc(gc, sizeof(int) * 2);
	pipex->status = 0;
	pipex->pipes = gc_malloc(gc, (sizeof(int *) * 2));
	fds = pipex->pipes;
	fds[0] = gc_malloc(gc, sizeof(int) * 2);
	fds[1] = gc_malloc(gc, sizeof(int) * 2);
	if (pipe(fds[0]) == -1)
		(gc_clear(gc), perror("pipe"), exit(1));
	if (pipe(fds[1]) == -1)
		(gc_clear(gc), perror("pipe"), exit(1));
	pipex->outfile = av[5];
	pipex->infile = NULL;
	pipex->infile_fd = 0;
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex->is_here_doc = 1;

}

void	clean_hd(t_pipex pipex, t_node **gc, int status)
{
	close(pipex.pipes[0][0]);
	close(pipex.pipes[0][1]);
	close(pipex.pipes[1][1]);
	close(pipex.pipes[1][0]);
	waitpid(pipex.pids[0], &status, 0);
	waitpid(pipex.pids[1], &status, 0);
	pipex.status = WEXITSTATUS(status);
	gc_clear(gc);
	exit(pipex.status);
}

void	handle_here_doc(int ac, char *av[], char *env[], t_node **gc)
{
	char	*line;
	int		status;
	int		i;
	int		id;
	t_pipex	pipex;

	setup_hd(&pipex, gc, ac, av);
	line = get_next_line(0, gc);
	while (ft_strcmp(line, ft_strjoin(av[2], "\n", gc)) != 0)
	{
		write(pipex.pipes[0][1], line, len(line));
		line = get_next_line(0, gc);
	}
	i = -1;
	while (++i < pipex.n_cmds)
	{
		id = fork();
		if (id == 0)
			execute_cmd(&pipex, i, gc);
		else if (pipex.pids[i] == -1)
			(gc_clear(gc), perror("fork"), exit(1));
		else
			pipex.pids[i] = id;
	}
}
