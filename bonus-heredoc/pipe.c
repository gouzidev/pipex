#include "pipex.h"

int** init_pipes(t_pipex *pipex, t_node **gc, int n_cmds)
{
    int i;
    int **pipes;

    pipes = gc_malloc(gc, n_cmds * sizeof(int *));
    i = 0;
    while (i < n_cmds - 1)
    {
        pipes[i] = gc_malloc(gc, 2 * sizeof(int));
        if (pipe(pipes[i]) == -1)
        {
            gc_clear(gc);
            perror("pipe");
            exit(5);
        }
        i++;
    }
    pipes[i] = NULL;
    return (pipes);
}

void close_allthe_pipes(int **pipes)
{
    int i;

    i = 0;
    while (pipes[i])
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void close_unused_pipes(int **pipes, int process_index, int n_pips)
{
    int i;

    i = 0;
    while (i < n_pips)
    {
        if (process_index == 0)
        {
            if (i != 0)
                close(pipes[i][1]);
            close(pipes[i][0]);
        }
        else if (process_index != n_pips)
        {
            if (process_index != i + 1)
                close(pipes[i][0]);
            if (process_index != i)
                close(pipes[i][1]);
        }
        else // last process
        {
            if (i != process_index - 1)
                close(pipes[i][0]);
            close(pipes[i][1]);
        }
        i++;
    }
}

