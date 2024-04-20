#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = ((unsigned char *)s1);
	str2 = ((unsigned char *)s2);
	i = 0;
	if (n == 0)
		return (0);
	while (str2[i] != '\0' && str1[i] == str2[i] && n > 1)
	{
		i++;
		n--;
	}
	return (str1[i] - str2[i]);
}

int is_path(char	*cmd)
{
	int	i;
	if (cmd[0] == '/' || cmd[0] == '.')
		return 1;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return 1;
		i++;
	}
	return 0;
}

char *get_env_path(char	*env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return env[i] + 5;
		i++;
	}
	return (NULL);
}
char	*make_path(char	*path, char	*cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		perror("malloc");
	full_path = ft_strjoin(temp, cmd);
	if (full_path == NULL)
		perror("malloc");
	free(temp);
	return full_path;
}

char *find_cmd_path(char	*env_path, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_split(env_path, ':');
	if (paths == NULL)
		perror("malloc");
	i = 0;
	while (paths[i])
	{
		path = make_path(paths[i], cmd);
		if (path == NULL)
			perror("malloc");
		if (access(path, X_OK) == 0)
			return path;
		free(path);
		i++;
	}
    return NULL;
}