/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_health_bar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:22:58 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 22:15:30 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

t_enemy_health_bar	*make_enemy_hb(void *mlx, int health)
{
	t_enemy_health_bar	*hb;

	hb = malloc(sizeof(t_enemy_health_bar));
	if (!hb)
		return (NULL);
	hb->current = health;
	hb->max = health;
	hb->image = make_image(mlx);
	if (!hb->image || !img_create(hb->image, ENEMY_HEALTH_BAR_IMG_WIDTH,
			ENEMY_HEALTH_BAR_IMG_HEIGHT))
		return (free_enemy_hb(hb));
	return (hb);
}

void	*free_enemy_hb(t_enemy_health_bar *hb)
{
	if (!hb)
		return (NULL);
	if (hb->image)
		free_image(hb->image);
	free(hb);
	return (NULL);
}
