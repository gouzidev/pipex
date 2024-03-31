/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:50 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/15 15:44:51 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// #include <stdio.h>
// int main()
// {
// 	t_list *head = NULL;
// 	ft_lstadd_front(NULL, NULL);

// 	while (head)
// 	{
// 		printf("-> %s\n", (char *) head->content);
// 		head = head->next;
// 	}
// }
