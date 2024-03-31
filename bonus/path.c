#include "pipex.h"

int is_path(t_node	*command)
{
	return (command->cmd[0] == '/' || command->cmd[0] == '.');
}

char *check_env_path(char	*env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return env[i];
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
		if (access(path, X_OK))
			return path;
		free(path);
		i++;
	}
    return NULL;
}