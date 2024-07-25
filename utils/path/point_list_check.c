/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_list_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:50:13 by tmazitov          #+#    #+#             */
/*   Updated: 2023/12/10 21:57:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

t_a_point	*lst_check_by_coord(t_point_list *list, int x, int y)
{
	t_point_node	*node;

	node = list->points;
	while (node && node->point)
	{
		if (node->point->x == x && node->point->y == y)
			return (node->point);
		node = node->next;
	}
	return (NULL);
}
