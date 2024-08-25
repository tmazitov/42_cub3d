/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:00:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 23:08:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int	*img_buffer(t_image *img)
{
	int	*buffer;

	buffer = (int *)mlx_get_data_addr(img->content,
			&img->pixel_bits,
			&img->line_bytes,
			&img->endian);
	if (!buffer)
		return (NULL);
	img->line_bytes /= 4;
	return (buffer);
}
