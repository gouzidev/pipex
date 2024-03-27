#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
static int	len(char const *s1)
{
	int	l;

	l = 0;
	while (s1[l])
		l++;
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	output = (char *)malloc((len(s1) + len(s2) + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < len(s1))
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len(s2))
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	output_len;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = 0;
	while (s[str_len])
		str_len++;
	i = 0;
	j = start;
	while (len - i > 0 && j <= str_len && s[j++])
		i++;
	output_len = i;
	sub = (char *)malloc((output_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	j = start;
	while (i < output_len)
		sub[i++] = s[j++];
	sub[i] = '\0';
	return ((char *)sub);
}

static char	**free_all(char **res, int w)
{
	while (w-- > 0)
		free(res[w]);
	free(res);
	return (NULL);
}

static int	count_words(char const *s1, char c)
{
	int	count;

	count = 0;
	while (*s1)
	{
		if (*s1 == '\0')
			return (count);
		else if (*s1 && *s1 == c)
		{
			while (*s1 && *s1 == c)
				(s1)++;
		}
		else if (*s1)
		{
			count++;
			while (*s1 && *s1 != c)
				s1++;
		}
	}
	return (count);
}

static char	**handle_null_malloc(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = ((char **)malloc((count_words(s, c) + 1) * sizeof(char *)));
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		w;
	char	**res;
	int		i;
	int		j;

	i = 0;
	res = handle_null_malloc(s, c);
	if (res == NULL)
		return (NULL);
	w = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = 0;
		while (s[i] && s[i] != c && ++j)
			i++;
		res[w++] = ft_substr(s, i - j, j);
		if (res[w - 1] == NULL)
			return (free_all(res, w - 1));
	}
	res[w] = 0;
	return (res);
}

void exit_print(char *msg)
{
    printf("%s", msg);
    exit(1);
}

int main(int ac, char *av[], char *env[])
{
    int id;

    id = fork();
    int i = 0;
    char *cmd;
    char **cmd1av =  ft_split(av[1], ' ');
    char *path;
    if (id == 0)
    {
        cmd = cmd1av[0];
        path = ft_strjoin("/bin/", cmd);
        if (access(path, F_OK) == 0)
            execve(path, cmd1av, NULL);
    }
    else
    {
        int status;
        // Wait for child process to finish
        wait(&status);
    }
}
