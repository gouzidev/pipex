#include "pipex.h"

int is_path(char	*cmd)
{
	return (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'));
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

char	*make_path(char	*path, char	*cmd, t_node **gc)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(path, "/", gc);
	full_path = ft_strjoin(temp, cmd, gc);
	return full_path;
}

char *find_cmd_path(char	*env_path, char *cmd, t_node **gc)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_split(env_path, ':', gc);
	if (paths == NULL)
		perror("malloc");
	i = 0;
	while (paths[i])
	{
		path = make_path(paths[i], cmd, gc);
		if (path == NULL)
			perror("malloc");
		if (access(path, X_OK) == 0)
			return path;
		i++;
	}
    return NULL;
}