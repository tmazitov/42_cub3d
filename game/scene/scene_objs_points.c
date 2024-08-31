/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objs_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 03:05:52 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 20:15:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	feel_objs_points(t_point_list *point, t_map_raw_list *raw_map)
{
	t_a_point	*new_point;
	int			x;
	int			y;

	y = 0;
	while (raw_map)
	{
		x = 0;
		while (raw_map->value[x])
		{
			if (raw_map->value[x] == '1' || \
				raw_map->value[x] == 'D')
			{
				new_point = make_a_point(x * 64, y * 64, NULL);
				if (!new_point \
					|| lst_add_point(point, new_point) != 0)
					return (0);
			}
			x++;
		}
		y++;
		raw_map = raw_map->next;
	}
	return (1);
}

void	set_active_objs_points(t_point_list *list, int x, int y, int value)
{
	t_point_node	*node;

	node = list->points;
	while (node)
	{
		if (node->point->x == x && node->point->y == y)
		{
			printf("door with coords : %d %d \n", x, y);
			node->point->is_active = value;
			return ;
		}
		node = node->next;
	}
}
