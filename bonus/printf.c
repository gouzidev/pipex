/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:21:47 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 18:09:32 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr(char *s, int *i)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*i += 6;
		return ;
	}
	while (*s)
	{
		write(1, s, 1);
		(*i)++;
		s++;
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	v;
	int		i;

	va_start(v, s);
	i = 0;
	while (*s)
	{
		if (s && *s == '%')
		{
			if (*(s + 1) == 's')
			{
				s++;
				if (*s == 's')
					ft_putstr(va_arg(v, char *), &i);
			}
		}
		else if (s && *s)
			(write(1, s, 1), ++i);
		s++;
	}
	va_end(v);
	return (i);
}
