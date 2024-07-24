/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:12:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/24 15:54:29 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static void	init_enemy(t_enemy *enemy)
{
	enemy->images = NULL;
	enemy->pos = NULL;
	enemy->hb = NULL;
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
	free(enemy);
	return (NULL);
}