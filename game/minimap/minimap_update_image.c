/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:04:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 16:34:30 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	minimap_draw_border(t_minimap *minimap)
{
	t_image_border	border;

	border.size = MINIMAP_BORDER_SIZE;
	border.radius = MINIMAP_BORDER_RADIUS;
	border.color = MINIMAP_BORDER_COLOR;
	img_paint_border(minimap->image, border);
}

void	minimap_draw_background(t_minimap *minimap)
{
	t_rectangle	rect;

	rect.start.x = MINIMAP_BORDER_SIZE;
	rect.start.y = MINIMAP_BORDER_SIZE;
	rect.width = minimap->width - MINIMAP_BORDER_SIZE * 2;
	rect.height = minimap->height - MINIMAP_BORDER_SIZE * 2;
	img_put_rectangle(minimap->image, rect, MINIMAP_BACKGROUND_COLOR);
}

void	minimap_draw_rect(t_minimap *minimap, t_rectangle rect, \
							int color)
{
	t_rectangle	rel_rect;

	rel_rect.start.x = round(rect.start.x / MINIMAP_SCALE) + MINIMAP_BORDER_SIZE - minimap->camera->x;
	rel_rect.start.y = round(rect.start.y / MINIMAP_SCALE) + MINIMAP_BORDER_SIZE - minimap->camera->y;
	rel_rect.height = rect.height / MINIMAP_SCALE;
	rel_rect.width = rect.width / MINIMAP_SCALE;
	img_put_rectangle(minimap->image, rel_rect, color);
}

void	minimap_draw_image(t_minimap *minimap, t_image *image, t_point pos, double angle)
{
	t_point	rel_pos;

	rel_pos.x = pos.x / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - minimap->camera->x;
	rel_pos.y = pos.y / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - minimap->camera->y;
	img_put_img(minimap->image, image, rel_pos, angle);
}

void	minimap_draw_wall(t_minimap *minimap, t_wall *wall)
{
	t_point rel_p1;
	t_point	rel_p2;
	
	rel_p1.x = wall->start->x / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - minimap->camera->x;
	rel_p1.y = wall->start->y / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - minimap->camera->y;
	rel_p2.x = wall->end->x / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - minimap->camera->x;
	rel_p2.y = wall->end->y / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - minimap->camera->y;

	img_put_line(minimap->image, MINIMAP_WALLS_COLOR, rel_p1, rel_p2);
}

