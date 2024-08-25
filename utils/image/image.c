/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:14:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 23:09:45 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_image	*make_image(void *mlx)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->mlx = mlx;
	image->width = 0;
	image->height = 0;
	image->endian = 0;
	image->line_bytes = 0;
	image->pixel_bits = 0;
	image->content = NULL;
	image->buffer = NULL;
	return (image);
}

void	*free_image(t_image *image)
{
	if (!image)
		return (NULL);
	if (image->content)
		mlx_destroy_image(image->mlx, image->content);
	free(image);
	return (NULL);
}
