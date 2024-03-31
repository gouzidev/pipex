/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:45:08 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/15 15:52:18 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	(*del)(lst->content);
	free(lst);
}

// void delete_node(void *ptr)
// {
// 	free(ptr);
// }
// #include <stdio.h>
// int main()
// {
// 	char *str1 = ft_strdup("Apple");
// 	char *str2 = ft_strdup("ourika");

// 	t_list *node1 = ft_lstnew(str1);
// 	t_list *node2 = ft_lstnew(str2);
// 	ft_lstdelone(node1, delete_node);
// 	node1->next = node2;
// 	printf("->  %s\n", node1->content);
// 	printf("->  %s\n", node2->content);
// }
