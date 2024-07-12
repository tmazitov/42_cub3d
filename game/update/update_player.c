/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 18:23:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static int	check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line			*wall_line;
	t_wall_node		*node;
	int				is_intersect;

	node = game->scene->map->walls->start;
	while(node)
	{
		wall_line = wall_to_line(node->wall);
		if (!wall_line)
			return (-1);
		is_intersect = check_intersection(player_path, wall_line);
	 	// free_line(wall_line);
		if (is_intersect == -1)
			return (-1);
		if (is_intersect)
			return (1);
		node = node->next;
	}
	return (0);
}

// Check if player can move in the direction of move_vector
static int	player_can_move(t_game *game, t_vector *move_vector)
{
	t_line			*player_path;
	int				is_wall_intersect;
	float			posX;
	float			posY;

	if (!move_vector)
		return (0);
	posX = game->scene->player->pos->x;
	posY = game->scene->player->pos->y;
	player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	if (!player_path)
		return (-1);
	is_wall_intersect = check_wall_intersection(player_path, game);
	free_line(player_path);
	if (is_wall_intersect == -1)
		return (-1);
	return (!is_wall_intersect);
}

static void	player_collect(t_game *game, t_player *player)
{
	t_treasure_storage	*storage;
	int					counter;
	t_point				*player_pos;
	t_point				*treasure_center;

	if (!player->pressed_buttons[6])
		return ;
	player_pos = game->scene->player->pos;
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

// Update player data
void	update_player(t_game *game)
{
	t_vector	*move_vector;
	int			is_player_can_move;

	player_collect(game, game->scene->player);
	player_rotate(game->scene->player);
	move_vector = player_move_vector(game->scene->player);
	if (!move_vector)
		return ;
	is_player_can_move = player_can_move(game, move_vector);
	if (is_player_can_move == -1)
		return (print_error("mem allocation error"));
	if (move_vector && is_player_can_move)
		player_move_update(game->scene->player, move_vector);
	if (move_vector)
		free_vector(move_vector);
}