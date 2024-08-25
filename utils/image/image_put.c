/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:46:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 22:46:18 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	img_put_pixel(t_image *img, int color, int x, int y)
{
	int	rel_pixel_index;

	if (!img)
		return ;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	rel_pixel_index = (y * img->line_bytes) + x;
	img->buffer[rel_pixel_index] = color;
}

void	img_put_rectangle(t_image *img, t_rectangle rect, int color)
{
	int	x;
	int	y;

	y = rect.start.y;
	while (y <= rect.start.y + rect.height)
	{
		x = rect.start.x;
		while (x <= rect.start.x + rect.width)
		{
			img_put_pixel(img, color, x, y);
			x++;
		}
		y++;
	}
}

void	img_put_step(t_image_put_step *step)
{
	double	src_x_f;
	int		src_x;
	double	src_y_f;
	int		src_y;
	int		color;

	src_x_f = (step->dest_x - step->dest_center_x) * step->cos_rad
		- (step->dest_y - step->dest_center_y) * step->sin_rad + step->center.x;
	src_y_f = (step->dest_x - step->dest_center_x) * step->sin_rad
		+ (step->dest_y - step->dest_center_y) * step->cos_rad + step->center.y;
	src_x = (int)round(src_x_f);
	src_y = (int)round(src_y_f);
	if (src_x >= 0 && src_x < step->src->width && src_y >= 0
		&& src_y < step->src->height)
	{
		color = img_get_pixel(step->src, src_x, src_y);
		if ((unsigned int)color != 0xff000000
			&& (unsigned int)color != 0x00000000)
			img_put_pixel(step->dest, color, step->dest_x, step->dest_y);
		else if ((unsigned int)color == 0x00000000)
		{
			color = img_get_pixel(step->dest, step->dest_x, step->dest_y);
			img_put_pixel(step->dest, color, step->dest_x, step->dest_y);
		}
	}
}

// Modified img_put_img function
void	img_put_img(t_image *dest, t_image *src, t_point pos, double angle)
{
	t_image_put_step	step;

	step.cos_rad = cos(-angle * PI / 180.0);
	step.sin_rad = sin(-angle * PI / 180.0);
	step.center.x = src->width / 2;
	step.center.y = src->height / 2;
	step.dest_center_x = pos.x + step.center.x;
	step.dest_center_y = pos.y + step.center.y;
	step.dest_y = 0;
	step.dest = dest;
	step.src = src;
	while (step.dest_y < dest->height)
	{
		step.dest_x = 0;
		while (step.dest_x < dest->width)
		{
			img_put_step(&step);
			step.dest_x++;
		}
		step.dest_y++;
	}
}
