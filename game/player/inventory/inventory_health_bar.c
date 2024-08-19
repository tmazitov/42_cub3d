/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_health_bar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:24:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 15:42:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory.h"

t_health_bar	*make_health_bar(int max)
{
	t_health_bar	*bar;

	bar = malloc(sizeof(t_health_bar));
	if (!bar)
		return (NULL);
	bar->image = NULL;
	bar->current = max;
	bar->max = max;
	return (bar);
}

int	hb_new_image(void *mlx, t_health_bar *bar, int width, int height)
{
	t_image_border	border;
	t_rectangle		rect;
	t_rectangle		fill;

	if (!bar)
		return (0);
	border.color = 0x545657;
	border.size = 4;
	border.radius = 4;
	if (bar->image)
		free_image(bar->image);
	bar->image = make_image(mlx);
	if (!bar->image)
		return (0);
	if (!img_create(bar->image, width, height))
		return (0);
	fill.start.x = 0;
	fill.start.y = 0;
	fill.width = width;
	fill.height = height;
	rect.start.x = 0;
	rect.start.y = 0;
	rect.width = (int)(bar->current * width / bar->max);
	rect.height = height;
	img_put_rectangle(bar->image, fill, 0x4a4a4a);
	img_put_rectangle(bar->image, rect, 0xd14755);
	img_paint_border(bar->image, border);
	return (1);
}

int		hb_add_damage(t_health_bar *bar, int damage)
{
	if (!bar)
		return (0);
	bar->current = max(0, bar->current - damage);
	if (!hb_new_image(bar->image->mlx, bar, bar->image->width, bar->image->height))
		return (0);
	return (1);
}

void	*free_health_bar(t_health_bar *bar)
{
	if (!bar)
		return (NULL);
	if (bar->image)
		free_image(bar->image);
	free(bar);
	return (NULL);
}