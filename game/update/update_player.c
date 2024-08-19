/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 19:32:27 by kshamsid         ###   ########.fr       */
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

t_line offset_line(t_line player_path, int offset_pos_or_neg, float offset_amount)
{
	t_line offset_path;

	float dx = player_path.end.x - player_path.start.x;
	float dy = player_path.end.y - player_path.start.y;

	float length = sqrt(dx * dx + dy * dy);
	dx /= length;
	dy /= length;

	float normal_x = -dy;
	float normal_y = dx;

	offset_path.start.x = player_path.start.x + offset_pos_or_neg * normal_x * offset_amount;
	offset_path.start.y = player_path.start.y + offset_pos_or_neg * normal_y * offset_amount;
	offset_path.end.x = player_path.end.x + offset_pos_or_neg * normal_x * offset_amount;
	offset_path.end.y = player_path.end.y + offset_pos_or_neg * normal_y * offset_amount;

	offset_path.A = player_path.A;
	offset_path.B = player_path.B;
	offset_path.D = player_path.D;
	offset_path.length = player_path.length;

	return (offset_path);
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

void	update_player(t_game *game)
{
	t_vector	*move_vector;
	t_player	*player;
	t_line		*move_vector_x;
	t_line		*move_vector_y;
	
	player = game->scene->player;
	player_collect(game, player);
	player_rotate(player);
	player_inventory_update(game);
	
	move_vector = player_move_vector(player, game);
	if (!move_vector)
		return ;
	move_vector_x = make_line(player->pos->x, player->pos->y, player->pos->x + move_vector->x, player->pos->y);
	move_vector_y = make_line(player->pos->x, player->pos->y, player->pos->x, player->pos->y + move_vector->y);
	player_intersect_handler(game, move_vector);
	if (get_array_map_value(*move_vector_x, game) == '1'
		|| get_array_map_value(*move_vector_y, game) == '1')
	{
		free_vector(move_vector);
		free_line(move_vector_x);
		free_line(move_vector_y);
		return ;
	}
	player_move_update(player, move_vector);
	return (free_vector(move_vector), free_line(move_vector_x),
		free_line(move_vector_y), (void)0);
}