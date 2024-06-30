/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:04:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 17:09:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static int	border_cond(int x, int y, int width, int height)
{
	return ((x >= 0 && x < MINIMAP_BORDER_SIZE) || \
			(y >= 0 && y < MINIMAP_BORDER_SIZE) || \
			(x <= width - 1 && x > width - MINIMAP_BORDER_SIZE) || \
			(y <= height - 1 && y > height - MINIMAP_BORDER_SIZE));
}

static void round_corners(t_minimap *minimap) 
{
    int		x;
    int		rel_x;
	int		y;
    int		rel_y;
	int		width;
	int		height;

	y = 0;
	width = minimap->image->width;
	height = minimap->image->height;
    while (y < MINIMAP_BORDER_RADIUS) 
	{
		x = 0;
        while (x < MINIMAP_BORDER_RADIUS) 
		{
			rel_x = x - MINIMAP_BORDER_RADIUS;
			rel_y = y - MINIMAP_BORDER_RADIUS;
			if (sqrt(pow(rel_x, 2) + pow(rel_y, 2)) < MINIMAP_BORDER_RADIUS) 
			{
				img_put_pixel(minimap->image, MINIMAP_BORDER_COLOR, x, y);
				img_put_pixel(minimap->image, MINIMAP_BORDER_COLOR, width - 1 - x, y);
				img_put_pixel(minimap->image, MINIMAP_BORDER_COLOR, x, height - 1 - y);
				img_put_pixel(minimap->image, MINIMAP_BORDER_COLOR, width - 1 - x, height - 1 - y);
            }
			else
			{
				img_put_pixel(minimap->image, 0x00000000, x, y);
				img_put_pixel(minimap->image, 0x00000000, width - 1 - x, y);
				img_put_pixel(minimap->image, 0x00000000, x, height - 1 - y);
				img_put_pixel(minimap->image, 0x00000000, width - 1 - x, height - 1 - y);
			}
			x++;
        }
		y++;
    }
}

static void	minimap_border(t_minimap *minimap)
{
	int		x;
	int		y;
	int		width;
	int		height;

	y = 0;
	width = minimap->image->width;
	height = minimap->image->height;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (border_cond(x, y, width, height))
				img_put_pixel(minimap->image, 0x0042c79a, x, y);
			x++;
		}
		y++;
	}
	round_corners(minimap);
}

void	minimap_update_image(t_minimap *minimap)
{
	if (!minimap)
		return ;
	minimap_border(minimap);
}

