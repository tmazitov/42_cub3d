/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:12:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 15:30:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static void	init_enemy(t_enemy *enemy)
{
	enemy->images = NULL;
	enemy->pos = NULL;
	enemy->hb = NULL;
	enemy->alive = 1;
	enemy->path = NULL;
	enemy->player_pos = NULL;
	enemy->move_target = NULL;
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
	if (enemy->images)
		free_enemy_images(enemy->images);
	if (enemy->path)
		free_path(enemy->path);
	if (enemy->player_pos)
		free_point(enemy->player_pos);
	if (enemy->move_target)
		free_point(enemy->move_target);
	free(enemy);
	return (NULL);
}