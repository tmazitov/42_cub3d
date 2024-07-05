/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 00:50:00 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	minimap_update(t_minimap *minimap, double player_rotation, t_point player_position)
{
	if (!minimap)
		return ;
	// minimap->player->x = game->player->x;
	// minimap->player->y = game->player->y;
	// minimap->player->angle = game->player->angle;
	minimap->player_pos = player_position;
	minimap->player_rotation = player_rotation;
	img_clear(minimap->image);
}

