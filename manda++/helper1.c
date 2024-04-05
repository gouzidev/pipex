#include "pipex.h"

void clean_up(t_pipex *pipex)
{
    int i;

    if (pipex->infile != -1)
    close(pipex->infile);
    if (pipex->outfile != -1)
        close(pipex->outfile);
    close_allthe_pipes(pipex->pipes);
    i = 0;
    while (i < pipex->n_cmds)
    {
        if (waitpid(pipex->pids[i], NULL, 0) < 0)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void setup(t_pipex *pipex, int  ac, char   *av[], char *env[])
{
    pipex->n_cmds = ac - 3;
    pipex->n_pips = pipex->n_cmds - 1;
    pipex->pids = malloc(pipex->n_cmds * sizeof(pid_t)); // Array to store PIDs
    if (pipex->pids == NULL)
        (printf("exit \n"), exit(1));
    
    pipex->cmds = parse_commands(ac, av);
    if (pipex->cmds == NULL)
        (free(pipex->pids), exit(1));
    pipex->infile = open(av[1], O_RDONLY); // Open the file for reading
    pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT, 0644); // Open the file for writing
    handle_status(pipex, ac, av);
    pipex->pipes = init_pipes(pipex->n_cmds);
    pipex->env = env;
}

void freee(t_pipex *pipex)
{
    int i;

    i = 0;
    while (pipex->pipes[i])
        free(pipex->pipes[i++]);
    free(pipex->pipes);
    i = 0;
    while (pipex->cmds[i])
        free(pipex->cmds[i++]);
    free(pipex->cmds);
    free(pipex->pids);
}

void handle_status(t_pipex *pipex, int  ac, char *av[])
{
    pipex->outfile_status = 1;
    pipex->infile_status = 1;
    if (pipex->outfile== -1)
    {
        pipex->outfile_status = -1;
        if (access(av[ac - 1], F_OK) == 0)
            pipex->outfile_status = -2;
    }
    if (pipex->infile == -1)
    {
        pipex->infile_status = -1;
        if (access(av[1], F_OK) == 0)
            pipex->infile_status = -2;
    }
    if (pipex->infile_status == -1)
        printf("no such file or directory: %s\n", av[1]);
    if (pipex->infile_status == -2)
        printf("permission denied: %s\n", av[1]);
    if (pipex->outfile_status == -2)
        printf("permission denied: %s\n", av[ac - 1]);
}

