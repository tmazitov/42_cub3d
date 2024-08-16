/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/16 14:54:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	minimap_update(t_minimap *minimap, double player_rotation, t_point player_position)
{
	if (!minimap)
		return ;
	minimap->player_pos = player_position;
	minimap->player_rotation = player_rotation;
	minimap_camera_move(minimap);
	printf("minimap %f %f \n", minimap->camera->x, minimap->camera->y);
	img_clear(minimap->image);
}

