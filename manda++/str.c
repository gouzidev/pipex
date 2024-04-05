#include "pipex.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    char *new_str;
    int i;

    new_str = malloc(ft_strlen(str) + 1);
    i = 0;
    while (str[i])
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}
