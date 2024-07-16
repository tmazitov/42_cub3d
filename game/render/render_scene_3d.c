/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/16 15:27:50 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

//Func to INIT image of Scene
/*

*/

//Func to FILL it with another IMAGE for floor and the sky
/*

*/

//Func to EDIT the IMAGE 
/**/

//Find end of line equivalent of CHAR in 2d array map
char	get_array_map_value(t_line ray, t_game *game)
{
	int index_y;
	int index_x;

// 	ray.start.x = fmod(ray.start.x, 32.0);
// 	if (game->player->angle > 90 && game->player->angle < 270)
// 		ray.start.x += 32;
// 	ray.start.y = fmod(ray.start.y, 32.0);
// 	ray.end.x = fmod(ray.end.x, 32.0)
// 	if (game->player->angle > 180 && game->p   layer->angle < 360)
// 		ray.end.x += 32;
	ray.start.x /= 64;
	ray.start.y /= 64;
	ray.end.x /= 64;
	ray.end.y /= 64;
	index_x = (int)((ray.end.x  - fmod(ray.end.x, 1)));
	index_y = (int)((ray.end.y  - fmod(ray.end.y, 1)));
	if (ray.end.x < 0 || ray.end.y < 0
		|| ray.end.x >= game->scene->map->width
		|| ray.end.y >= game->scene->map->height)
		return (printf("ERROR SOETHING RONG"), '1');
	
	// return (game->scene->map->map_double_array[(int)round(ray.end.y)][(int)round(ray.end.x)]);
	return (game->scene->map->map_double_array[index_y][index_x]);
}


//Check SOLO why check_wall_interaction doesnt respond as it should
			// perhaps because i am too percise with the walls and
			// they dont count as LINE INTERSECTIONS
//Texture identification and putting using 
/*

*/