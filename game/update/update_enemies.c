/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:17:44 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 16:24:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static void update_enemy_path(t_enemy *enemy, t_game *game)
{
	t_player	*pl;
	t_a_point	*src;
	t_a_point	*dest;
	
	pl = game->scene->player;
	if (!point_is_equal(*pl->pos, *enemy->player_pos))
		enemy->path = free_path(enemy->path);
	if (!enemy->path)
	{
		src = make_a_point((int)(enemy->pos->x / 64) * 64, (int)(enemy->pos->y / 64) * 64, NULL);
		if (!src)
			return ;
		
		dest = make_a_point((int)(pl->pos->x / 64) * 64, (int)(pl->pos->y / 64) * 64, NULL);
		if (!dest)
		{
			free_a_point(src);
			return ;
		}
		printf("enemy->path : %d %d ----> %d %d \n", src->x, src->y, dest->x, dest->y);
		enemy->path = calc_path(src, dest, game->scene->objs_points);
		printf("\t new_path : %p\n", enemy->path);
		enemy->player_pos->x = pl->pos->x;
		enemy->player_pos->y = pl->pos->y;
		free_a_point(src);
		free_a_point(dest);
	}
}

static void	update_enemy_pos(t_enemy *enemy)
{
	t_vector	*move_vector;

	if (!enemy_calc_move_target(enemy))
		return ;
	move_vector = enemy_calc_move_vector(enemy);
	if (!move_vector)
		return ;
	enemy_move(enemy, move_vector);
	free_vector(move_vector);
}

static void	update_enemy(t_enemy *enemy, t_game *game)
{
	update_enemy_path(enemy, game);
	update_enemy_pos(enemy);
}

void	update_enemies(t_game *game)
{
	t_enemy_storage	*storage;
	int				counter;
	t_enemy			*enemy;

	storage = game->scene->enemies;
	counter = 0;
	while (counter < storage->size)
	{
		enemy = storage->enemies[counter];
		if (enemy->alive) 
			update_enemy(enemy, game);		
		counter++;
	}
}