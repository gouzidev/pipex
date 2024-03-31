/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 22:48:51 by sgouzi            #+#    #+#             */
/*   Updated: 2023/10/31 16:27:47 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *)b)[i++] = (unsigned char)c;
	return (b);
}

// #include <stdio.h>
// int main()
// {
// 	char arr[] = "hello_world";
// 	ft_memset(arr, 99, 6);
// 	int i = 0;
// 	while (i < 12)
// 	{
// 		printf("%c", arr[i]);
// 		i++;
// 	}
// }