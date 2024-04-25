# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    int id1;
    int id2;
    int status;

    id1 = fork();

    if (id1 == 0)
    {
        char **args1;
        args1 = malloc(sizeof(char *) * 2);
        args1[0] = "/bin/pwd";
        args1[1] = NULL;
        execve("/bin/pwd", args1, NULL);
    }
    else
        wait(&status);
    
    id2 = fork();
    if (id2 == 0)
    {
        char **args2;
        args2 = malloc(sizeof(char *) * 3);
        args2[0] = "/bin/ls";
        args2[1] = "9";
        args2[2] = NULL;
        execve("/bin/ls", args2, NULL);
    }
    else
        wait(&status);
    printf("Done\n");
    return (status >> 8);
}