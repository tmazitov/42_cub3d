/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:12:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/13 18:03:13 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static void	init_enemy(t_enemy *enemy)
{
	enemy->pos = NULL;
	enemy->hb = NULL;
	enemy->alive = 1;
	enemy->path = NULL;
	enemy->player_pos = NULL;
	enemy->move_target = NULL;
	enemy->move_anime = NULL;
}

t_enemy	*make_enemy(void *mlx, t_point pos, int health)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	init_enemy(enemy);
	enemy->pos = make_point(pos.x, pos.y);
	if (!enemy->pos)
		return (free_enemy(enemy));
	enemy->hb = make_enemy_hb(mlx, health);
	if (!enemy->hb)
		return (free_enemy(enemy));
	enemy->player_pos = make_point(0, 0);
	if (!enemy->player_pos)
		return (free_enemy(enemy));
	if (!make_enemy_anime(enemy))
		return (free_enemy(enemy));
	return (enemy);
}

void	*free_enemy(t_enemy *enemy)
{
	if (!enemy)
		return (NULL);
	if (enemy->pos)
		free_point(enemy->pos);
	if (enemy->hb)
		free_enemy_hb(enemy->hb);
	if (enemy->path)
		free_path(enemy->path);
	if (enemy->player_pos)
		free_point(enemy->player_pos);
	if (enemy->move_target)
		free_point(enemy->move_target);
	free_enemy_anime(enemy);
	free(enemy);
	return (NULL);
}