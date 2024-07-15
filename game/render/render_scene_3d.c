/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/15 23:00:35 by kshamsid         ###   ########.fr       */
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
	ray.start.x /= 64;
	ray.start.y /= 64;
	ray.end.x /= 64;
	ray.end.y /= 64;
	if (ray.end.x < 0 || ray.end.y < 0
		|| ray.end.x >= game->scene->map->width
		|| ray.end.y >= game->scene->map->height)
		return (printf("ERROR SOETHING RONG"), '1');
	return (game->scene->map->map_double_array[(int)ray.end.y][(int)ray.end.x]);
}


//Check SOLO why check_wall_interaction doesnt respond as it should
			// perhaps because i am too percise with the walls and
			// they dont count as LINE INTERSECTIONS
//Texture identification and putting using 
/*

*/