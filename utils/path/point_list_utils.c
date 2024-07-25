/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:39:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 03:48:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

void	lst_rem_point(t_point_list *list, t_a_point *point)
{
	t_point_node	*node;
	t_point_node	*prev;

	prev = NULL;
	node = list->points;
	while (node)
	{
		if (node->point == point)
		{
			if (prev)
				prev->next = node->next;
			else if (!prev && list->points == node && !node->next)
				list->points = NULL;
			else if (!prev && list->points == node)
				list->points = node->next;
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
	return ;
}

t_a_point	*lst_get_min_point(t_point_list *list)
{
	int				min;
	t_point_node	*node;
	t_a_point		*point;

	if (!list || !list->points)
		return (NULL);
	node = list->points;
	point = node->point;
	min = node->point->weight;
	while (node)
	{
		if (node->point->weight < min)
		{
			min = node->point->weight;
			point = node->point;
		}
		node = node->next;
	}
	return (point);
}

int	lst_length(t_point_list *list)
{
	int				length;
	t_point_node	*node;

	length = 0;
	node = list->points;
	while (node)
	{
		length++;
		node = node->next;
	}
	return (length);
}

t_point_node	*lst_get_item(t_point_list *list, int index)
{
	t_point_node	*iter;
	int				counter;

	counter = 0;
	iter = list->points;
	while (iter && iter->next && counter++ != index - 1)
		iter = iter->next;
	return (iter);
}

t_point_list	*lst_reverse(t_point_list *list)
{
	t_point_list	*result;
	t_point_node	*iter;
	t_a_point		*p;
	int				length;

	if (!list)
		return (NULL);
	result = make_point_list();
	if (!result)
		return (NULL);
	length = lst_length(list);
	while (1)
	{
		iter = lst_get_item(list, length--);
		p = iter->point;
		if (lst_add_point(result, make_a_point(p->x, p->y, NULL)))
			return (free_point_list(result));
		if (iter == list->points)
			break ;
	}
	return (result);
}
