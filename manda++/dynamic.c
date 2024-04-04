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

int main() {

    int n_cmds = 4;
    int **pipes; // Array of pipes
    int **cmmds; // Array of pipes
    pipes = init_pipes(n_cmds);

    int infile = open("Makefile", O_RDONLY); // Open the file for reading
    int outfile = open("outfile", O_WRONLY | O_CREAT, 0644); // Open the file for writing
    pid_t childA, childB, childC, childD;

    childA = fork();
    if (childA == 0) {
        // Child process 0
        close (pipes[0][0]);
        // close (pipes[0][1]);
        close (pipes[1][0]);
        close (pipes[1][1]);
        close (pipes[2][0]);
        close (pipes[2][1]);
        dup2(infile, STDIN_FILENO); // Redirect stdin from infile
        dup2(pipes[0][1], STDOUT_FILENO); // Redirect stdout to pipe1
        execlp("head", "head", "-4", NULL);
        perror("child 1 couldnt exec");
        exit(1); // Exit upon error
    }
    childB = fork();
    if (childB == 0) {        
        // Child process 1
        // close (pipes[0][0]);
        close (pipes[0][1]);
        close (pipes[1][0]);
        // close (pipes[1][1]);
        close (pipes[2][0]);
        close (pipes[2][1]);
        
        dup2(pipes[0][0], STDIN_FILENO); // Redirect stdin from pipe1
        dup2(pipes[1][1], STDOUT_FILENO); // Redirect stdout to pipe2
        execlp("grep", "grep", "-", NULL);
        perror("child 2 couldnt exec");
        exit(1); // Exit upon error
    }
    childC = fork();
    if (childC == 0) {
        // Child process 2
        close (pipes[0][0]);
        close (pipes[0][1]);
        // close (pipes[1][0]);
        close (pipes[1][1]);
        close (pipes[2][0]);
        // close (pipes[2][1]);
        dup2(pipes[1][0], STDIN_FILENO); // Redirect stdin from pipe2
        dup2(pipes[2][1], STDOUT_FILENO); // Redirect stdout to outfile
        execlp("wc", "wc", NULL);
        perror("child 3 couldnt exec");
        exit(1); // Exit upon error
    }
    childD = fork();
    if (childD == 0) {
        // Child process 3
        close (pipes[0][0]);
        close (pipes[0][1]);
        close (pipes[1][0]);
        close (pipes[1][1]);
        // close (pipes[2][0]);
        close (pipes[2][1]);
        
        dup2(pipes[2][0], STDIN_FILENO); // Redirect stdin from pipe2
        dup2(outfile, STDOUT_FILENO); // Redirect stdout to outfile
        execlp("awk", "awk", "{print $3}", NULL);
        perror("child 3 couldnt exec");
        exit(1); // Exit upon error
    }
    // Close file descriptors in the parent process
    close(infile);
    close(outfile);
    close_pipes(pipes);
    // Wait for all child processe0 to finish
    waitpid(childA, NULL, 0);
    waitpid(childB, NULL, 0);
    waitpid(childC, NULL, 0);
    waitpid(childD, NULL, 0);

    return 0;
}