/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:33 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 18:40:21 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	len(char *s1)
{
	int	l;

	l = 0;
	while (s1[l])
		l++;
	return (l);
}

int	count_words(char const *s1, char c)
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

char	**handle_null_malloc(char const *s, char c, t_node **gc)
{
	char	**res;

	if (!s)
		return (NULL);
	res = ((char **)gc_malloc(gc, (count_words(s, c) + 1) * sizeof(char *)));
	return (res);
}

char	**ft_split(char const *s, char c, t_node **gc)
{
	int		w;
	char	**res;
	int		i;
	int		j;

	i = 0;
	res = handle_null_malloc(s, c, gc);
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
		res[w++] = ft_substr(s, i - j, j, gc);
	}
	res[w] = 0;
	return (res);
}
