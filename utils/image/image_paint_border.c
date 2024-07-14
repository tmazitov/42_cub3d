/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_paint_border.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:23:59 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 18:46:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"


static int	border_cond(t_rectangle rect, t_image_border border)
{
	return ((rect.start.x >= 0 && rect.start.x < border.size) || \
			(rect.start.y >= 0 && rect.start.y < border.size) || \
			(rect.start.x <= rect.width - 1 && rect.start.x > rect.width - border.size) || \
			(rect.start.y <= rect.height - 1 && rect.start.y > rect.height - border.size));
}

static void round_corners(t_image *image, t_image_border border) 
{
    int		x;
    int		rel_x;
	int		y;
    int		rel_y;
	int		width;
	int		height;

	y = 0;
	width = image->width;
	height = image->height;
    while (y < border.radius) 
	{
		x = 0;
        while (x < border.radius) 
		{
			rel_x = x - border.radius;
			rel_y = y - border.radius;
			if (sqrt(pow(rel_x, 2) + pow(rel_y, 2)) < border.radius) 
			{
				img_put_pixel(image, border.color, x, y);
				img_put_pixel(image, border.color, width - 1 - x, y);
				img_put_pixel(image, border.color, x, height - 1 - y);
				img_put_pixel(image, border.color, width - 1 - x, height - 1 - y);
            }
			else
			{
				img_put_pixel(image, 0x00000000, x, y);
				img_put_pixel(image, 0x00000000, width - 1 - x, y);
				img_put_pixel(image, 0x00000000, x, height - 1 - y);
				img_put_pixel(image, 0x00000000, width - 1 - x, height - 1 - y);
			}
			x++;
        }
		y++;
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