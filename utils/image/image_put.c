/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:46:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 01:14:25 by tmazitov         ###   ########.fr       */
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

void img_put_img(t_image *dest, t_image *src, t_point pos, double angle)
{
    int x, y;
    int dest_x, dest_y;
    int color;
    int new_x, new_y;

    double rad = angle * PI / 180.0;
    
    int cx = src->width / 2;
    int cy = src->height / 2;

    int src_x, src_y;

    for (y = 0; y < src->height; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            src_x = x - cx;
            src_y = y - cy;
            
            // Rotate the pixel
            new_x = (int)(src_x * cos(rad) - src_y * sin(rad)) + cx;
            new_y = (int)(src_x * sin(rad) + src_y * cos(rad)) + cy;

            // Calculate the destination position
            dest_x = new_x + pos.x;
            dest_y = new_y + pos.y;

            // Ensure the new coordinates are within the destination image bounds
            if (new_x >= 0 && new_x < src->width && new_y >= 0 && new_y < src->height)
            {
                color = img_get_pixel(src, x, y);
                if (color != 0xff000000)  // Assuming 0xff000000 is the transparent color
                {
                    img_put_pixel(dest, color, dest_x, dest_y);
                }
            }
        }
    }
}