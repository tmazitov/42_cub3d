/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/22 15:32:42 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static t_line	*check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line			*wall_line;
	t_wall_node		*node;
	t_point			intersect_point;
	int				is_intersect;

	node = game->scene->map->walls->start;
	while(node)
	{
		wall_line = wall_to_line(node->wall);
		if (!wall_line)
			return (NULL);
		is_intersect = check_intersection(player_path, wall_line, &intersect_point);
		if (is_intersect)
		{
			line_update_by_points(player_path, player_path->start, intersect_point);
			return (wall_line);
		}
	 	free_line(wall_line);
		node = node->next;
	}
	return (NULL);
}

static void	update_player_vector(t_vector *move_vector, t_line *player_path, t_line *wall_line)
{
	t_line	*wall_perpendicular;

	wall_perpendicular = line_perpendicular(wall_line, player_path->start);
	if (!wall_perpendicular)
		return ;
	move_vector->x = - (wall_perpendicular->B + player_path->B) * -1;
	move_vector->y = (wall_perpendicular->A + player_path->A) * -1;
}

// Check if player can move in the direction of move_vector
static void	player_intersect_handler(t_game *game, t_vector *move_vector)
{
	t_line			*player_path;
	t_line			*inter_wall;
	float			posX;
	float			posY;

	if (!move_vector)
		return ;
	posX = game->scene->player->pos->x;
	posY = game->scene->player->pos->y;
	player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	if (!player_path)
		return ;
	inter_wall = check_wall_intersection(player_path, game);
	if (!inter_wall)
	{
		free_line(player_path);
		return ;
	}
	update_player_vector(move_vector, player_path, inter_wall);
	free_line(player_path);
	free_line(inter_wall);
}

static void	player_collect(t_game *game, t_player *player)
{
	t_treasure_storage	*storage;
	int					counter;
	t_point				*player_pos;
	t_point				*treasure_center;

	if (!player->pressed_buttons[6])
		return ;
	player_pos = player->pos;
	storage = game->scene->treasures;
	counter = 0;
	while(storage->boxes[counter])
	{
		treasure_center = storage->boxes[counter]->center;
		if (point_distance(*player_pos, *treasure_center) <= TREASURE_COLLECT_DISTANCE \
			&& treasure_collect(storage, storage->boxes[counter], player))
			break ;
		counter++;
	}
}

static void	player_inventory_update(t_game *game)
{
	t_inv_images	images;
	t_sprite_node	*sprite;
	t_player		*player;

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
	player = game->scene->player;
	if (images.pistol_image && images.bullet_image && images.slot_image && images.active_slot_image)
		inv_update_image(player->inventory, player->update_count, \
						images, game->writer);
}

// Update player data
void	update_player(t_game *game)
{
	t_vector	*move_vector;
	t_player	*player;


	player = game->scene->player;
	player_collect(game, player);
	player_rotate(player);
	player_inventory_update(game);
	move_vector = player_move_vector(player);
	if (!move_vector)
		return ;
	player_intersect_handler(game, move_vector);
	player_move_update(player, move_vector);
	free_vector(move_vector);
}