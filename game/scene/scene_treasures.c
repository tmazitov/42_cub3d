/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_treasures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 03:16:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 14:52:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	init_treasure_storage(t_treasure_storage *storage)
{
	storage->boxes = NULL;
	storage->items = NULL;
	storage->size = 0;
}

static int	count_of_treasures(t_map_raw_list *raw_map_item)
{
	int	counter;
	int	count;
	
	count = 0;
	while (raw_map_item)
	{
		counter = 0;
		while (raw_map_item->value[counter])
		{
			if (raw_map_item->value[counter] == 'B')
				count++;
			counter++;
		}
		raw_map_item = raw_map_item->next;
	}
	return (count);	
}


int	feel_treasure_storage(t_treasure_storage *storage, t_map_raw_list *raw_map)
{
	int	x;
	int	y;
	int treasure_count;
	int treasure_created;
	
	treasure_count = count_of_treasures(raw_map);
	if (treasure_count == 0)
		return (1);
	storage->boxes = malloc(sizeof(t_treasure *) * (treasure_count+1));
	storage->items = malloc(sizeof(t_item_collection *) * (treasure_count+1));
	if (!storage->items || !storage->boxes)
		return (0);
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
				storage->items[treasure_created] = make_item_collection(1);
				if (!storage->boxes[treasure_created] || !storage->items[treasure_created])
					return (0);
				if (!item_collection_add_item(storage->items[treasure_created], BULLET, random_int(7, 19)))
					return (0);
				printf("\t|__| Treasure with bullets added at (%d, %d)\n", x*64, y*64);
				printf("\t\t--> contain %d bullets\n", storage->items[treasure_created]->items[0]->amount);
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
		while (storage->boxes)
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