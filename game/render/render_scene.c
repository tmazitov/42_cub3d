/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/12 23:41:20 by kshamsid         ###   ########.fr       */
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


//Using the angle of the player, calculates the delta X
//Delta Y is always 64.
static float find_dx(float dy, float degree, t_game *game)
{
	float deg_to_pie;
	float temp;

	deg_to_pie = degree * PI / 180.0;
	temp = dy/tan(deg_to_pie);
	// printf("game->scene->minimap->player_pos.x %f\n", game->scene->minimap->player_pos.x);
	//print player rotation
	// printf("player rotation %f\n", game->scene->minimap->player_rotation);
	if (game->scene->minimap->player_pos.x - temp < 0)
		return (game->scene->minimap->player_pos.x);
	else if (game->scene->minimap->player_pos.x + temp > 1920)
		return (1920 - game->scene->minimap->player_pos.x);
	else
		return (temp);
	// return ((dy * sin(deg_to_pie))/ cos(deg_to_pie));
}

// static float find_dy(float dy, float degree, t_game *game)
// {
// 	float deg_to_pie;
// 	float temp;

// 	if (degree == 0 || degree == 180)
// 		return (0);
// 	else if (degree == 90 || degree == 270)
// 		return (64);
// 	deg_to_pie = degree * PI / 180.0;
// 	temp = dy/tan(deg_to_pie);
// 	if (game->scene->minimap->player_pos.x - temp < 0)
// 		return (game->scene->minimap->player_pos.x);
// 	else if (game->scene->minimap->player_pos.x + temp > 1920)
// 		return (1920 - game->scene->minimap->player_pos.x);
// 	else
// 		return (temp);
// 	// return ((dy * sin(deg_to_pie))/ cos(deg_to_pie));
// }

float distance_between_points(t_point point)
{
    return sqrt(point.x * point.x + point.y * point.y);
}

t_line	ray_line_getter(t_game *game, float chosen_rotation)
{
	t_point	ray_position;
	float	ray_y;
	float	ray_x;
	float	arctan;
	float	y_iteration;
	float	x_iteration;
	
	t_line	ray;
	arctan = atan(chosen_rotation);
	ray_position = game->scene->minimap->player_pos;
	if (chosen_rotation > 180)
	{
		ray_y = fmod(ray_position.y, 64.0) - 0.00001;
		ray_x = (game->scene->minimap->player_pos.y - ray_y) * tan(arctan) + game->scene->minimap->player_pos.x;
		y_iteration = -64;
		x_iteration = y_iteration / tan(arctan);
	}
	if (chosen_rotation < 180)
	{
		ray_y = fmod(ray_position.y, 64.0) + 64;
		ray_x = (game->scene->minimap->player_pos.y - ray_y) * tan(arctan) + game->scene->minimap->player_pos.x;
		y_iteration = 64;
		x_iteration = y_iteration / tan(arctan);
	}
	//FIXING CODE BELOW IN IF 
	if (chosen_rotation == 0 || chosen_rotation == 180)
	{
		ray_y = game->scene->minimap->player_pos.y;
		ray_x = game->scene->minimap->player_pos.x;
		y_iteration = 0;
		x_iteration = 64;
	}
	ray.start = game->scene->minimap->player_pos;
	ray.end = ray_position;
	return ()
}

// void	render_scene(t_game *game)
//----------------------------------
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
// 	else if (game->scene->minimap->player_rotation > 180 && game->scene->minimap->player_rotation < 360)
// 		distance_to_itersec_y = 64 - fmod(player_path.end.y, 64.0);
// 	iteration_distance = 64;
// 	// printf("distance to intersection mini_DY = %f\n", distance_to_itersec_y);
// 	dx_value = find_dx(distance_to_itersec_y, chosen_rotation, game);
// 	// iteration_distance = find_dx((float)64, chosen_rotation, game);
// 	// printf("iteration distance of DX %f\n", iteration_distance);
// 	player_path.end.x -= dx_value;
// 	player_path.end.y -= distance_to_itersec_y;
// 	// if (game->scene->minimap->player_rotation > 0 && game->scene->minimap->player_rotation < 180)
// 	// 	player_path.end.y += 64;
// 	// else if (game->scene->minimap->player_rotation > 180 && game->scene->minimap->player_rotation < 360)
// 	// 	player_path.end.y -= 64;
// 	while (check_wall_intersection(&player_path, game) != 0 && player_path.end.x > 0 && player_path.end.y > 0)
// 	{
// 		player_path.end.x -= iteration_distance;
// 		player_path.end.y -= 64;
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

