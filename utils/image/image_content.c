/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:17:58 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 18:16:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <stdio.h>

int	img_load(t_image *img, char *path)
{
	int	*w;
	int	*h;

	if (!img || access(path, R_OK) == -1)
		return (print_error("invalid texture file"), 0);
	w = &img->width; // mlx bug
	h = &img->height;
	img->content = mlx_xpm_file_to_image(img->mlx, path, w, h);
	printf("\t\twidth : %d height : %d \n", *w, *h);
	if (!img->content)
		return (print_error("invalid xpm structure"), 0);
	img->buffer = img_buffer(img);
	if (!img->buffer)
		return (0);
	return (1);
}

int	img_create(t_image *img, int width, int height)
{
	if (!img)
		return (1);
	img->width = width;
	img->height = height;
	img->content = mlx_new_image(img->mlx, img->width, img->height);
	if (!img->content)
		return (0);
	img->buffer = img_buffer(img);
	if (!img->buffer)
		return (0);
	return (1);
}

int img_scale(t_image **img, int scale)
{
	t_image	*new_img;
	int		x;
	int		y;

	new_img = make_image((*img)->mlx);
	if (!new_img)
		return (0);
	if (!img_create(new_img, (*img)->width * scale, (*img)->height * scale))
		return (0);
	y = 0;
	while (y < new_img->height)
	{
		x = 0;
		while (x < new_img->width)
		{
			img_put_pixel(new_img, img_get_pixel(*img, x / scale, y / scale), x, y);
			x++;
		}
		y++;
	}
	free_image(*img);
	*img = new_img;
	return (1);
}

void	img_clear(t_image *img)
{
	int	x;	
	int	y;	
	
	if (!img || !img->buffer)
		return ;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while(x < img->width)
		{
			img_put_pixel(img, 0x00000000, x, y);			
			x++;
		}
		y++;
	}
}
