/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:27:59 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 18:39:43 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[len(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *str, char *buff, t_node **gc)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!str)
	{
		str = (char *)gc_malloc(gc, 1 * sizeof(char));
		str[0] = '\0';
	}
	if (!buff)
		return (NULL);
	res = gc_malloc(gc, sizeof(char) * ((len(str) + len(buff)) + 1));
	if (res == NULL)
		(gc_clear(gc), exit(1));
	i = -1;
	j = 0;
	if (str)
		while (str[++i] != '\0')
			res[i] = str[i];
	while (buff[j] != '\0')
		res[i++] = buff[j++];
	res[len(str) + len(buff)] = '\0';
	return (res);
}

char	*ft_get_line(char *str, t_node **gc)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	line = (char *)gc_malloc(gc, sizeof(char) * (i + 1));
	if (!line)
		(gc_clear(gc), exit(1));
	i = -1;
	while (++i >= 0 && str[i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_rest(char *str, t_node **gc)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	buff = (char *)gc_malloc(gc, sizeof(char) * (len(str) - i + 1));
	if (!buff)
		(gc_clear(gc), perror("malloc"), exit(1));
	i++;
	j = 0;
	while (str[i])
		buff[j++] = str[i++];
	buff[j] = '\0';
	return (buff);
}

char	*get_next_line(int fd, t_node **gc)
{
	char		*line;
	static char	*str;
	char		*buff;
	int			bytes;

	buff = gc_malloc(gc, ((size_t)1 + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, 1);
		if (bytes == -1)
			return (gc_clear(gc), NULL);
		buff[bytes] = '\0';
		str = ft_strjoin_gnl(str, buff, gc);
	}
	if (!str)
		return (gc_clear(gc), NULL);
	line = ft_get_line(str, gc);
	str = get_rest(str, gc);
	return (line);
}
