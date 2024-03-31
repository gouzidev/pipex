/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:39:50 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/06 14:41:59 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (((char *)str + i));
		i++;
	}
	if (str[i] == (char)c)
		return (((char *)str + i));
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	printf("ters   ->  %s\n", strchr("STRING", 'S'));
// 	printf("mine   ->  %s\n", ft_strchr("STRING", 'S'));

// 	printf("ters   ->  %s\n", strchr("STRING\0after", 0) + 1);
// 	printf("mine   ->  %s\n", ft_strchr("STRING\0after", 0) + 1);

// 	printf("ters   ->  %s\n", strchr("STRING", 0));
// 	printf("mine   ->  %s\n", ft_strchr("STRING", 0));

// 	printf("ters   ->  %s\n", strchr(NULL, 'c'));
// 	printf("mine   ->  %s\n", ft_strchr(NULL, 'c'));
// }