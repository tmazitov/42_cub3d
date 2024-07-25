/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:28:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 18:41:40 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

int	enemy_calc_move_target(t_enemy *enemy)
{
	t_a_point	*next;

	if (!enemy->path && !enemy->move_target)
		return (0);
	if (enemy->move_target && point_is_equal(*enemy->move_target, *enemy->pos))
		enemy->move_target = free_point(enemy->move_target);
	if (!enemy->move_target && enemy->path)
	{
		next = get_next_point(enemy->path);
		if (!next)
			return (0);
		enemy->move_target = make_point(next->x, next->y);
		if (!enemy->move_target)
			return (0);
	}
	if (!enemy->move_target && !enemy->path)
		return (0);
	return (1);
}

void	enemy_calc_path(t_enemy *enemy, t_point player_pos, t_point_list *objs_points)
{
	t_a_point	*src;
	t_a_point	*dest;
			
	src = make_a_point((int)(enemy->pos->x / 64) * 64, (int)(enemy->pos->y / 64) * 64, NULL);
	if (!src)
		return ;
	dest = make_a_point(player_pos.x, player_pos.y, NULL);
	if (!dest)
	{
		free_a_point(src);
		return ;
	}
	enemy->path = calc_path(src, dest, objs_points);
	enemy->player_pos->x = player_pos.x;
	enemy->player_pos->y = player_pos.y;
	free_a_point(src);
	free_a_point(dest);
}

t_vector	*enemy_calc_move_vector(t_enemy *enemy)
{
	t_vector	*vector;
	t_point		*target;
	t_point		*pos;

	if (!enemy->move_target)
		return (NULL);
	target = enemy->move_target;
	pos = enemy->pos;
	vector = make_vector(target->x - pos->x, target->y - pos->y);

	if (vector->x)
	{
		vector->x /= sqrt(pow(vector->x, 2) + pow(vector->y, 2));
		vector->x *= ENEMY_SPEED;
	}
	if (vector->y)
	{
		vector->y /= sqrt(pow(vector->x, 2) + pow(vector->y, 2));
		vector->y *= ENEMY_SPEED;
	}
	return (vector);
}

int	enemy_move(t_enemy *enemy, t_vector *vector)
{
	if (!vector || !enemy)
		return (0);
	enemy->pos->x += vector->x;	
	enemy->pos->y += vector->y;
	return (1);	
}