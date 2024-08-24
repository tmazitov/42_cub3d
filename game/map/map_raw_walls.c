/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_raw_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:23:46 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 19:31:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_point	wall_pos(int x, int y)
{
	t_point pos;

	pos.x = x * 64;
	pos.y = y * 64;
	return (pos);
}

int	add_direction_wall(t_map *map, int x, int y, t_map_raw_list *node)
{
	if (node->value[x] == '1' && is_moveable_area(map, x, y + 1))
	{
		if (!add_wall(wall_pos(x, y + 1), WALL, NORTH, map->walls))
			return (0);
	}
	if (node->value[x] == '1' && is_moveable_area(map, x, y - 1))
	{
		if (!add_wall(wall_pos(x, y), WALL, SOUTH, map->walls))
			return (0);
	}
	if (node->value[x] == '1' && is_moveable_area(map, x + 1, y))
	{
		if (!add_wall(wall_pos(x + 1, y), WALL, WEST, map->walls))
			return (0);
	}	
	if (node->value[x] == '1' && is_moveable_area(map, x - 1, y))
	{
		if (!add_wall(wall_pos(x, y), WALL, EAST, map->walls))
			return (0);
	}
	return (1);
}
