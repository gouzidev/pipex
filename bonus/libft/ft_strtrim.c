/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:35:19 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/05 22:31:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	helper(size_t *i, char const *set, char const *s1, size_t *start)
{
	while (s1[*i])
	{
		if (!in_set(s1[*i], set))
			break ;
		(*i)++;
	}
	*start = *i;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*buff;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	helper(&i, set, s1, &start);
	end = ft_strlen(s1);
	while (end - 1 > start)
	{
		if (!in_set(s1[end - 1], set))
			break ;
		end--;
	}
	i = -1;
	buff = malloc((end - start + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	while (start + (++i) < end)
		buff[i] = s1[start + i];
	buff[i] = '\0';
	return (buff);
}
