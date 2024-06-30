/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:42:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 14:54:26 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	img_draw(void *win,t_image *img, int x, int y)
{
	if (!img)
		return ;
	mlx_put_image_to_window(img->mlx, win, img->content, x, y);
}