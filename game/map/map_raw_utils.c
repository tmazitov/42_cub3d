/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_raw_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:43:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 16:56:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_map_raw_list	*get_last_raw_item(t_map_raw_list *item)
{
	if (item->next)
		return (get_last_raw_item(item->next));
	return (item);
}

int	add_map_raw_item(t_map *map, char *value)
{
	t_map_raw_list	*new_item;

	new_item = malloc(sizeof(t_map_raw_list));
	if (!new_item)
		return (0);
	new_item->value = ft_strdup(value);
	if (!new_item->value)
		return (free(new_item), 0);
	new_item->next = NULL;
	new_item->prev = NULL;
	if (!map->raw)
		map->raw = new_item;
	else
	{
		new_item->prev = get_last_raw_item(map->raw);
		get_last_raw_item(map->raw)->next = new_item;
	}
	return (1);
}

char	get_raw_value(t_map *map, int x, int y)
{
	t_map_raw_list	*node;
	int				i;

	node = map->raw;
	i = 0;
	if (y >= map->height)
		return ('\0');
	while (i < y && y < map->height)
	{
		if (!node)
			return (0);
		node = node->next;
		i++;
	}
	if (node && x >= (int)ft_strlen(node->value))
		return ('\0');
	if (!node || i != y || y < 0 || x < 0)
		return ('\0');
	return (node->value[x]);
}

int	is_moveable_area(t_map *map, int x, int y)
{
	char	symbol;
	char	*moveable_symbols;
	int		counter;

	moveable_symbols = "0BZNEWS";
	symbol = get_raw_value(map, x, y);
	counter = 0;
	while (moveable_symbols[counter])
	{
		if (symbol == moveable_symbols[counter])
			return (1);
		counter++;
	}
	return (0);
}

int	setup_player_position(t_map *map, char ch, int x, int y)
{
	if (ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W')
		return (1);
	if (map->player_start)
		return (print_error("dup player position"), 1);
	map->player_start = make_point(x * 64, y * 64);
	if (!map->player_start)
		return (1);
	if (ch == 'N')
		map->player_direction = NORTH;
	else if (ch == 'S')
		map->player_direction = SOUTH;
	else if (ch == 'W')
		map->player_direction = WEST;
	else
		map->player_direction = EAST;
	return (1);
}
