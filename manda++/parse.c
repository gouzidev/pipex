#include "pipex.h"

char **parse_commands(int  ac, char *av[])
{
    char **cmds;
    int i;
    cmds = (char **)malloc((ac - 2) * sizeof(char *));
    i = 2;
    while (i < ac - 1)
    {
        cmds[i - 2] = ft_strdup(av[i]);
        i++;
    }
    cmds[i - 2] = NULL;
    return cmds;
}