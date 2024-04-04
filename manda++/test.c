#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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

void close_pipes(int **pipes) {
    int i;

    i = 0;
    while (pipes[i])
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

int main(int ac, char *av[], char *env[])
{
    int **pipes;
    int n_cmds = 4;
    int status;
    int i;
    int j;
    char **cmd_args;
    char *env_path;
    char *cmd_path;
    char **cmds = malloc(4 * sizeof(char *));
    cmds = {"grep CC", "wc -l", "wc -l" };
    cmds[3] = NULL;
    pipes = init_pipes(n_cmds);

    int infile = open("Makefile", O_RDONLY); // Open the file for reading
    int outfile = open("outfile", O_WRONLY | O_CREAT, 0644); // Open the file for writing
    pid_t id;
    i = 0;
    j = 0;
    while (i < n_cmds)
    {
        id = fork();
        if (id == 0) {
            while (pipes[j])
            {
                if (j == 0)
                {
                    close(pipes[j][0]);
                    dup2(infile, STDIN_FILENO); // Redirect stdin from infile
                    dup2(pipes[j + 1][1], STDOUT_FILENO); // Redirect stdout to pipe1
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
                if (j == n_cmds - 1)
                {
                    close(pipes[j][1]);
                    dup2(outfile, STDOUT_FILENO); // Redirect stdout to outfile
                    dup2(pipes[j - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
                    close(infile);
                }
                else {
                    if (i != j - 1)
                        close(pipes[j][0]);
                    if (i != j + 1)
                    close(pipes[j][1]);
                    dup2(pipes[j - 1][0], STDIN_FILENO); // Redirect stdin from pipe2
                    dup2(pipes[j + 1][1], STDOUT_FILENO); // Redirect stdout to pipe1
                    close(infile);
                    close(outfile);
                }
                j++;
            }
        }
    }
    
    
    // Close file descriptors in the parent process
    close(infile);
    close(outfile);
    close_pipes(pipes);
    // Wait for all child processe0 to finish
    wait(&status);
    wait(&status);
    wait(&status);
    wait(&status);

    return 0;
}