/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:48:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/09/01 00:28:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_neighbors(t_map *map, int x, int y)
{
	char	neighbor[4];
	char	corner[4];

	corner[0] = get_raw_value(map, x - 1, y - 1);
	corner[1] = get_raw_value(map, x + 1, y - 1);
	corner[2] = get_raw_value(map, x + 1, y + 1);
	corner[3] = get_raw_value(map, x - 1, y + 1);
	neighbor[0] = get_raw_value(map, x, y - 1);
	neighbor[1] = get_raw_value(map, x, y + 1);
	neighbor[2] = get_raw_value(map, x - 1, y);
	neighbor[3] = get_raw_value(map, x + 1, y);
	if (neighbor[0] == 0 || neighbor[1] == 0
		|| neighbor[2] == 0 || neighbor[3] == 0
		|| corner[0] == 0 || corner[1] == 0
		|| corner[2] == 0 || corner[3] == 0)
		return (0);
	return (neighbor[0] != ' ' && neighbor[1] != ' '
		&& neighbor[2] != ' ' && neighbor[3] != ' '
		&& corner[0] != ' ' && corner[1] != ' '
		&& corner[2] != ' ' && corner[3] != ' ');
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
			if (!is_allowed_char(node->value[x])
				|| !setup_player_position(map, node->value[x], x, y))
				return (print_error("invalid map char"), 0);
			if (node->value[x] != '1' && node->value[x] != ' '
				&& !check_neighbors(map, x, y))
				return (print_error("invalid map"), 0);
			if (!add_direction_wall(map, x, y, node))
				return (print_error("invalid map"), 0);
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
