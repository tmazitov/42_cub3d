/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/30 13:55:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static t_line	*check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line		*wall_line;
	t_wall_node	*node;
	t_point		inter;
	int			is_intersect;

	node = game->scene->map->walls->start;
	while (node)
	{
		wall_line = wall_to_line(node->wall);
		if (!wall_line)
			return (NULL);
		is_intersect = check_intersection(player_path, wall_line, &inter);
		if (is_intersect)
		{
			line_update_by_points(player_path, player_path->start, inter);
			return (wall_line);
		}
		free_line(wall_line);
		node = node->next;
	}
	return (NULL);
}

static void	update_player_vector(t_vector *move_vector, t_line *player_path,
		t_line *wall_line)
{
	t_line	*wall_perpendicular;

	wall_perpendicular = line_perpendicular(wall_line, player_path->start);
	if (!wall_perpendicular)
		return ;
	move_vector->x = -(wall_perpendicular->b + player_path->b) * -1;
	move_vector->y = (wall_perpendicular->a + player_path->a) * -1;
	free_line(wall_perpendicular);
}

t_line	offset_line(t_line pl_path, int offset_pn, float offset_a)
{
	t_line	offset_path;
	float	dx;
	float	dy;
	float	normal_x;
	float	normal_y;

	dx = pl_path.end.x - pl_path.start.x;
	dy = pl_path.end.y - pl_path.start.y;
	dx /= sqrt(dx * dx + dy * dy);
	dy /= sqrt(dx * dx + dy * dy);
	normal_x = -dy;
	normal_y = dx;
	offset_path.start.x = pl_path.start.x + offset_pn * normal_x * offset_a;
	offset_path.start.y = pl_path.start.y + offset_pn * normal_y * offset_a;
	offset_path.end.x = pl_path.end.x + offset_pn * normal_x * offset_a;
	offset_path.end.y = pl_path.end.y + offset_pn * normal_y * offset_a;
	offset_path.a = pl_path.a;
	offset_path.b = pl_path.b;
	offset_path.d = pl_path.d;
	offset_path.length = pl_path.length;
	return (offset_path);
}

static void	player_intersect_handler(t_game *game, t_vector *move_vector)
{
	t_line	*player_path;
	t_line	*inter_wall;
	float	pos_x;
	float	pos_y;

	if (!move_vector)
		return ;
	pos_x = game->scene->player->pos->x;
	pos_y = game->scene->player->pos->y;
	player_path = make_line(pos_x, pos_y, pos_x + move_vector->x, pos_y
			+ move_vector->y);
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
	float		x;
	float		y;
	t_vector	*move;
	t_line		*move_x;
	t_line		*move_y;

	x = game->scene->player->pos->x;
	y = game->scene->player->pos->y;
	player_collect(game, game->scene->player);
	player_rotate(game->scene->player);
	player_inventory_update(game);
	if (game->scene->player->pressed_buttons[6])
		player_door_update(game);
	move = player_move_vector(game->scene->player, game->scene);
	if (!move)
		return ;
	move_x = make_line(x, y, x + move->x, y);
	move_y = make_line(x, y, x, y + move->y);
	if (!move_x || !move_y)
		return (free_vector(move), free_line(move_y), free_line(move_x),
			(void)0);
	player_intersect_handler(game, move);
	if (is_player_can_move(game, *move, *move_x, *move_y))
		player_move_update(game->scene->player, move);
	return (free_vector(move), free_line(move_y), free_line(move_x), (void)0);
}
