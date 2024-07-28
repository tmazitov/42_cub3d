/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_line_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/28 04:43:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// #include <sys/time.h>
void	print_time_since_last_call()
{
	// static struct	timeval last_time;
	// struct timeval			current_time;
	// long int				elapsed_time;

	// gettimeofday(&current_time, NULL);
	// elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_usec - last_time.tv_usec) / 1000;
	// printf("Elapsed time: %ld ms\n", elapsed_time);
	// last_time = current_time;
}

float	distance_between_points(t_point start, t_point end)
{
	float	dx;
	float	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

//NEW MODIFICATION
t_line	*ray_line_getter_x(t_game *game, float angle_in_degrees)
{
	float	y_iteration;	//y_iteration in while loop
	float	x_iteration;	//x_iteration in while loop
	int		iterations;	//Like a Counter for block iterations to find the wall.
	float	angle_in_pie;	//angle in radians.
	t_line	*ray;	//final struct to return.

	if (angle_in_degrees < 0)
		angle_in_degrees += 360;
	if (angle_in_degrees > 360)
		angle_in_degrees -= 360;
	angle_in_pie = angle_in_degrees * PI / 180.0;
	y_iteration = 0;
	x_iteration = 0;
	ray = make_line_by_points(game->scene->minimap->player_pos, game->scene->minimap->player_pos);
	if (!ray)
		return (NULL);
	if (angle_in_degrees > 0 && angle_in_degrees < 180)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x - (fmod(ray->start.y, 64.0) / tan(angle_in_pie)), \
			(ray->start.y - fmod(ray->end.y, 64.0) - 0.001));
		y_iteration = -64;
		x_iteration = y_iteration / tan(angle_in_pie);
	}
	else if (angle_in_degrees > 180 && angle_in_degrees < 360)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x + ((64 - fmod(ray->start.y, 64.0)) / tan(angle_in_pie)), \
			ray->start.y - fmod(ray->end.y, 64.0) + 64);
		y_iteration = 64;
		x_iteration = y_iteration / tan(angle_in_pie);
	}
	if (angle_in_degrees == 0 || angle_in_degrees == 180)
		return (free_line(ray));
	iterations = 0;
	while (
		get_array_map_value(*ray, game) != '1' &&
		ray->end.x > 0
		&& ray->end.y > 0 && iterations < 12)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->end.x + x_iteration, \
			ray->end.y + y_iteration);
		iterations++;
	}
	return (ray);
}

//WORKING MALLOCING VERSION
t_line	*ray_line_getter_y(t_game *game, float angle_in_degrees)
{
	float	y_iteration;	//y_iteration in while loop
	float	x_iteration;	//x_iteration in while loop
	int		iterations;	//Like a Counter for block iterations to find the wall.
	float	angle_in_pie;	//angle in radians.
	t_line	*ray;	//final struct to return.

	if (angle_in_degrees < 0)
		angle_in_degrees += 360;
	if (angle_in_degrees > 360)
		angle_in_degrees -= 360;
	angle_in_pie = angle_in_degrees * PI / 180.0;
	y_iteration = 0;
	x_iteration = 0;
	ray = make_line_by_points(game->scene->minimap->player_pos, game->scene->minimap->player_pos);
	if (!ray)
		return (NULL);
	if ((angle_in_degrees > 270 && angle_in_degrees <= 360)
		|| (angle_in_degrees >= 0 && angle_in_degrees < 90))
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x - fmod(ray->end.x, 64.0) - 0.001, \
			ray->start.y - (fmod(ray->start.x, 64.0) * tan(angle_in_pie)));
		x_iteration = -64;
		y_iteration = x_iteration * tan(angle_in_pie);
	}
	else if (angle_in_degrees > 90 && angle_in_degrees < 270)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x - fmod(ray->end.x, 64.0) + 64, \
			ray->start.y + ((64 - fmod(ray->start.x, 64.0)) * tan(angle_in_pie)));
		x_iteration = 64;
		y_iteration = x_iteration * tan(angle_in_pie);
	}
	else if (angle_in_degrees == 90 || angle_in_degrees == 270)
		return (free_line(ray));
	iterations = 0;
	while (
		get_array_map_value(*ray, game) != '1' &&
		ray->end.x > 0
		&& ray->end.y > 0 && iterations < 12)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->end.x + x_iteration, \
			ray->end.y + y_iteration);
		iterations++;
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
	if (intersect_horizontal->length 
		< intersect_vertical->length)
		return (free_line(intersect_vertical), intersect_horizontal);
	else
		return (free_line(intersect_horizontal), intersect_vertical);
}

