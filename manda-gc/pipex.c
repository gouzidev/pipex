#include "pipex.h"

void handle_dup(t_pipex *pipex, int i)
{
    if (i == 0)
    {
        dup2(pipex->infile, STDIN_FILENO); // Redirect stdin from pipex->infile
        dup2(pipex->pipes[i][1], STDOUT_FILENO); // Redirect stdout to pipe1
    }
    else if (i != pipex->n_cmds - 1)
    {
        dup2(pipex->pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
        dup2(pipex->pipes[i][1], STDOUT_FILENO); // Redirect stdout to pipe1
    }
    else
    {
        dup2(pipex->outfile, STDOUT_FILENO); // Redirect stdout to pipex->outfile
        dup2(pipex->pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
    }
}

void handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
    handle_dup(pipex, i);
    execve(cmd_args[0], cmd_args, pipex->env);
    printf("no such file or directory: %s\n", cmd_args[0]);
    gc_clear(gc);
    exit(127);
}

void handle_unset_path(t_node **gc)
{
    perror("path was not set\n");
    gc_clear(gc);
    exit(127);
}

void handle_unkown_cmd(char **cmd_args, t_node **gc)
{
    printf("command not found: %s\n", cmd_args[0]);
    gc_clear(gc);
    exit(127);
}

void execute_cmd(t_pipex *pipex, int i, int flag, t_node **gc)
{
    char **cmd_args;
    char *env_path;
    char *cmd_path;
    cmd_args = ft_split(pipex->cmds[i], ' ', gc);
    if (!is_path(cmd_args[0]))
    {
        env_path = get_env_path(pipex->env);
        if (env_path)
        {
            cmd_path = find_cmd_path(env_path, cmd_args[0], gc);
            if (cmd_path)
            {
                handle_dup(pipex, i);
                execve(cmd_path, cmd_args, pipex->env);
            }
            else
                handle_unkown_cmd(cmd_args, gc);
        }
        else
            handle_unset_path(gc);
    }
    else
        handle_cmd_path(pipex, i, gc, cmd_args);
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
    handle_dup(pipex, i);
    execute_cmd(pipex, i, i, gc);
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