/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:07:11 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/17 22:52:37 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	prepare_and_push_to_a(t_stack **a, t_stack **b)
{
	t_stack	*cheapest;

	give_index(*a, true);
	give_index(*b, true);
	set_b_targets_in_a(*a, *b);
	calc_push_cost(*a, *b);
	cheapest = get_cheapest(*b);
	if (cheapest->below_median)
		handle_cheapest_below_med(a, b, cheapest);
	else if (!cheapest->below_median)
		handle_cheapest_above_med(a, b, cheapest);
	push_from_to(a, b, "pa\n");
}

void	give_index(t_stack *head, bool set_target_null)
{
	t_stack	*curr;
	int		i;
	int		median;

	if (!head)
		return ;
	median = get_size(head) / 2;
	curr = head;
	i = 0;
	while (curr)
	{
		if (set_target_null == true)
			curr->target = NULL;
		curr->i = i++;
		curr->push_cost = -1;
		curr->below_median = false;
		if (curr->i > median)
			curr->below_median = true;
		curr = curr->next;
	}
}

int	is_stack_sorted(t_stack *head)
{
	while (head && head->next)
	{
		if (head->n > head->next->n)
			return (0);
		head = head->next;
	}
	return (1);
}

void	sort_more(t_stack **a, t_stack **b)
{
	t_stack	*smallest;

	while (get_size(*a) > 3)
		prepare_and_push_to_b(a, b);
	sort_less_than_four(a);
	while (*b)
		prepare_and_push_to_a(a, b);
	give_index(*a, true);
	smallest = get_min(*a);
	if (smallest->below_median)
	{
		while (*a != smallest)
			reverse_rotate_stack(a, "rra\n", true);
	}
	else
	{
		while (*a != smallest)
			rotate_stack(a, "ra\n", true);
	}
}
