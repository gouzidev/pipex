/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:11:34 by sgouzi            #+#    #+#             */
/*   Updated: 2023/11/09 19:47:56 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;

	new_lst = NULL;
	new_node = NULL;
	if (lst)
	{
		while (lst)
		{
			new_node = ft_lstnew((*f)(lst->content));
			if (new_node == NULL)
			{
				ft_lstclear(&new_lst, del);
				new_lst = NULL;
				return (NULL);
			}
			ft_lstadd_back(&new_lst, new_node);
			lst = lst->next;
		}
	}
	return (new_lst);
}
