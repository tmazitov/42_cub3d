/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bullets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:38:49 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 20:06:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int	player_add_bullets(t_player *player, int amount)
{
	int			hb_width;
	int			old_amount;
	t_inventory	*inv;

	old_amount = player->inventory->bullets;
	player->inventory->bullets += amount;
	player->update_count += 1;
	if (max_delimeter(old_amount) != max_delimeter(player->inventory->bullets))
	{
		inv = player->inventory;
		hb_width = inv->image->width - (INV_PADDING + INV_BORDER_SIZE) * 2
			- bullets_message_size(inv);
		if (!hb_new_image(inv->image->mlx, inv->health_bar, hb_width, 24))
			return (0);
	}
	return (1);
}

int	player_add_weapon(t_player *player, t_item_type type)
{
	t_item_collection	*player_items;
	int					counter;

	if (type != PISTOL)
		return (0);
	counter = 0;
	player_items = player->inventory->slots;
	while (player_items->items[counter])
	{
		if (player_items->items[counter]->type == type)
			return (0);
		counter++;
	}
	if (!item_collection_add_item(player_items, type, 1))
		return (0);
	return (1);
}
