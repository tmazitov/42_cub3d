/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:48:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/04 15:33:09 by tmazitov         ###   ########.fr       */
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

static char	get_raw_value(t_map *map, int x, int y)
{
	t_map_raw_list	*node;
	int				i;

	node = map->raw;
	i = 0;
	while (i < y && y < map->height)
	{
		if (!node)
			return (0);
		node = node->next;
		i++;
	}
	if (!node)
		return (0);
	if (x < 0)
		return (node->value[0]);
	return (node->value[x]);
}

int convert_raw_to_objs(t_map *map)
{
	int		y;
	int 	status;
	int		x;
	t_map_raw_list	*node;

	y = 0;
	node = map->raw;
	status = 1;
	node = map->raw;
	while(node && y != map->height)
	{
		x = 0;
		while (node->value[x] && node->value[x] == ' ')
			x++;
		if (!node->value[x])
			return (0);
		while (node->value[x])
		{
			if (node->value[x] == '1' && get_raw_value(map, x, y + 1) == '0')
				status = add_wall((x)*64, (y + 1)*64, WALL, NORTH, map->walls);
			if (!status)
				return (0);
			if (node->value[x] == '1' && get_raw_value(map, x, y - 1) == '0')
				status = add_wall((x)*64, (y)*64, WALL, SOUTH, map->walls);
			if (!status)
				return (0);
			if (node->value[x] == '1' && get_raw_value(map, x + 1, y) == '0')
				status = add_wall((x + 1)*64, (y)*64, WALL, WEST, map->walls);
			if (!status)
				return (0);
			if (node->value[x] == '1' && get_raw_value(map, x - 1, y) == '0')
				status = add_wall((x)*64 , (y)*64, WALL, EAST, map->walls);
			if (!status)
				return (0);
			x++;
		}
		y++;
		node = node->next;
	}
	return (1);
}



void *free_map_raw_item(t_map_raw_list *item)
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