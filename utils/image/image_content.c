/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:17:58 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/03 14:14:14 by tmazitov         ###   ########.fr       */
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
	w = &img->width;
	h = &img->height;
	img->content = mlx_xpm_file_to_image(img->mlx, path, w, h);
	if (!img->content)
		return (print_error("invalid xpm structure"), 0);
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
