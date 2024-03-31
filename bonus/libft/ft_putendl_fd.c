/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:08:24 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/10 22:03:31 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// #include <stdio.h>
// int main()
// {
// 	int fd = open("new", O_CREAT | O_WRONLY);

// 	printf("fd of the file test.v  is   -> %i\n", fd);
// 	write(fd, "hello", 5);
// 	return (0);
// }