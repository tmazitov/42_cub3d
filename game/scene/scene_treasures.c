/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_treasures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 03:16:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/24 16:35:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	init_treasure_storage(t_treasure_storage *storage)
{
	storage->boxes = NULL;
	storage->items = NULL;
	storage->size = 0;
}


int	feel_treasure_storage(t_treasure_storage *storage, t_map_raw_list *raw_map)
{
	int	x;
	int	y;
	int treasure_count;
	int treasure_created;
	int	pistol_count;
	int	bullets_count;
	int	total_items_count;
	

	treasure_count = count_of_objs(raw_map, 'B');
	if (treasure_count == 0)
		return (1);
	storage->boxes = ft_calloc(treasure_count+1, sizeof(t_treasure *));
	storage->items = ft_calloc(treasure_count+1, sizeof(t_item_collection *));
	if (!storage->items || !storage->boxes)
		return (0);
	int counter = 0;
	while(counter <= treasure_count)
	{
		storage->items[counter] = NULL;
		storage->boxes[counter] = NULL;
		counter++;
	}
	y = 0;
	treasure_created = 0;
	while (raw_map && treasure_created < treasure_count)
	{
		x = 0;
		while (raw_map->value[x])
		{
			if (raw_map->value[x] == 'B')
			{
				storage->boxes[treasure_created] = make_treasure(x*64, y*64);
				pistol_count = random_int(-5, 1);
				bullets_count = random_int(7, 19);
				total_items_count = !!pistol_count + !!bullets_count;
				storage->items[treasure_created] = make_item_collection(total_items_count);
				if (!storage->boxes[treasure_created] || !storage->items[treasure_created])
					return (0);
				if (pistol_count > 0 && !item_collection_add_item(storage->items[treasure_created], PISTOL, 1))
					return (0);
				if (!item_collection_add_item(storage->items[treasure_created], BULLET, random_int(7, 19)))
					return (0);
				printf("\t|__| Treasure box added at (%d, %d)\n", x*64, y*64);
				item_collection_print(storage->items[treasure_created]);
				treasure_created++;
			}
			x++;
		}
		y++;
		raw_map = raw_map->next;
	}
	storage->boxes[treasure_created] = NULL;
	storage->items[treasure_created] = NULL;
	return (1);
}

t_treasure_storage	*make_treasure_storage(t_map_raw_list *raw_map)
{
	t_treasure_storage *storage;

	storage = (t_treasure_storage *)malloc(sizeof(t_treasure_storage));
	if (!storage)
		return (NULL);
	init_treasure_storage(storage);
	if (!feel_treasure_storage(storage, raw_map))
		return (free_treasure_storage(storage));
	return (storage);
}


void	*free_treasure_storage(t_treasure_storage *storage)
{
	int counter;

	if (!storage)
		return (NULL);
	if (storage->boxes)
	{
		counter = 0;
		while (storage->boxes[counter])
		{
			if (storage->boxes[counter])
				free_treasure(storage->boxes[counter]);
			counter++;
		}
		free(storage->boxes);
	}
	if (storage->boxes)
	{
		counter = 0;
		while (storage->items[counter])
		{
			if (storage->items[counter])
				free_item_collection(storage->items[counter]);
			counter++;
		}
		free(storage->items);
	}
	free(storage);
	return (NULL);
}