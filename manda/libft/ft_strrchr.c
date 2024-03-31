/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:33:41 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/05 22:33:42 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			last = ((char *)str + i);
		i++;
	}
	if (str[i] == (char)c)
		last = (((char *)str + i));
	return (last);
}
