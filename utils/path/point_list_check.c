/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_list_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:50:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 23:55:38 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

t_a_point	*lst_check_by_coord(t_point_list *list, int x, int y)
{
	t_point_node	*node;

	node = list->points;
	while (node && node->point)
	{
		if (node->point->x == x && node->point->y == y
			&& node->point->is_active)
			return (node->point);
		node = node->next;
	}
	return (NULL);
}
