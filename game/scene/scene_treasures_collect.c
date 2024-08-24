/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_treasures_collect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:34:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 16:09:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <pthread.h>

static int	get_treasure_box_index(t_treasure_storage *storage, t_treasure *box)
{
	int	index;

	index = 0;
	while (storage->boxes[index] && \
		storage->boxes[index] != box)
		index++;
	if (storage->boxes[index] == NULL)
		return (-1);
	return (index);
}

static void	play_collect_sound(void)
{
	pthread_t	sound_thread;

	pthread_create(&sound_thread, NULL, shoot_sound_func, \
		"cub3d_gear_pickup_sound.wav");
	pthread_detach(sound_thread);
	return ;
}

static int	collect_treasure_items(t_item_collection *treasure, \
	t_player *player)
{
	t_item				*item;
	int					counter;
	int					is_added;
	int					collected_count;

	counter = 0;
	collected_count = 0;
	is_added = 0;
	while (treasure->items[counter])
	{
		item = treasure->items[counter];
		if (item->type == BULLET && player_add_bullets(player, item->amount))
			is_added = 1;
		if (is_added)
		{
			treasure->items[counter] = free_item(item);
			collected_count += 1;
			is_added = 0;
		}
		counter++;
	}
	if (collected_count != 0)
		play_collect_sound();
	return (collected_count);
}

int	treasure_collect(t_treasure_storage *storage, \
	t_treasure *box, t_player *player)
{
	int					treasure_index;
	t_item_collection	*treasure_items;
	int					collected_count;

	if (!storage || !box || !player)
		return (0);
	treasure_index = get_treasure_box_index(storage, box);
	if (treasure_index == -1)
		return (0);
	treasure_items = storage->items[treasure_index];
	if (treasure_items == NULL)
		return (0);
	collected_count = collect_treasure_items(treasure_items, player);
	if (!collected_count)
		return (0);
	if (collected_count == treasure_items->size)
		storage->items[treasure_index] = free_item_collection(treasure_items);
	return (1);
}
