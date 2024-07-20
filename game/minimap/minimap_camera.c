/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:48:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 20:54:29 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static int	is_right_move_area(t_minimap *map, float relX)
{
	return (relX > map->width - MINIMAP_MOVE_AREA_SIZE && relX < map->width);
}

static int is_left_move_area(float relX)
{
	relX -= MINIMAP_BORDER_SIZE;
	return (relX > 0 && relX < MINIMAP_MOVE_AREA_SIZE);
}

static int is_top_move_area(t_minimap *map, float relY)
{
	return (relY > map->height - MINIMAP_MOVE_AREA_SIZE && relY < map->height);	
}

static int is_bop_move_area(float relY)
{
	relY -= MINIMAP_BORDER_SIZE;
	return (relY > 0 && relY < MINIMAP_MOVE_AREA_SIZE);	
}


void	minimap_camera_move(t_minimap *map, t_point player_pos, t_vector player_move)
{
	float	relX;
	float	relY;

	relX = player_pos.x / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - map->camera->x;
	relY = player_pos.y / MINIMAP_SCALE + MINIMAP_BORDER_SIZE - map->camera->y;
	if (player_move.x > 0 && is_right_move_area(map, relX))
	{
		map->camera->x += fmax(player_move.x / MINIMAP_SCALE, 1);
	}
	if (player_move.x < 0 && is_left_move_area(relX))
	{
		map->camera->x += fmin(player_move.x / MINIMAP_SCALE, -1);
	}
	if (player_move.y > 0 && is_top_move_area(map, relY))
	{
		map->camera->y += fmax(player_move.y / MINIMAP_SCALE, 1);
	}
	if (player_move.y < 0 && is_bop_move_area(relY))
	{
		map->camera->y += fmin(player_move.y / MINIMAP_SCALE, -1);
	}
	map->camera->x = max(map->camera->x, 0);
	map->camera->y = max(map->camera->y, 0);
	// printf("x : %f y : %f \n", map->camera->x, map->camera->y);
}