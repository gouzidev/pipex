/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:36:53 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/05 22:37:13 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
