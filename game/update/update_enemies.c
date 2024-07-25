/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:17:44 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 15:15:49 by tmazitov         ###   ########.fr       */
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
		src = make_a_point(enemy->pos->x, enemy->pos->y, NULL);
		if (!src)
			return ;
		dest = make_a_point((int)(pl->pos->x / 64) * 64, (int)(pl->pos->y / 64) * 64, NULL);
		if (!dest)
		{
			free_a_point(src);
			return ;
		}
		enemy->path = calc_path(src, dest, game->scene->objs_points);
		enemy->player_pos->x = pl->pos->x;
		enemy->player_pos->y = pl->pos->y;
	}
}

static void	update_enemy_pos(t_enemy *enemy, t_game *game)
{
	(void)enemy;
	(void)game;
}

static void	update_enemy(t_enemy *enemy, t_game *game)
{
	update_enemy_path(enemy, game);
	update_enemy_pos(enemy, game);
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