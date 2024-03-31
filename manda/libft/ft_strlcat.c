/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:34:54 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/12 16:07:59 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:34:46 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/05 22:34:46 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lsrc;
	size_t	ldst;
	size_t	i;
	size_t	j;

	lsrc = ft_strlen((char *)src);
	if (!dst && size == 0)
		return (size + lsrc);
	ldst = ft_strlen(dst);
	if (size <= ldst)
		return (size + lsrc);
	i = 0;
	j = ldst;
	while (i < size - ldst - 1 && src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (ldst + lsrc);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*dst;

// 	str = "hello";
// 	dst = NULL;
// 	strlcat(dst, str, 0);
// 	printf("ters %s\n", dst);
// 	ft_strlcat(dst, str, 0);
// 	printf("mine %s\n", dst);
// 	return (0);
// }
