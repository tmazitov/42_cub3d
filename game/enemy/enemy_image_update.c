/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:27:48 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/24 15:33:43 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

void	enemy_hb_image_update(t_enemy_health_bar *hb)
{
	float			full_percent;
	t_rectangle		rect;
	t_image_border	border;
	
	img_clear(hb->image);
	full_percent = hb->current / (float)hb->max;
	rect.start.x = 0;
	rect.start.y = 0;
	rect.height = ENEMY_HEALTH_BAR_IMG_HEIGHT;
	rect.width = ENEMY_HEALTH_BAR_IMG_WIDTH * full_percent;
	img_put_rectangle(hb->image, rect, ENEMY_HEALTH_BAR_FILL_COLOR);
	border.color = ENEMY_HEALTH_BAR_BORDER_COLOR;
	border.size = ENEMY_HEALTH_BAR_BORDER_SIZE;
	border.radius = 0;
	img_paint_border(hb->image, border);
}