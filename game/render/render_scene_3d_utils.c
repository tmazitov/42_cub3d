/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:09:21 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 19:09:48 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	update_screen_values(t_render_window *r_w, t_game *game)
{
	r_w->temp_to_rotate += (r_w->player_fov / (game->width));
	r_w->screen_render.x += 1;
	r_w->vert_wall_iter++;
}

void	update_w_slct_and_d_t_wll(t_render_window *r_w, t_game *game,
	t_line *ray, float *d_t_wall)
{
	r_w->wall_select = get_wall_side(game->scene
			->minimap->player_rotation + r_w->temp_to_rotate, ray->end);
	d_t_wall[r_w->vert_wall_iter]
		= distance_between_points(ray->start, ray->end);
}

char	get_array_map_value(t_line ray, t_game *game)
{
	int	index_y;
	int	index_x;

	ray.start.x /= 64;
	ray.start.y /= 64;
	ray.end.x /= 64;
	ray.end.y /= 64;
	index_x = (int)((ray.end.x - fmod(ray.end.x, 1)));
	index_y = (int)((ray.end.y - fmod(ray.end.y, 1)));
	if (ray.end.x < 0 || ray.end.y < 0
		|| ray.end.x >= game->scene->map->width
		|| ray.end.y >= game->scene->map->height)
		return ('1');
	return (game->scene->map->map_double_array[index_y][index_x]);
}
