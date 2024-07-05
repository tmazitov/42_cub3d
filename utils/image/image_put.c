/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:46:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 00:03:55 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void img_put_pixel(t_image *img, int color, int x, int y)
{
	int	rel_pixel_index;

	if (!img)
		return ;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	rel_pixel_index =  (y * img->line_bytes) + x;
	img->buffer[rel_pixel_index] = color;
}

void	img_put_line(t_image *img, int color, t_point p1, t_point p2)
{
	// printf("put line from %f %f to %f %f\n", p1.x, p1.y, p2.x, p2.y);
	
	while (p1.x == p2.x && p1.y != p2.y)
	{
		img_put_pixel(img, color, p1.x, p1.y);
		if (p1.y < p2.y)
			p1.y += 1;
		else if (p1.y > p2.y)
			p1.y -= 1;
	}
	
	while (p1.y == p2.y && p1.x != p2.x)
	{
		img_put_pixel(img, color, p1.x, p1.y);
		if (p1.x < p2.x)
			p1.x += 1;
		else if (p1.x > p2.x)
			p1.x -= 1;
	}
}

void	img_put_rectangle(t_image* img, t_rectangle rect, int color)
{
	int	x;
	int	y;

	y = rect.start.y;
	while (y != rect.start.y + rect.height)
	{
		x = rect.start.x;
		while (x != rect.start.x + rect.width)
		{
			img_put_pixel(img, color, x, y);
			x++;
		}
		y++;
	}
}

void	img_put_img(t_image *dest, t_image *src, t_point pos)
{
	int	x;
	int	y;
	int	dest_x;
	int	dest_y;
	int color;

	y = 0;
	dest_y = pos.y;
	while (y < src->height)
	{
		x = 0;
		dest_x = pos.x;
		while (x < src->width)
		{
			color = img_get_pixel(src, x, y);
			if (color != 0xff000000)
				img_put_pixel(dest, color, dest_x, dest_y);
			x++;
			dest_x++;
		}
		y++;
		dest_y++;
	}
}