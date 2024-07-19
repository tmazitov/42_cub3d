/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_treasures_collect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:34:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 00:10:23 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	treasure_collect(t_treasure_storage *storage, t_treasure *box, t_player *player)
{
	int					treasure_index;
	int					counter;
	int					is_added;
	int					added_count;
	t_item				*treasure_item;
	t_item_collection	*treasure_items;

	if (!storage || !box || !player)
		return (0);
	treasure_index = 0;
	while (storage->boxes[treasure_index] && \
		storage->boxes[treasure_index] != box)
		treasure_index++;
	if (storage->boxes[treasure_index] == NULL)
		return (0);
	treasure_items = storage->items[treasure_index];
	if (treasure_items == NULL)
		return (0);
	counter = 0;
	added_count = 0;
	is_added = 0;
	while (treasure_items->items[counter])
	{
		treasure_item = treasure_items->items[counter];
		if (treasure_item->type == BULLET && player_add_bullets(player, treasure_item->amount))
			is_added = 1;
		if (treasure_item->type == PISTOL && player_add_weapon(player, treasure_item->type))
			is_added = 1;
		if (is_added)
		{
			treasure_items->items[counter] = free_item(treasure_item);
			added_count += 1;
			is_added = 0;
		}
		counter++;
	}
	if (added_count == counter)
		storage->items[treasure_index] = free_item_collection(treasure_items);
	return (1);
}