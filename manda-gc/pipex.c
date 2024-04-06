#include "pipex.h"

// void free_split(char **split)
// {
//     int i;

//     i = 0;
//     while (split[i])
//         free(split[i++]);
//     free(split);
// }


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
                if (flag == 0)
                {
                    dup2(pipex->infile, STDIN_FILENO); // Redirect stdin from pipex->infile
                    dup2(pipex->pipes[i][1], STDOUT_FILENO); // Redirect stdout to pipe1
                }
                else if (flag == 1)
                {
                    dup2(pipex->pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
                    dup2(pipex->pipes[i][1], STDOUT_FILENO); // Redirect stdout to pipe1
                }
                else
                {
                    dup2(pipex->outfile, STDOUT_FILENO); // Redirect stdout to pipex->outfile
                    dup2(pipex->pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
                }
                execve(cmd_path, cmd_args, pipex->env);

            }
            else
            {
                printf("command not found: %s\n", cmd_args[0]);
                gc_clear(gc);
                if (flag == 2)
                {
                    exit(127);
                }
            }
        }
        perror("path was not set\n");
        gc_clear(gc);
        // pipex->status = 127;
        exit(127);
    }
    else
    {
        execve(cmd_args[0], cmd_args, pipex->env);
        printf("no such file or directory: %s\n", cmd_args[0]);
        gc_clear(gc);
        // pipex->status = 127;
        exit(127);
    }
}

void childi(t_pipex *pipex, int i, t_node **gc)
{
    if (pipex->infile != -1)
        close(pipex->infile);
    if (pipex->outfile != -1)
        close(pipex->outfile);
    execute_cmd(pipex, i, 1, gc);
}

void child1(t_pipex *pipex, int i, t_node **gc)
{
    close(pipex->outfile);
    execute_cmd(pipex, i, 0, gc);
}

void childn(t_pipex *pipex, int i, t_node **gc)
{
    if (pipex->infile != -1)
        close(pipex->infile);
    execute_cmd(pipex, i, 2, gc);
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
        if (id == 0) {
            close_unused_pipes(pipex.pipes, i, pipex.n_pips);
            if (pipex.infile_status > 0 && i == 0)
                child1(&pipex, i, &gc);
            if (pipex.infile_status > 0 && i < pipex.n_cmds - 1)
                childi(&pipex, i, &gc);
            else
                childn(&pipex, i, &gc);
        }
        if (id == -1)
            perror("fork");
        else
            pipex.pids[i] = id;
        i++;
    }
    clean_up(&pipex);
    gc_clear(&gc);
    return 0;
}