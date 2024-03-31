/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:39:05 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/07 02:53:21 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*buf;

	len = 0;
	while (s1[len])
		len++;
	buf = malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		buf[i] = s1[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

// int main()
// {
// 	printf("ters   ->  %s\n", (strdup(NULL)));
// 	printf("mine   ->  %s\n", (ft_strdup(NULL)));
// }