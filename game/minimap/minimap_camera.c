/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:48:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 17:27:26 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	minimap_camera_move(t_minimap *map)
{
	t_point	player_rel_pos;

	player_rel_pos.x = map->player_pos.x - (64) / 2;
	player_rel_pos.y = map->player_pos.y - (64) / 2;
	player_rel_pos.x = player_rel_pos.x / MINIMAP_SCALE + MINIMAP_BORDER_SIZE;
	player_rel_pos.y = player_rel_pos.y / MINIMAP_SCALE + MINIMAP_BORDER_SIZE;
	map->camera->x = floor(player_rel_pos.x - map->width / 2);
	map->camera->y = floor(player_rel_pos.y - map->height / 2);
}
