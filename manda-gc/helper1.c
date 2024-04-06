#include "pipex.h"

void parent(t_pipex *pipex, t_node **gc)
{
    int i;
    int status;

    if (pipex->infile != -1)
    close(pipex->infile);
    if (pipex->outfile != -1)
        close(pipex->outfile);
    close_allthe_pipes(pipex->pipes);
    i = 0;
    while (i < pipex->n_cmds)
    {
        if (waitpid(pipex->pids[i], &status, 0) < 0)
        {
            perror("waitpid");
            printf("failed waiting %d\n", pipex->status);
            gc_clear(gc);
            exit(-5);
        }
        i++;
    }
    gc_clear(gc);
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
}

