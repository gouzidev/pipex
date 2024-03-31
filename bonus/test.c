#include "pipex.h"

int main(int ac, char *av[], char *env[])
{
    char *const *cmd;
    int fds[2];
    int fdin;
    int fdout;
    int id1;
    int status;

    fdin = open("Makefile", O_RDONLY);
    fdout = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    pipe(fds);

    id1 = fork();
    if (id1 == 0)
    {
        close(fds[0]); // Close read end of the pipe
        dup2(fdin, STDIN_FILENO); // Redirect stdin to input file
        dup2(fds[1], STDOUT_FILENO); // Redirect stdout to write end of the pipe
        close(fdin);
        close(fds[1]);
        cmd = ft_split("grep CC", ' ');
        execve("/usr/bin/grep", cmd, env);
        perror("Child 1 execve failed");
        exit(1);
    }

    id1 = fork();
    if (id1 == 0)
    {
        close(fds[1]); // Close write end of the pipe
        dup2(fds[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
        dup2(fdout, STDOUT_FILENO); // Redirect stdout to output file
        close(fdout);
        close(fds[0]);
        cmd = ft_split("grep $(CC)", ' ');
        execve("/usr/bin/grep", cmd, env);
        perror("Child 2 execve failed");
        exit(1);
    }

    // Close pipe in parent process
    close(fds[0]);
    close(fds[1]);
    close(fdin);
    close(fdout);

    // Wait for both child processes to finish
    waitpid(id1, &status, 0);

    return 0;
}