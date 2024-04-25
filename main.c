# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int main(int    ac, char *av[], char *env[])
{
    int id;

    char **args1;
    args1 = malloc(sizeof(char *) * 2);
    args1[0] = "/bin/pwd";
    args1[1] = NULL;
    
    char **args2;
    args2 = malloc(sizeof(char *) * 2);
    args2[0] = "/bin/ls";
    args2[1] = NULL;
    
    id = fork();
    execve("/bin/pwd", args1, NULL);
    execve("/bin/ls", args2, NULL);
}