/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_paint_border.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:23:59 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 23:05:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static int	border_cond(t_rectangle rect, t_image_border border)
{
	return ((rect.start.x >= 0 && rect.start.x < border.size)
		|| (rect.start.y >= 0 && rect.start.y < border.size)
		|| (rect.start.x <= rect.width - 1 && rect.start.x > rect.width
			- border.size) || (rect.start.y <= rect.height - 1
			&& rect.start.y > rect.height - border.size));
}

static void	draw_corner(t_image *image, int color, t_point pos)
{
	img_put_pixel(image, color, pos.x, pos.y);
	img_put_pixel(image, color, image->width - pos.x, pos.y);
	img_put_pixel(image, color, pos.x, image->height - pos.y);
	img_put_pixel(image, color, image->width - pos.x, image->height - pos.y);
}

static void	draw_empty(t_image *image, t_point pos)
{
	img_put_pixel(image, 0, pos.x, pos.y);
	img_put_pixel(image, 0, image->width - pos.x, pos.y);
	img_put_pixel(image, 0, pos.x, image->height - pos.y);
	img_put_pixel(image, 0, image->width - pos.x, image->height - pos.y);
}

static void	round_corners(t_image *image, t_image_border border)
{
	int		rel_x;
	int		rel_y;
	t_point	pos;

	pos.y = 0;
	while (pos.y < border.radius)
	{
		pos.x = 0;
		while (pos.x < border.radius)
		{
			rel_x = pos.x - border.radius;
			rel_y = pos.y - border.radius;
			if (sqrt(pow(rel_x, 2) + pow(rel_y, 2)) < border.radius)
				draw_corner(image, border.color, pos);
			else
				draw_empty(image, pos);
			pos.x++;
		}
		pos.y++;
	}
}

void	img_paint_border(t_image *image, t_image_border border)
{
	t_rectangle	rect;

	rect.start.y = 0;
	rect.width = image->width;
	rect.height = image->height;
	while (rect.start.y < rect.height)
	{
		rect.start.x = 0;
		while (rect.start.x < rect.width)
		{
			if (border_cond(rect, border))
				img_put_pixel(image, border.color, rect.start.x, rect.start.y);
			rect.start.x++;
		}
		rect.start.y++;
	}
	round_corners(image, border);
}
