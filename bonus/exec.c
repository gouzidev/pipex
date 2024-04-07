#include "pipex.h"

void handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args)
{
    if (access(cmd_args[0], F_OK) == -1)
    {
        printf("no such file or directory: %s\n", cmd_args[0]);
        gc_clear(gc);
        if (i == pipex->n_cmds - 1)
            exit(127); // last path to cmd not found
        exit(0); // path to cmd not found
    }
    else if (access(cmd_args[0], X_OK) == -1)
    {
        printf("permission denied: %s\n", cmd_args[0]);
        gc_clear(gc);
        if (i == pipex->n_cmds - 1)
            exit(126); // last path to cmd not found
        exit(0); // path to cmd not found

    }
    else
    {
        handle_dup(pipex, i);
        execve(cmd_args[0], cmd_args, pipex->env);
        printf("execve failed: %s\n", cmd_args[0]);
        gc_clear(gc);
        if (i == pipex->n_cmds - 1)
            exit(127); // last path to cmd not found
        exit(0); // path to cmd not found
    }
}

void handle_unset_path(t_pipex *pipex, int  i, t_node **gc)
{
    perror("path was not set\n");
    gc_clear(gc);
    if (i == pipex->n_cmds - 1)
        exit(127); // last path was not set
    else
        exit(0); // path was not set
}

void handle_unkown_cmd(t_pipex *pipex, char **cmd_args, int i, t_node **gc)
{
    printf("command not found: %s\n", cmd_args[0]);
    gc_clear(gc);
    if (i == pipex->n_cmds - 1)
        exit(127); // last cmd not found
    exit(10); // cmd not found
}

void handle_dup(t_pipex *pipex, int i)
{
    if (i == 0)
    {
        if (pipex->infile == -1)
            handle_infile(pipex);
        dup2(pipex->infile, STDIN_FILENO); 

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

void execute_cmd(t_pipex *pipex, int i, t_node **gc)
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
                handle_unkown_cmd(pipex, cmd_args, i, gc);
        }
        else
            handle_unset_path(pipex, i, gc);
    }
    else
        handle_cmd_path(pipex, i, gc, cmd_args);
}
