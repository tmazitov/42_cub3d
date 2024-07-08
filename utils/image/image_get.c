/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:55:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 16:38:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int	img_get_pixel(t_image *img, int x, int y)
{
	int	rel_pixel_index;

	if (!img)
		return (0);
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	rel_pixel_index =  (y * img->line_bytes) + x;
	return (img->buffer[rel_pixel_index]);
}