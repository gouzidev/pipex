#include "pipex.h"

int main(int ac, char *av[], char *env[])
{
    int id;
    char **cmd_args;
    int status;
    int fds[2];

    if (ac != 5)
        exit_print("bad number of args");

    int infile_fd = open(av[1], O_RDONLY);
    int outfile_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);

    pipe(fds); // Create the pipe before the fork

    id = fork();
    if (id == 0)
    {
        dup2(infile_fd, STDIN_FILENO); // redirect the input file to stdin
        dup2(fds[1], STDOUT_FILENO); // redirect stdout to the write end of the pipe
        close(fds[0]); // close the read end of the pipe, it's not needed in this process
        close(infile_fd);
        cmd_args = ft_split("grep CC", ' ');
        execve("/usr/bin/grep", cmd_args, env);
		perror("cant execve 1\n");
    }

    id = fork();
    if (id == 0)
    {
        dup2(fds[0], STDIN_FILENO); // redirect the read end of the pipe to stdin
        dup2(outfile_fd, STDOUT_FILENO); // redirect stdout to the output file
        close(fds[1]); // close the write end of the pipe, it's not needed in this process
        close(outfile_fd);
        cmd_args = ft_split("wc -l", ' ');
        execve("/usr/bin/wc", cmd_args, env);
		perror("cant execve 2\n");
    }

    close(fds[0]); // close the read end of the pipe in the parent process
    close(fds[1]); // close the write end of the pipe in the parent process

    wait(&status);
    wait(&status);

    return 0;
}