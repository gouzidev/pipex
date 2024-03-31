/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:34:36 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/07 02:33:25 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lsrc;

	i = 0;
	lsrc = ft_strlen(src);
	if (size == 0)
		return (lsrc);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lsrc);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	// printf("%zu \n", ft_strlcpy(NULL, "dst", 1));
// 	printf("%zu \n", ft_strlcpy("dst", NULL, 3));
// }