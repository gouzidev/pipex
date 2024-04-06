#include "pipex.h"

char **parse_commands(t_pipex *pipex, t_node **gc, int  ac, char *av[])
{
    char **cmds;
    int i;
    cmds = (char **)gc_malloc(gc, (ac - 2) * sizeof(char *));
    i = 2;
    while (i < ac - 1)
    {
        cmds[i - 2] = ft_strdup(av[i], gc);
        i++;
    }
    cmds[i - 2] = NULL;
    return cmds;
}