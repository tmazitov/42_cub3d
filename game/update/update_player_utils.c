/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:08:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 20:09:08 by kshamsid         ###   ########.fr       */
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

void	player_door_update_utils(t_line *door_check_pos,
	t_player *player, float dx, float dy)
{
	door_check_pos->start = *player->pos;
	door_check_pos->end = *player->pos;
	door_check_pos->end.x -= dx;
	door_check_pos->end.y -= dy;
}

void	player_door_update(t_game *game)
{
	t_player	*player;
	t_line		door_check_pos;
	float		player_angle;
	float		dx;
	float		dy;

	player_angle = game->scene->minimap->player_rotation;
	dx = 50 * cosf(player_angle * M_PI / 180.0f);
	dy = 50 * sinf(player_angle * M_PI / 180.0f);
	player = game->scene->player;
	player_door_update_utils(&door_check_pos, player, dx, dy);
	if (!player->pressed_buttons[6])
		return ;
	if (get_array_map_value(door_check_pos, game) == 'D')
	{
		door_check_pos.end.x /= 64;
		door_check_pos.end.y /= 64;
		door_check_pos.end.x = (int)((door_check_pos.end.x
					- fmod(door_check_pos.end.x, 1)));
		door_check_pos.end.y = (int)((door_check_pos.end.y
					- fmod(door_check_pos.end.y, 1)));
		game->scene->map->map_double_array[(int)door_check_pos
			.end.y][(int)door_check_pos.end.x] = '0';
	}
}
