/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_line_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 20:29:13 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

void	r_l_getter_utils_1(t_ray_struct *r_s, t_line *ray,
	float angle_in_degrees)
{
	if (angle_in_degrees > 0 && angle_in_degrees < 180)
	{
		line_update_start(ray, ray->start.x, ray->start.y);
		line_update_end(ray,
			ray->start.x - (fmod(ray->start.y, 64.0) / tan(r_s->angle_in_pie)),
			(ray->start.y - fmod(ray->end.y, 64.0) - 0.001));
		r_s->y_iteration = -64;
		r_s->x_iteration = r_s->y_iteration / tan(r_s->angle_in_pie);
	}
	else if (angle_in_degrees > 180 && angle_in_degrees < 360)
	{
		line_update_start(ray, ray->start.x, ray->start.y);
		line_update_end(ray,
			ray->start.x + ((64 - fmod(ray->start.y, 64.0))
				/ tan(r_s->angle_in_pie)), ray->start.y
			- fmod(ray->end.y, 64.0) + 64);
		r_s->y_iteration = 64;
		r_s->x_iteration = r_s->y_iteration / tan(r_s->angle_in_pie);
	}
}

//NEW MODIFICATION
t_line	*ray_line_getter_x(t_game *game, float angle_in_degrees)
{
	t_ray_struct	r_s;
	t_line			*ray;

	init_ray_struct(&r_s, &angle_in_degrees);
	ray = make_line_by_points(game->scene->minimap->player_pos,
			game->scene->minimap->player_pos);
	if (!ray)
		return (NULL);
	r_l_getter_utils_1(&r_s, ray, angle_in_degrees);
	if (angle_in_degrees == 0 || angle_in_degrees == 180
		|| angle_in_degrees == 360)
		return (free_line(ray));
	r_s.iterations = 0;
	while ((get_array_map_value(*ray, game) != '1'
			&& get_array_map_value(*ray, game) != 'D') && ray->end.x > 0
		&& ray->end.y > 0 && (r_s.iterations) < PLAYER_VIEW_DEPTH)
	{
		line_update_start(ray, ray->start.x, ray->start.y);
		line_update_end(ray,
			ray->end.x + r_s.x_iteration, \
			ray->end.y + r_s.y_iteration);
		(r_s.iterations)++;
	}
	return (ray);
}

void	r_l_getter_utils_2(t_ray_struct *r_s, t_line *ray,
	float angle_in_degrees)
{
	if ((angle_in_degrees > 270 || angle_in_degrees < 90))
	{
		line_update_start(ray, ray->start.x, ray->start.y);
		line_update_end(ray,
			ray->start.x - fmod(ray->end.x, 64.0) - 0.001, \
			ray->start.y - (fmod(ray->start.x, 64.0) * tan(r_s->angle_in_pie)));
		r_s->x_iteration = -64;
		r_s->y_iteration = r_s->x_iteration * tan(r_s->angle_in_pie);
	}
	else if (angle_in_degrees > 90 && angle_in_degrees < 270)
	{
		line_update_start(ray, ray->start.x, ray->start.y);
		line_update_end(ray, ray->start.x
			- fmod(ray->end.x, 64.0) + 64, ray->start.y
			+ ((64 - fmod(ray->start.x, 64.0)) * tan(r_s->angle_in_pie)));
		r_s->x_iteration = 64;
		r_s->y_iteration = r_s->x_iteration * tan(r_s->angle_in_pie);
	}
}

//WORKING MALLOCING VERSION
t_line	*ray_line_getter_y(t_game *game, float angle_in_degrees)
{
	t_ray_struct	r_s;
	t_line			*ray;

	init_ray_struct(&r_s, &angle_in_degrees);
	ray = make_line_by_points(game->scene->minimap->player_pos,
			game->scene->minimap->player_pos);
	r_l_getter_utils_2(&r_s, ray, angle_in_degrees);
	if (!ray)
		return (NULL);
	if (angle_in_degrees == 90 || angle_in_degrees == 270)
		return (free_line(ray));
	(r_s.iterations) = 0;
	while (get_array_map_value(*ray, game) != '1'
		&& get_array_map_value(*ray, game) != 'D'
		&& ray->end.x > 0 && ray->end.y > 0
		&& (r_s.iterations) < PLAYER_VIEW_DEPTH)
	{
		line_update_start(ray, ray->start.x, ray->start.y);
		line_update_end(ray,
			ray->end.x + r_s.x_iteration, ray->end.y + r_s.y_iteration);
		(r_s.iterations)++;
	}
	return (ray);
}

t_line	*ray_line_shortest_xy(t_game *game, float angle_in_degrees)
{
	t_line	*intersect_horizontal;
	t_line	*intersect_vertical;

	intersect_horizontal = ray_line_getter_x(game, angle_in_degrees);
	intersect_vertical = ray_line_getter_y(game, angle_in_degrees);
	if (!intersect_horizontal && !intersect_vertical)
		return (NULL);
	if (!intersect_horizontal)
		return (intersect_vertical);
	if (!intersect_vertical)
		return (intersect_horizontal);
	intersect_horizontal->length
		= distance_between_points(intersect_horizontal->start,
			intersect_horizontal->end);
	intersect_vertical->length
		= distance_between_points(intersect_vertical->start,
			intersect_vertical->end);
	if (intersect_horizontal->length < intersect_vertical->length)
		return (free_line(intersect_vertical), intersect_horizontal);
	else
		return (free_line(intersect_horizontal), intersect_vertical);
}
