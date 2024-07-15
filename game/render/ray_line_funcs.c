/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_line_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/15 23:22:01 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

//create me a function to convert

/*
static int	check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line			*wall_line;
	t_wall_node		*node;
	int				is_intersect;

	// printf("\t player path %f %f %f %f\n", player_path->start.x, player_path->start.y, player_path->end.x, player_path->end.y),
	node = game->scene->map->walls->start;
	while(node)
	{
		wall_line = wall_to_line(node->wall);
		if (!wall_line)
			return (-1);
		is_intersect = check_intersection(player_path, wall_line);
		if (is_intersect)
			return (printf("\t intersect with wall %f %f %f %f\n", wall_line->start.x, wall_line->start.y, wall_line->end.x, wall_line->end.y),1);
		node = node->next;
	}
	// printf("\t no intersect\n");
	return (0);
}
*/

#include <sys/time.h>
void	print_time_since_last_call()
{
	static struct	timeval last_time;
	struct timeval			current_time;
	long int				elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_usec - last_time.tv_usec) / 1000;
	printf("Elapsed time: %ld ms\n", elapsed_time);
	last_time = current_time;
}

float	distance_between_points(t_point start, t_point end)
{
	float	dx;
	float	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

//CAT VIDEO TRY
t_line	ray_line_getter_x(t_game *game, float angle_in_degrees)
{
	float	y_iteration;	//y_iteration in while loop
	float	x_iteration;	//x_iteration in while loop
	int		iterations;	//Like a Counter for block iterations to find the wall.
	float	angle_in_pie;	//angle in radians.
	t_line	ray;	//final struct to return.

	if (angle_in_degrees < 0)
		angle_in_degrees += 360;
	if (angle_in_degrees > 360)
		angle_in_degrees -= 360;
	angle_in_pie = angle_in_degrees * PI / 180.0;
	ray.start = game->scene->minimap->player_pos;
	ray.end = game->scene->minimap->player_pos;
	printf("player_angle = %f\n", angle_in_degrees);
	if (angle_in_degrees > 0 && angle_in_degrees < 180)
	{
		ray.end.y = ray.start.y - fmod(ray.end.y, 64.0) /*- 0.01*/;//-----------------------
		ray.end.x = ray.start.x - (fmod(ray.start.y, 64.0) / tan(angle_in_pie));
		y_iteration = -64;
		x_iteration = y_iteration / tan(angle_in_pie);
	}
	if (angle_in_degrees > 180 && angle_in_degrees < 360)
	{
		ray.end.y = ray.start.y - fmod(ray.end.y, 64.0) + 64/*- 0.01*/;//-----------------------
		ray.end.x = ray.start.x + ((64 -fmod(ray.start.y, 64.0)) / tan(angle_in_pie));
		y_iteration = 64;
		// if (angle_in_degrees > 180 && angle_in_degrees < 360)
		// 	x_iteration = y_iteration / tan(angle_in_pie);
		// else
		x_iteration = -y_iteration / tan(angle_in_pie);
	}
	if (angle_in_degrees == 0 || angle_in_degrees == 180)
	{
		ray.end.y = ray.start.y;
		ray.end.x = ray.start.x;
		y_iteration = 0;
		x_iteration = 0;
	}
	iterations = 0;
	//if i do check_wall_intersection(&ray, game) != 0 iterates once for testing.
	while (/*check_wall_intersection(&ray, game) == 0 && */
		// get_array_map_value(ray, game) == '0' &&
		ray.end.x > 0
		&& ray.end.y > 0 && iterations < 0)
	{
		ray.end.x += x_iteration;
		ray.end.y += y_iteration;
		iterations++;
	}
	printf("value of BLOCK = %c\n", get_array_map_value(ray, game));
	ray.length = distance_between_points(ray.start, ray.end);
	return (ray);
}

t_line	ray_line_getter_y(t_game *game, float angle_in_degrees)
{
	float	y_iteration;	//y_iteration in while loop
	float	x_iteration;	//x_iteration in while loop
	int		iterations;	//Like a Counter for block iterations to find the wall.
	float	angle_in_pie;	//angle in radians.
	t_line	ray;	//final struct to return.

	if (angle_in_degrees < 0)
		angle_in_degrees += 360;
	if (angle_in_degrees > 360)
		angle_in_degrees -= 360;
	angle_in_pie = angle_in_degrees * PI / 180.0;
	ray.start = game->scene->minimap->player_pos;
	ray.end = game->scene->minimap->player_pos;
	if ((angle_in_degrees > 270 && angle_in_degrees <= 360)
		|| (angle_in_degrees >= 0 && angle_in_degrees < 90))//LOOKING LEFT
	{
		ray.end.x = ray.start.x - fmod(ray.end.x, 64.0) /*- 0.01*/;//-----------------------
		ray.end.y = ray.start.y - (fmod(ray.start.x, 64.0) * tan(angle_in_pie));
		x_iteration = -64;
		y_iteration = -x_iteration * tan(angle_in_pie);
	}
	if (angle_in_degrees > 90 && angle_in_degrees < 270)//LOOKING RIGHT
	{
		ray.end.x = ray.start.x - fmod(ray.end.x, 64.0) + 64/*- 0.01*/;//-----------------------
		ray.end.y = ray.start.y + ((64 - fmod(ray.start.x, 64.0)) * tan(angle_in_pie));
		x_iteration = 64;
		// if (angle_in_degrees > 90 && angle_in_degrees < 270)
		// 	y_iteration = -x_iteration * tan(angle_in_pie);
		// else
			y_iteration = x_iteration * tan(angle_in_pie);
	}
	if (angle_in_degrees == 90 || angle_in_degrees == 270)
	{
		ray.end.x = ray.start.y;
		ray.end.y = ray.start.x;
		y_iteration = 0;
		x_iteration = 0;
	}
	iterations = 0;
	while (/*check_wall_intersection(&ray, game) == 0 && */
		// get_array_map_value(ray, game) == '0' &&
		ray.end.x > 0
		&& ray.end.y > 0 && iterations < 0)
	{
		ray.end.x += x_iteration;
		ray.end.y += y_iteration;
		iterations++;
	}
	printf("value of BLOCK = %c\n", get_array_map_value(ray, game));
	ray.length = distance_between_points(ray.start, ray.end);
	return (ray);
}

t_line	ray_line_shortest_xy(t_game *game, float angle_in_degrees)
{
	t_line	intersect_horizontal;
	t_line	intersect_vertical;

	intersect_horizontal = ray_line_getter_x(game, angle_in_degrees);
	intersect_vertical = ray_line_getter_y(game, angle_in_degrees);
	if (distance_between_points(intersect_horizontal.start, intersect_horizontal.end) 
		< distance_between_points(intersect_vertical.start, intersect_vertical.end))
		return (intersect_horizontal);
	else
		return (intersect_vertical);
}
	//Calculate distance to Cross Section.

	//Put line according to distance
	//Iterate Over to the next Cross Section.
	//take value x4 and check for the value in the type of wall. NO SO EA WE
	//Draw vertical line depending on distance from wall.
	//Max height == height of the screen.

	// render_minimap(game);
	// render_3d(game);


// int get_next_vertical_pixel()
// {

// }

