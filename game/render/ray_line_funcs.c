/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_line_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/20 20:27:56 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

//create me a function to convert

// static void draw_all_line(t_game *game, t_line *line, int color)
// {
// 	t_point rel_p1;
// 	t_point	rel_p2;
// 	t_image	*minimap;

// 	minimap = game->scene->minimap->image;
	
// 	rel_p1.x = line->start.x / 4 + MINIMAP_BORDER_SIZE;
// 	rel_p1.y = line->start.y / 4 + MINIMAP_BORDER_SIZE;
// 	rel_p2.x = line->end.x / 4 + MINIMAP_BORDER_SIZE;
// 	rel_p2.y = line->end.y / 4 + MINIMAP_BORDER_SIZE;

// 	img_put_line(minimap, color, rel_p1, rel_p2);
// }

// static int	check_wall_intersection(t_line *player_path, t_game *game, t_direction direction)
// {
// 	t_line			*wall_line;
// 	t_wall_node		*node;
// 	int				is_intersect;

// 	// printf("\t player path %f %f %f %f\n", player_path->start.x, player_path->start.y, player_path->end.x, player_path->end.y),
// 	node = game->scene->map->walls->start;
// 	while(node)
// 	{
// 		if (node->wall->direction == direction)
// 			wall_line = wall_to_line(node->wall);
// 		else
// 			wall_line = wall_to_direction_line(node->wall, direction);
// 		if (!wall_line)
// 		{
// 			node = node->next;
// 			continue ;
// 		}
// 		is_intersect = check_intersection(player_path, wall_line);
// 		if (is_intersect)
// 		{
// 			// draw_all_line(game, wall_line, 0x860e99);
// 			return (1);
// 		}
// 		else if (0)
// 			draw_all_line(game, wall_line, 0xf1f516);
// 		node = node->next;
// 	}
// 	// printf("\t no intersect\n");
// 	return (0);
// }


#include <sys/time.h>
void	print_time_since_last_call()
{
	static struct	timeval last_time;
	struct timeval			current_time;
	long int				elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_usec - last_time.tv_usec) / 1000;
	// printf("Elapsed time: %ld ms\n", elapsed_time);
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

//NEW MODIFICATION
t_line	*ray_line_getter_x(t_game *game, float angle_in_degrees)
{
	float	y_iteration;	//y_iteration in while loop
	float	x_iteration;	//x_iteration in while loop
	int		iterations;	//Like a Counter for block iterations to find the wall.
	float	angle_in_pie;	//angle in radians.
	t_direction direction;
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
	if (angle_in_degrees > 0 && angle_in_degrees < 180)//Looking UPP
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x - (fmod(ray->start.y, 64.0) / tan(angle_in_pie)), \
			ray->start.y - fmod(ray->end.y, 64.0));
		y_iteration = -64;
		x_iteration = y_iteration / tan(angle_in_pie);
		direction = NORTH;
	}
	else if (angle_in_degrees > 180 && angle_in_degrees < 360) // Looking DOWNN
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x + ((64 - fmod(ray->start.y, 64.0)) / tan(angle_in_pie)), \
			ray->start.y - fmod(ray->end.y, 64.0) + 64);
		y_iteration = 64;
		// if (angle_in_degrees > 90 && angle_in_degrees < 180)
		// 	y_iteration = y_iteration * tan(angle_in_pie);
		// else
			x_iteration = y_iteration / tan(angle_in_pie);
		direction = SOUTH;
	}
	if (angle_in_degrees == 0 || angle_in_degrees == 180)
	{
		// printf("0 or 180 ERROR CASE, freeing");
		return (free_line(ray));
	}
	t_point save;
	iterations = 0;

	while (
		get_array_map_value(*ray, game) != '1' &&
		ray->end.x > 0
		&& ray->end.y > 0 && iterations < 10)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->end.x + x_iteration, \
			ray->end.y + y_iteration);
		// if ((get_array_map_value(*ray, game) == '1' && 
		// 	(angle_in_degrees > 0 && angle_in_degrees < 180)) ||
		// 	(ray->end.x < 0 || ray->end.y < 0))
		// {
		// 			line_update(ray, \
		// 	ray->start.x, ray->start.y, \
		// 	ray->end.x - x_iteration, \
		// 	ray->end.y - y_iteration);
		// 	// return (free_line(ray), NULL);
		// 	return (ray);
		// }
		// if (check_wall_intersection(ray, game, direction) != 0)
		// {
		// 	line_update(ray, \
		// 		ray->start.x, ray->start.y, \
		// 		ray->end.x - x_iteration, \
		// 		ray->end.y - y_iteration);
		// 	return (ray); 
		// }
		iterations++;
		save = ray->end;
	}
	// if (iterations == 3)
	// {
	// 	printf("ERROR: 3 iterations reached\n");
	// 	return (free_line(ray));
	// }
	// ray->end = save;
	// printf("player ANGLE  = %f\n", angle_in_degrees);
	// if (angle_in_degrees > 0 && angle_in_degrees < 180)
	// {
	// 	if (angle_in_degrees > 180 &&  angle_in_degrees < 360)
	// 		ray->end.x -= x_iteration;
	// 	else
	// 		ray->end.x += x_iteration;
	// if (check_wall_intersection(ray, game) != 0)
	// {
	// 	printf("Wall was HIT going reverse\n");
	// 	ray->end.y -= y_iteration;
	// 	ray->end.x -= x_iteration;
	// }
	// 	line_update_by_points(ray, ray->start, ray->end);
	// }
	// printf("value of BLOCK = %c\n", get_array_map_value(*ray, game));
	// ray->length = distance_between_points(ray->start, ray->end);
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
	t_direction	direction;

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
		|| (angle_in_degrees >= 0 && angle_in_degrees < 90))//LOOKING LEFT
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x - fmod(ray->end.x, 64.0), \
			ray->start.y - (fmod(ray->start.x, 64.0) * tan(angle_in_pie)));
		x_iteration = -64;
		y_iteration = x_iteration * tan(angle_in_pie);
		direction = WEST;
	}
	else if (angle_in_degrees > 90 && angle_in_degrees < 270)//LOOKING RIGHT
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->start.x - fmod(ray->end.x, 64.0) + 64, \
			ray->start.y + ((64 - fmod(ray->start.x, 64.0)) * tan(angle_in_pie)));
		x_iteration = 64;
		direction = EAST;
		// if (angle_in_degrees > 90 && angle_in_degrees < 180)
		// 	y_iteration = x_iteration * tan(angle_in_pie);
		// else
			y_iteration = x_iteration * tan(angle_in_pie);
	}
	else if (angle_in_degrees == 90 || angle_in_degrees == 270)
	{
		// printf("90 or 270 ERROR CASE, freeing");
		return (free_line(ray));
	}
	t_point save;
	iterations = 0;
	while (
		get_array_map_value(*ray, game) != '1' &&
		ray->end.x > 0
		&& ray->end.y > 0 && iterations < 10)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->end.x + x_iteration, \
			ray->end.y + y_iteration);
		// if ((((angle_in_degrees > 270 && angle_in_degrees <= 360)
		// || (angle_in_degrees >= 0 && angle_in_degrees < 90))
		// && (get_array_map_value(*ray, game) == '1')) ||
		// 	(ray->end.x < 0 || ray->end.y < 0))
		// {
		// 			line_update(ray, \
		// 	ray->start.x, ray->start.y, \
		// 	ray->end.x - x_iteration, \
		// 	ray->end.y - y_iteration);
		// 	// return (free_line(ray), NULL);
		// 	return (ray);
		// }
		// if (check_wall_intersection(ray, game, direction) != 0)
		// {
		// 	line_update(ray, \
		// 		ray->start.x, ray->start.y, \
		// 		ray->end.x - x_iteration, \
		// 		ray->end.y - y_iteration);
		// 	break ;
		// }
		iterations++;
		save = ray->end;
	}
	// ray->end = save;
	// printf("player ANGLE  = %f\n", angle_in_degrees);
	// if (angle_in_degrees > 0 && angle_in_degrees < 180)
	// {
	// 	if (angle_in_degrees > 180 &&  angle_in_degrees < 360)
	// 		ray->end.x -= x_iteration;
	// 	else
	// 		ray->end.x += x_iteration;
	// if (check_wall_intersection(ray, game) != 0)
	// {
	// 	printf("Wall was HIT going reverse\n");
	// 	ray->end.y -= y_iteration;
	// 	ray->end.x -= x_iteration;
	// }
		// line_update_by_points(ray, ray->start, ray->end);
	// }
	// printf("value of BLOCK = %c\n", get_array_map_value(*ray, game));
	// ray->length = distance_between_points(ray->start, ray->end);
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
		return (free_line(intersect_vertical), intersect_horizontal); // added free
	else
		return (free_line(intersect_horizontal), intersect_vertical); // added free
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

