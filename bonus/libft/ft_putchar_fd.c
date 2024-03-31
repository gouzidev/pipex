/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:09:11 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/10 22:03:18 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <fcntl.h>
// int main()
// {
// 	int fd = open("FILELeeeeeeeeeeeeeeeeeeeeeeeeeeee", O_CREAT | O_WRONLY);
// 	printf("fd ->   %i\n", fd);

// 	ft_putstr_fd("ggggg", fd);
// 	return (0);
// }