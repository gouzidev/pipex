#include "pipex.h"



void handle_status(int outfile_fd, int infile_fd, int *out_file_status_code, int *in_file_status_code, int  ac, char *av[])
{
    if (outfile_fd == -1)
    {
        *out_file_status_code = -1;
        if (access(av[ac - 1], F_OK) == 0)
            *out_file_status_code = -2;
    }

    if (infile_fd == -1)
    {
        *in_file_status_code = -1;
        if (access(av[1], F_OK) == 0)
            *in_file_status_code = -2;
    }
    if (*in_file_status_code == -1)
        printf("no such file or directory: %s\n", av[1]);
    if (*in_file_status_code == -2)
        printf("permission denied: %s\n", av[1]);
    if (*out_file_status_code == -2)
        printf("permission denied: %s\n", av[ac - 1]);
}

int** init_pipes(int n_cmds) {
    int i;
    int **pipes;

    pipes = malloc(n_cmds * sizeof(int *));
    i = 0;
    while (i < n_cmds - 1)
    {
        pipes[i] = malloc(2 * sizeof(int));
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        i++;
    }
    pipes[i] = NULL;
    return (pipes);
}
void print_pipes(int **pipes) {
    int i;

    i = 0;
    while (pipes[i])
    {
        printf("pipe %d -> %d\n", i, pipes[i][0]);
        printf("pipe %d -> %d\n", i, pipes[i][1]);
        i++;
    }
}

void close_allthe_pipes(int **pipes) {
    int i;

    i = 0;
    while (pipes[i])
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void close_unused_pipes(int **pipes, int process_index, int n_pips) {
    int i;

    i = 0;
    while (i < n_pips)
    {
        if (process_index == 0)
        {
            if (i != 0)
                close(pipes[i][1]);
            else
                printf("first writing -> %d\n", pipes[i][1]);
            close(pipes[i][0]);
        }
        else if (process_index != n_pips)
        {
            if (process_index != i + 1)
                close(pipes[i][0]);
            else
                printf("middle reading -> %d\n", pipes[i][0]);
            if (process_index != i)
                close(pipes[i][1]);
            else
                printf("middle writing -> %d\n", pipes[i][1]);
        }
        else // last process
        {
            if (i != process_index - 1)
                close(pipes[i][0]);
            else
                printf("last reading -> %d\n", pipes[i][0]);
            close(pipes[i][1]);
        }
        i++;
    }
}


int main(int ac, char *av[], char *env[])
{
    int **pipes;
    int n_cmds = 4;
    int n_pips = n_cmds - 1;
    pid_t *pids = malloc(n_cmds * sizeof(pid_t)); // Array to store PIDs
    int status;
    int i;
    char **cmd_args;
    char *env_path;
    char *cmd_path;
    char **cmds = malloc((n_cmds + 1) * sizeof(char *));
    cmds[0] = "head -4";
    cmds[1] = "grep -";
    cmds[2] = "wc";
    cmds[3] = "cat";
    cmds[4] = NULL;
    // 3 
    int infile = open("Makefile", O_RDONLY); // Open the file for reading
    // 4
    int outfile = open("outfile", O_WRONLY | O_CREAT, 0644); // Open the file for writing
    // 5 6   7 8   9 10
    pipes = init_pipes(n_cmds);

    pid_t id;
    i = 0;
    while (i < n_cmds)
    {
        id = fork();
        if (id == 0) {
            printf("child i %d \n", i);
            close_unused_pipes(pipes, i, n_pips);
            if (i == 0)
            {
                dup2(infile, STDIN_FILENO); // Redirect stdin from infile
                dup2(pipes[i][1], STDOUT_FILENO); // Redirect stdout to pipe1
                close(outfile);
                cmd_args = ft_split(cmds[i], ' ');
                if (!is_path(cmd_args[0]))
                {
                    env_path = get_env_path(env);
                    if (env_path)
                    {
                        cmd_path = find_cmd_path(env_path, cmd_args[0]);
                        if (cmd_path)
                            execve(cmd_path, cmd_args, env);
                        exit(0);
                    }
                    printf("path was not set\n");
                    exit(1);
                }
                else
                    execve(cmd_args[0], cmd_args, env);
                perror("cant execve 2\n");
                exit(1);
            }
            if (i == n_cmds - 1)
            {
                dup2(outfile, STDOUT_FILENO); // Redirect stdout to outfile
                dup2(pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
                close(infile);
                cmd_args = ft_split(cmds[i], ' ');
                if (!is_path(cmd_args[0]))
                {
                    env_path = get_env_path(env);
                    if (env_path)
                    {
                        cmd_path = find_cmd_path(env_path, cmd_args[0]);
                        if (cmd_path)
                            execve(cmd_path, cmd_args, env);
                        exit(0);
                    }
                    printf("path was not set\n");
                    exit(1);
                }
                else
                    execve(cmd_args[0], cmd_args, env);
                perror("cant execve 2\n");
                exit(1);
            }
            else {
                dup2(pipes[i - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
                dup2(pipes[i][1], STDOUT_FILENO); // Redirect stdout to pipe1
                close(infile);
                close(outfile);
                cmd_args = ft_split(cmds[i], ' ');
                if (!is_path(cmd_args[0]))
                {
                    env_path = get_env_path(env);
                    if (env_path)
                    {
                        cmd_path = find_cmd_path(env_path, cmd_args[0]);
                        if (cmd_path)
                            execve(cmd_path, cmd_args, env);
                        exit(0);
                    }
                    printf("path was not set\n");
                    exit(1);
                }
                else
                    execve(cmd_args[0], cmd_args, env);
            }
        }
        if (id == -1)
            perror("fork");
        else
            pids[i] = id;
        i++;
    }
    
    
    // Close file descriptors in the parent process
    close(infile);
    close(outfile);
    close_allthe_pipes(pipes);
    // Wait for all child processe0 to finish
    for (i = 0; i < n_cmds; i++) {
        if (waitpid(pids[i], NULL, 0) < 0) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}