#include "pipex.h"

void	child(t_pipex *pipex, int i, t_node **gc)
{
	close_unused_pipes(pipex, pipex->pipes, i, pipex->n_pips);
	close_unused_files(i, pipex);
	execute_cmd(pipex, i, gc);
}

void	parent(t_pipex *pipex, t_node **gc)
{
	int	i;
	int	status;
	int	terminated_pid;

	if (pipex->outfile_fd != -1)
		close(pipex->outfile_fd);
	if (pipex->infile_fd != -1)
		close(pipex->infile_fd);
	close_allthe_pipes(pipex, pipex->pipes);
	i = 0;
	while (i < pipex->n_cmds)
	{
		terminated_pid = waitpid(pipex->pids[i], &status, 0);
		if (terminated_pid < 0)
		{
			perror("waitpid");
			gc_clear(gc);
			exit(1);
		}
		pipex->status = status >> 8;
		i++;
	}
	gc_clear(gc);
	exit(pipex->status);
}