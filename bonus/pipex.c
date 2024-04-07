#include "pipex.h"

char **parse_commands(t_pipex *pipex, t_node **gc, int  ac, char *av[])
{
    char **cmds;
    int i;
    cmds = (char **)gc_malloc(gc, (ac - 2) * sizeof(char *));
    i = 2;
    while (i < ac - 1)
    {
        cmds[i - 2] = ft_strdup(av[i], gc);
        i++;
    }
    cmds[i - 2] = NULL;
    return cmds;
}

void child(t_pipex *pipex, int i, t_node **gc)
{
    close_unused_pipes(pipex->pipes, i, pipex->n_pips);
    if (i == 0) // first child
    {
        close(pipex->outfile);
    }
    else if (i == pipex->n_cmds - 1) // last child
    {
        if (pipex->infile != -1)
            close(pipex->infile);
    }
    else
    {
        if (pipex->infile != -1)
            close(pipex->infile);
        if (pipex->outfile != -1)
            close(pipex->outfile);
    }
    execute_cmd(pipex, i, gc);
}

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

int main(int ac, char *av[], char *env[])
{
    struct s_pipex pipex;
    t_node *gc;
    int i;
    pid_t id;

    if (ac < 5)
        perror("usage: ./pipex infile cmd1 cmd2 outfile");
    gc = gc_init();
    setup(&pipex, &gc, ac, av, env);
    i = 0;
    while (i < pipex.n_cmds)
    {
        id = fork();
        if (id == 0)
            child(&pipex, i, &gc);
        if (id == -1)
            (gc_clear(&gc), perror("fork"), exit(1));
        else
            pipex.pids[i] = id;
        i++;
    }
    parent(&pipex, &gc);
    return 0;
}