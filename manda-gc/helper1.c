#include "pipex.h"

void clean_up(t_pipex *pipex)
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
            exit(EXIT_FAILURE);
        }
        i++;
    }
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

// void freee(t_pipex *pipex)
// {
//     int i;

//     i = 0;
//     while (pipex->pipes[i])
//         free(pipex->pipes[i++]);
//     free(pipex->pipes);
//     i = 0;
//     while (pipex->cmds[i])
//         free(pipex->cmds[i++]);
//     free(pipex->cmds);
//     free(pipex->pids);
// }

void ft_free_data(void **data)
{
    if (*data)
    {
        free(*data);
        *data = NULL;
    }
}

void ft_free_node(t_node **node)
{
    if (*node)
    {
        free(*node);
        *node = NULL;
    }
}

void handle_status(t_pipex *pipex, int  ac, char *av[])
{
}

