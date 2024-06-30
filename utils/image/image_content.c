/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:17:58 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 14:54:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int	img_open_file(t_image *img, char *path)
{
	int	*w;
	int	*h;

	if (!img || access(path, R_OK))
		return (1);
	w = &img->width;
	h = &img->height;
	img->content = mlx_xpm_file_to_image(img->mlx, path, w, h);
	if (!img->content)
		return (1);
	img->buffer = img_buffer(img);
	if (!img->buffer)
		return (1);
	return (0);
}

int	img_create(t_image *img, int width, int height)
{
	if (!img)
		return (1);
	img->width = width;
	img->height = height;
	img->content = mlx_new_image(img->mlx, img->width, img->height);
	if (!img->content)
		return (1);
	img->buffer = img_buffer(img);
	if (!img->buffer)
		return (1);
	return (0);
}
