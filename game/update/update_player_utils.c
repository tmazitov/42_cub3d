/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:08:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 17:25:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

void	player_collect(t_game *game, t_player *player)
{
	t_treasure_storage	*storage;
	int					counter;
	t_point				*player_pos;
	t_point				*box_pos;
	int					check;

	if (!player->pressed_buttons[6])
		return ;
	player_pos = player->pos;
	storage = game->scene->treasures;
	counter = 0;
	while (storage->boxes[counter])
	{
		box_pos = storage->boxes[counter]->center;
		check = point_distance(*player_pos, *box_pos) <= COLLECT_DISTANCE;
		if (check && treasure_collect(storage, storage->boxes[counter], player))
			break ;
		counter++;
	}
}

void	player_inventory_update(t_game *game)
{
	t_inv_images	images;
	t_sprite_node	*sprite;
	t_player		*pl;

	images.bullet_image = NULL;
	images.slot_image = NULL;
	images.active_slot_image = NULL;
	images.pistol_image = NULL;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_SLOT");
	if (sprite && sprite->image)
		images.slot_image = sprite->image;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_SLOT_ACTIVE");
	if (sprite && sprite->image)
		images.active_slot_image = sprite->image;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_BULLET");
	if (sprite && sprite->image)
		images.bullet_image = sprite->image;
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_ICON");
	if (sprite && sprite->image)
		images.pistol_image = sprite->image;
	pl = game->scene->player;
	inv_update_image(pl->inventory, pl->update_count, images, game->writer);
}
