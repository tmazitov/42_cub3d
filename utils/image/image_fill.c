/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:46:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 16:46:01 by tmazitov         ###   ########.fr       */
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

