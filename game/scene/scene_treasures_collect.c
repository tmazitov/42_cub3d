/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_treasures_collect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:34:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 18:16:33 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	treasure_collect(t_treasure_storage *storage, t_treasure *box, t_player *player)
{
	int					treasure_index;
	int					counter;
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
	while (treasure_items->items[counter])
	{
		treasure_item = treasure_items->items[counter];
		if (treasure_item->type == BULLET)
			player_add_bullets(player, treasure_item->amount);
		counter++;
	}
	storage->items[treasure_index] = free_item_collection(treasure_items);
	return (1);
}