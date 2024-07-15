/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/15 18:48:34 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

//create me a function to convert

static int	check_wall_intersection(t_line *player_path, t_game *game)
{
	t_line			*wall_line;
	t_wall_node		*node;
	int				is_intersect;

	printf("\t player path %f %f %f %f\n", player_path->start.x, player_path->start.y, player_path->end.x, player_path->end.y),
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
	printf("\t no intersect\n");
	return (0);
}

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
	if (angle_in_degrees > 0 && angle_in_degrees < 180)
	{
		ray.end.y = ray.start.y - fmod(ray.end.y, 64.0) /*- 0.01*/;//-----------------------
		ray.end.x = ray.start.x - (fmod(ray.start.y, 64.0) / tan(angle_in_pie));
		y_iteration = -64;
		if (angle_in_degrees > 0 && angle_in_degrees < 90)
			x_iteration = y_iteration / tan(angle_in_pie);
		else
			x_iteration = -y_iteration / tan(angle_in_pie);
	}
	if (angle_in_degrees > 180 && angle_in_degrees < 360)
	{
		ray.end.y = ray.start.y - fmod(ray.end.y, 64.0) + 64/*- 0.01*/;//-----------------------
		ray.end.x = ray.start.x + (fmod(ray.start.y, 64.0) / tan(angle_in_pie));
		y_iteration = 64;
		if (angle_in_degrees > 180 && angle_in_degrees < 270)
			x_iteration = -y_iteration / tan(angle_in_pie);
		else
			x_iteration = y_iteration / tan(angle_in_pie);
	}
	if (angle_in_degrees == 0 || angle_in_degrees == 180)
	{
		ray.end.y = ray.start.y;
		ray.end.x = ray.start.x;
		y_iteration = 0;
		x_iteration = 0;
	}
	iterations = 0;
	while (check_wall_intersection(&ray, game) != 0 && ray.end.x > 0
		&& ray.end.y > 0 && iterations < 10)
	{
		ray.end.x += x_iteration;
		printf("ray.end.y (%f) + y_iteration = (%f)\n", ray.end.y ,y_iteration);
		ray.end.y += y_iteration;
		iterations++;
	}
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

	printf("player ANGLE DEGREES (ray_line_getter) = %f\n", angle_in_degrees);
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
		printf("\t\t [[ray_end_x = %f]]\n", ray.end.x);
		ray.end.x = ray.start.x - fmod(ray.end.x, 64.0) /*- 0.01*/;//-----------------------
		ray.end.y = ray.start.y - (fmod(ray.start.x, 64.0) * tan(angle_in_pie));
		// ray.end.y = ray.start.y;
		x_iteration = -64;
		if (angle_in_degrees > 270 && angle_in_degrees < 360)
			y_iteration = x_iteration * tan(angle_in_pie);
		else
			y_iteration = -x_iteration * tan(angle_in_pie);
	}
	if (angle_in_degrees > 90 && angle_in_degrees < 270)//LOOKING RIGHT
	{
		ray.end.x = ray.start.x - fmod(ray.end.x, 64.0) + 64/*- 0.01*/;//-----------------------
		ray.end.y = ray.start.y + (fmod(ray.start.x, 64.0) * tan(angle_in_pie));
		x_iteration = 64;
		if (angle_in_degrees > 90 && angle_in_degrees < 270)
			y_iteration = -x_iteration * tan(angle_in_pie);
		else
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
	while (check_wall_intersection(&ray, game) != 0 && ray.end.x > 0
		&& ray.end.y > 0 && iterations < 10)
	{
		ray.end.x += x_iteration;
		printf("ray.end.y (%f) + y_iteration = (%f)\n", ray.end.y ,y_iteration);
		ray.end.y += y_iteration;
		iterations++;
	}
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

// t_line ray_line_getter(t_game *game, float chosen_rotation)
// {
//     float distance_to_intersec_y;
//     float dx_value;
//     float iteration_distance;
//     t_line player_path;
//     float arctan;

//     // Convert the chosen_rotation to radians for trigonometric functions
//     float rotation_radians = chosen_rotation * M_PI / 180.0;

//     arctan = tan(rotation_radians);

//     // Init path
//     player_path.start = game->scene->minimap->player_pos;
//     player_path.end = game->scene->minimap->player_pos;

//     distance_to_intersec_y = fmod(player_path.end.y, 64.0);
//     if (chosen_rotation > 180 && chosen_rotation < 360)
//         distance_to_intersec_y = 64 - fmod(player_path.end.y, 64.0);

//     dx_value = distance_to_intersec_y / arctan;

//     player_path.end.x += dx_value;
//     player_path.end.y -= distance_to_intersec_y;

//     if (chosen_rotation > 0 && chosen_rotation < 180)
//         iteration_distance = 64 / arctan;
//     else
//         iteration_distance = -64 / arctan;

//     // Adjust iteration_distance for vertical and horizontal steps
//     // float x_step = 64 / arctan;
//     float y_step = 64;

// 	int iterations = 0;
//     // if (chosen_rotation > 0 && chosen_rotation < 180)
//     //     player_path.end.y += 64;
//     // else
//     //     player_path.end.y -= 64;
//     while (check_wall_intersection(&player_path, game) == 0 && player_path.end.x > 0 && player_path.end.y > 0 && iterations < 20)
//     {
//         player_path.end.x += iteration_distance;
//         if (chosen_rotation > 0 && chosen_rotation < 180)
//             player_path.end.y += y_step;
//         else
//             player_path.end.y -= y_step;
// 		iterations++;
//     }

//     return player_path;
// }


// void	render_scene(t_game *game)
// ----------------------------------
// t_line	ray_line_getter(t_game *game, float chosen_rotation)
// {
// 	float	distance_to_itersec_y;
// 	float	dx_value;
// 	float	iteration_distance;
// 	t_line	player_path;
// 	float	arctan;

// 	arctan = atan(chosen_rotation);
// 	//Init path
// 	player_path.start = game->scene->minimap->player_pos;
// 	player_path.end = game->scene->minimap->player_pos;
// 	distance_to_itersec_y = fmod(player_path.end.y, 64.0);
// 	if (game->scene->minimap->player_rotation > 180 && game->scene->minimap->player_rotation < 360)
// 		distance_to_itersec_y = 64 - fmod(player_path.end.y, 64.0);
// 	iteration_distance = 64;
// 	// printf("distance to intersection mini_DY = %f\n", distance_to_itersec_y);
// 	dx_value = find_dx(distance_to_itersec_y, chosen_rotation, game);
// 	// iteration_distance = find_dx((float)64, chosen_rotation, game);
// 	// printf("iteration distance of DX %f\n", iteration_distance);
// 	player_path.end.x -= dx_value;
// 	player_path.end.y -= distance_to_itersec_y;
// 	float	y_iter = 64;
// 	if (game->scene->minimap->player_rotation > 180 && game->scene->minimap->player_rotation < 360)
// 		y_iter = -64;

// 	// if (game->scene->minimap->player_rotation > 0 && game->scene->minimap->player_rotation < 180)
// 	// 	player_path.end.y += 64;
// 	// else if (game->scene->minimap->player_rotation > 180 && game->scene->minimap->player_rotation < 360)
// 	// 	player_path.end.y -= 64;
// 	while (check_wall_intersection(&player_path, game) != 0 && player_path.end.x > 0 && player_path.end.y > 0)
// 	{
// 		player_path.end.x -= iteration_distance;
// 		printf("1value before y_iter %f\n", player_path.end.y);
		
// 		player_path.end.y -= y_iter;
// 		printf("2value after y_iter %f\n", player_path.end.y);
// 	}
// 	return (player_path);
// }
//----------------------------------

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

