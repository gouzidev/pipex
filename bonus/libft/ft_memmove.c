/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:37:58 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/14 14:14:41 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	s = (char *)src;
	d = (char *)dst;
	if (!s && !d)
		return (NULL);
	if (d < s)
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	return (dst);
}

// #include <stdio.h>
// int main()
// {
// memmove(NULL, "string", 0);
// ft_memmove(NULL, "string", 0);

// memmove("string", NULL, 5);
// ft_memmove("string", NULL, 5);

// printf("re  => %s\n", (char *)memmove(NULL, "d", 0));
// printf("re  => %s\n", (char *)ft_memmove(NULL, "d", 0));
// }
