/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:42 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/15 15:44:43 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst == NULL)
			ft_lstadd_front(lst, new);
		else
		{
			last = *lst;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}

// #include <stdio.h>
// int main()
// {
// 	t_list *head = NULL;
// 	t_list **hhead = &head;
// 	ft_lstadd_back(hhead, ft_lstnew("str1"));
// 	ft_lstadd_back(hhead, NULL);
// 	ft_lstadd_back(hhead, NULL);

// 	while (head)
// 	{
// 		printf("-> %s\n", (char *) head->content);
// 		head = head->next;
// 	}
// }
