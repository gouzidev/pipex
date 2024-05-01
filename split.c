/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:33 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/27 22:20:48 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	len(char *s1)
{
	int	l;

	if (!s1)
		return (0);
	l = 0;
	while (s1[l])
		l++;
	return (l);
}

int	count_words(char const *s1, char *sep)
{
	int	count;

	count = 0;
	while (*s1)
	{
		if (*s1 == '\0')
			return (count);
		else if (*s1 && is_sep(*s1, sep))
		{
			while (*s1 && is_sep(*s1, sep))
				(s1)++;
		}
		else if (*s1)
		{
			count++;
			while (*s1 && !is_sep(*s1, sep))
				s1++;
		}
	}
	return (count);
}

char	**handle_null_malloc(char const *s, char *sep, t_node **gc)
{
	char	**res;

	if (!s)
		return (NULL);
	res = ((char **)gc_malloc(gc, (count_words(s, sep) + 1) * sizeof(char *)));
	return (res);
}

int is_sep(char c, char *sep)
{
	int i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char *sep, t_node **gc)
{
	int		w;
	char	**res;
	int		i;
	int		j;

	i = 0;
	res = handle_null_malloc(s, sep, gc);
	if (res == NULL)
		return (NULL);
	w = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], sep))
			i++;
		if (!s[i])
			break ;
		j = 0;
		while (s[i] && !is_sep(s[i], sep) && ++j)
			i++;
		res[w++] = ft_substr(s, i - j, j, gc);
	}
	res[w] = 0;
	return (res);
}
