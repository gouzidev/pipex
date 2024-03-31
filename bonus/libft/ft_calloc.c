/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:18:35 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/05 23:18:36 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*buffer;
	size_t			nbytes;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	nbytes = count * size;
	buffer = malloc(nbytes);
	if (buffer == 0)
		return (0);
	while (i < nbytes)
		buffer[i++] = 0;
	return (buffer);
}
