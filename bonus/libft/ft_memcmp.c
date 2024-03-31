/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:09:32 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/07 02:26:34 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s2)[i] == ((unsigned char *)s1)[i] && n > 1)
	{
		i++;
		n--;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
