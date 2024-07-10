/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/10 16:11:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static int	check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line			*wall_line;
	t_wall_node		*node;
	int				is_intersect;

	printf("\t player path %f %f %f %f\n", player_path->start.x, player_path->start.y, player_path->end.x, player_path->end.y),
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
			return (printf("\t intersect with wall %f %f %f %f\n", wall_line->start.x, wall_line->start.y, wall_line->end.x, wall_line->end.y),1);
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
	// if (move_vector->x > 0)
	// 	posX += 32;
	// else if (move_vector->x < 0)
	// 	posX -= 32;
	// if (move_vector->y > 0)
	// 	posY += 32;
	// else if (move_vector->y < 0)
	// 	posY -= 32;
	printf("move vector : %f %f\n", move_vector->x, move_vector->y);
	player_path = make_line(posX, posY, posX + move_vector->x, posY + move_vector->y);
	if (!player_path)
		return (-1);
	is_wall_intersect = check_wall_intersection(player_path, game);
	free_line(player_path);
	if (is_wall_intersect == -1)
		return (-1);
	return (!is_wall_intersect);
}

// Update player data
void	update_player(t_game *game)
{
	t_vector	*move_vector;
	int			is_player_can_move;

	player_rotate(game->scene->player);
	move_vector = player_move_vector(game->scene->player);
	if (!move_vector)
		return ;
	is_player_can_move = player_can_move(game, move_vector);
	printf("player can move: %d\n", is_player_can_move);
	if (is_player_can_move == -1)
		return (print_error("mem allocation error"));
	if (move_vector && is_player_can_move)
		player_move_update(game->scene->player, move_vector);
	if (move_vector)
		free_vector(move_vector);
}