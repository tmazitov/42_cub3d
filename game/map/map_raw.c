/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:48:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 16:57:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_neighbors(t_map *map, int x, int y)
{
	char	top;
	char	bot;
	char	left;
	char	right;

	top = get_raw_value(map, x, y - 1);
	bot = get_raw_value(map, x, y + 1);
	left = get_raw_value(map, x - 1, y);
	right = get_raw_value(map, x + 1, y);
	if (top == 0 || bot == 0 || right == 0 || left == 0)
		return (0);
	return (top != ' ' && bot != ' ' && left != ' ' && right != ' ');
}

int	add_direction_wall(t_map *map, int x, int y, t_map_raw_list *node)
{
	int		status;
	t_point	pos;

	if (node->value[x] != '1')
		return (1);
	status = 1;
	pos.x = x * 64;
	pos.y = y * 64;
	if (node->value[x] == '1' && is_moveable_area(map, x, y + 1))
		status = add_wall(pos, WALL, NORTH, map->walls);
	else if (node->value[x] == '1' && is_moveable_area(map, x, y - 1))
		status = add_wall(pos, WALL, SOUTH, map->walls);
	else if (node->value[x] == '1' && is_moveable_area(map, x + 1, y))
		status = add_wall(pos, WALL, WEST, map->walls);
	else if (node->value[x] == '1' && is_moveable_area(map, x - 1, y))
		status = add_wall(pos, WALL, EAST, map->walls);
	return (status);
}

int	convert_raw_to_objs(t_map *map)
{
	int				y;
	int				x;
	t_map_raw_list	*node;

	y = 0;
	node = map->raw;
	while (node && y != map->height)
	{
		x = 0;
		while (node->value[x])
		{
			if (!setup_player_position(map, node->value[x], x, y))
				return (0);
			if (node->value[x] != '1' && node->value[x] != ' '
				&& !check_neighbors(map, x, y))
				return (print_error("invalid map"), 0);
			if (!add_direction_wall(map, x, y, node))
				return (print_error("invalid map aa"), 0);
			x++;
		}
		y++;
		node = node->next;
	}
	return (1);
}

void	*free_map_raw_item(t_map_raw_list *item)
{
	if (!item)
		return (NULL);
	if (item->next)
		free_map_raw_item(item->next);
	if (item->value)
		free(item->value);
	free(item);
	return (NULL);
}

int	count_of_objs(t_map_raw_list *item, char obj_char)
{
	int	counter;
	int	count;

	count = 0;
	while (item)
	{
		counter = 0;
		while (item->value[counter])
		{
			if (item->value[counter] == obj_char)
				count++;
			counter++;
		}
		item = item->next;
	}
	return (count);
}
