/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:04:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/04 10:43:42 by tmazitov         ###   ########.fr       */
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

void	minimap_draw_border(t_minimap *minimap)	
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

	rel_rect.start.x = rect.start.x / 4 + MINIMAP_BORDER_SIZE;
	rel_rect.start.y = rect.start.y / 4 + MINIMAP_BORDER_SIZE;
	rel_rect.height = rect.height / 4;
	rel_rect.width = rect.width / 4;
	img_put_rectangle(minimap->image, rel_rect, color);
}

void	minimap_draw_wall(t_minimap *minimap, t_wall *wall)
{
	t_point rel_p1;
	t_point	rel_p2;
	
	rel_p1.x = wall->start->x / 4 + MINIMAP_BORDER_SIZE;
	rel_p1.y = wall->start->y / 4 + MINIMAP_BORDER_SIZE;
	rel_p2.x = wall->end->x / 4 + MINIMAP_BORDER_SIZE;
	rel_p2.y = wall->end->y / 4 + MINIMAP_BORDER_SIZE;

	img_put_line(minimap->image, MINIMAP_WALLS_COLOR, rel_p1, rel_p2);
}

