/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:45:00 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/15 15:45:01 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (lst && *lst && del)
	{
		while (*lst)
		{
			next = (*lst)->next;
			(*del)((*lst)->content);
			free(*lst);
			*lst = next;
		}
	}
}

// void del(void *ptr)
// {
// 	free(ptr);
// }

// int main()
// {
// 	char *str0 = ft_strdup("node0");
// 	char *str1 = ft_strdup("node1");
// 	char *str2 = ft_strdup("node2");
// 	char *str3 = ft_strdup("node3");
// 	t_list *head = ft_lstnew(str0);
// 	ft_lstadd_back(&head, ft_lstnew(str1));
// 	ft_lstadd_back(&head, ft_lstnew(str2));
// 	ft_lstadd_back(&head, ft_lstnew(str3));
// 	ft_lstclear(&head, del);
// 	printf("1\n");
// }
