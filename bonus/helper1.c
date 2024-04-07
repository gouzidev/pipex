#include "pipex.h"

void parent(t_pipex *pipex, t_node **gc)
{
    int i;
    int status;
    pid_t terminated_pid;

    if (pipex->outfile != -1)
        close(pipex->outfile);
    close_allthe_pipes(pipex->pipes);
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
        else if (terminated_pid == pipex->pids[i]) // Check if the child has terminated
            pipex->status = WEXITSTATUS(status);
        i++;
    }
    gc_clear(gc);
    exit(pipex->status);
}

void setup(t_pipex *pipex, t_node **gc, int  ac, char   *av[], char *env[])
{
    t_node *new_node;
    pipex->status = 0;
    pipex->n_cmds = ac - 3;
    pipex->n_pips = pipex->n_cmds - 1;
    pipex->env = env;
    pipex->pids = gc_malloc(gc, (pipex->n_cmds * sizeof(pid_t)));
    pipex->cmds = parse_commands(pipex,gc, ac, av);
    pipex->pipes = init_pipes(pipex, gc, pipex->n_cmds);
    pipex->infile = open(av[1], O_RDONLY); // Open the file for reading
    pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT, 0644); // Open the file for writing
    handle_status(pipex, ac, av);

}

void handle_status(t_pipex *pipex, int  ac, char *av[])
{
    if (pipex->infile == -1)
    {
        if (access(av[1], F_OK) == -1)
            printf("no such file or directory: %s\n", av[1]);
        else if (access(av[1], R_OK) == -1)
            printf("permission denied: %s\n", av[1]);
        pipex->status = 1;
    }
    if (pipex->outfile == -1)
    {
        printf("permission denied: %s\n", av[ac - 1]);  
        pipex->status = 1;
        exit(1);
    }
}

