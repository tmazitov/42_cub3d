/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_treasures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 03:16:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/28 20:10:06 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_treasure_storage	*make_treasure_storage(t_map_raw_list *raw_map)
{
	t_treasure_storage	*storage;

	storage = (t_treasure_storage *)malloc(sizeof(t_treasure_storage));
	if (!storage)
		return (NULL);
	storage->boxes = NULL;
	storage->items = NULL;
	storage->size = 0;
	if (!feel_treasure_storage(storage, raw_map))
		return (free_treasure_storage(storage));
	return (storage);
}

void	*free_treasure_storage(t_treasure_storage *storage)
{
	int	counter;

	if (!storage)
		return (NULL);
	counter = 0;
	while (storage->boxes && counter < storage->size)
	{
		free_treasure(storage->boxes[counter]);
		counter++;
	}
	if (storage->boxes)
		free(storage->boxes);
	counter = 0;
	while (storage->items && counter < storage->size)
	{
		free_item_collection(storage->items[counter]);
		counter++;
	}
	if (storage->items)
		free(storage->items);
	return (free(storage), NULL);
}

int	prepare_treasure_storage(t_treasure_storage *storage,
								t_map_raw_list *raw_map)
{
	int	bullet_box_amount;
	int	total_amount;
	int	counter;

	counter = 0;
	bullet_box_amount = count_of_objs(raw_map, 'B');
	total_amount = bullet_box_amount;
	if (total_amount == 0)
		return (2);
	storage->boxes = ft_calloc(total_amount + 1, sizeof(t_treasure *));
	if (!storage->boxes)
		return (0);
	storage->items = ft_calloc(total_amount + 1, sizeof(t_item_collection *));
	if (!storage->items)
		return (0);
	while (counter <= total_amount)
	{
		storage->items[counter] = NULL;
		storage->boxes[counter++] = NULL;
	}
	storage->size = total_amount;
	storage->boxes[total_amount - 1] = NULL;
	storage->items[total_amount - 1] = NULL;
	return (1);
}

int	create_bullet_box(t_treasure_storage *storage, int x, int y, int index)
{
	storage->boxes[index] = make_treasure(x * 64, y * 64);
	if (!storage->boxes[index])
		return (0);
	storage->items[index] = make_item_collection(1);
	if (!storage->boxes[index] || !storage->items[index])
		return (0);
	if (!item_collection_add_item(storage->items[index], BULLET, random_int(7,
				19)))
		return (0);
	return (1);
}

int	feel_treasure_storage(t_treasure_storage *storage, t_map_raw_list *raw_map)
{
	int	x;
	int	y;
	int	created_count;
	int	is_ready;

	is_ready = prepare_treasure_storage(storage, raw_map);
	if (is_ready == 0 || is_ready == 2)
		return (is_ready != 0);
	y = 0;
	created_count = 0;
	while (raw_map && created_count < storage->size)
	{
		x = 0;
		while (raw_map->value[x])
		{
			if (raw_map->value[x] == 'B' && !create_bullet_box(storage, x, y,
					created_count))
				return (0);
			if (raw_map->value[x++] == 'B')
				created_count++;
		}
		y++;
		raw_map = raw_map->next;
	}
	return (1);
}
