/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 23:54:03 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	minimap_update(t_minimap *minimap, double player_rotation,
		t_point player_position)
{
	if (!minimap)
		return ;
	minimap->is_update_image = minimap->player_pos.x != player_position.x
		|| minimap->player_pos.y != player_position.y
		|| player_rotation != minimap->player_rotation;
	minimap->player_pos = player_position;
	minimap->player_rotation = player_rotation;
	minimap_camera_move(minimap);
	if (minimap->is_update_image)
		img_clear(minimap->image);
}
