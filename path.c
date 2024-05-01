/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:25 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/27 22:20:48 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_path(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *env_path, char *cmd, t_node **gc)
{
	char	**paths;
	int		i;
	char	*full_path;
	char	*temp;

	if (ft_strncmp(cmd, ".", 1) == 0)
		return (cmd);
	paths = ft_split(env_path, ":", gc);
	if (paths == NULL)
		perror("malloc");
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/", gc);
		if (temp == NULL)
			perror("malloc");
		full_path = ft_strjoin(temp, cmd, gc);
		if (full_path == NULL)
			perror("malloc");
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
