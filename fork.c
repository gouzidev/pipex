#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main()
{

    printf("only parent will write this\n");

    int id = fork();

    printf("hello\n");
    printf("world\n");
}