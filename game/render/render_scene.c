/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/12 22:09:08 by kshamsid         ###   ########.fr       */
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

	if (degree == 0 || degree == 180)
		return (0);
	else if (degree == 90 || degree == 270)
		return (64);
	deg_to_pie = degree * PI / 180.0;
	temp = dy/tan(deg_to_pie);
	if (game->scene->minimap->player_pos.x - temp < 0)
		return (game->scene->minimap->player_pos.x);
	else if (game->scene->minimap->player_pos.x + temp > 1920)
		return (1920 - game->scene->minimap->player_pos.x);
	else
		return (temp);
	// return ((dy * sin(deg_to_pie))/ cos(deg_to_pie));
}

// void	render_scene(t_game *game)
t_line	ray_line_getter(t_game *game, float chosen_rotation)
{
	float	distance_to_itersec_y;
	float	dx_value;
	float	iteration_distance;
	t_line	player_path;

	player_path.start = game->scene->minimap->player_pos;
	player_path.end = game->scene->minimap->player_pos;
	distance_to_itersec_y = fmod(player_path.end.y, 64.0);
	iteration_distance = 64;
	// printf("distance to intersection mini_DY = %f\n", distance_to_itersec_y);
	dx_value = find_dx(distance_to_itersec_y, chosen_rotation, game);
	iteration_distance = find_dx((float)64, chosen_rotation, game);
	// printf("iteration distance of DX %f\n", iteration_distance);
	player_path.end.x -= dx_value;
	player_path.end.y -= distance_to_itersec_y;

	if (player_path.start.y < player_path.end.y)
		player_path.end.y += 1;
	else if (player_path.start.y > player_path.end.y)
		player_path.end.y -= 1;

	while (check_wall_intersection(&player_path, game) != 0 && player_path.end.x > 0 && player_path.end.y > 0)
	{
		printf("---------\n");
		printf("---------\n");
		printf("---------\n");
		printf("---------\n");
		printf("---------\n");
		printf("---------\n");
		player_path.end.x -= iteration_distance;
		player_path.end.y -= 64;
	}
	return (player_path);
	//Deviding values to on TEMP to print on minimap;
	// player_path.end.x /= 4;
	// player_path.end.y /= 4;
	// player_path.start.x /= 4;
	// player_path.start.y /= 4;
	// printf("player path %f %f %f %f\n", player_path.start.x, player_path.start.y, player_path.end.x, player_path.end.y);
	// img_put_line(game->scene->minimap->image, 0x00FF00, player_path.start, player_path.end);

	// //Line print test with FIXED values.
	// t_point print_test;
	// print_test.x = 0;
	// print_test.y = 0;
	// t_point print_test_1;
	// print_test_1.x = 100;
	// print_test_1.y = 100;
	// img_put_line(game->scene->minimap->image, 0x0F0F0F, print_test, print_test_1);
}

	//Calculate distance to Cross Section.

	//Put line according to distance
	//Iterate Over to the next Cross Section.
	//take value x4 and check for the value in the type of wall. NO SO EA WE
	//Draw vertical line depending on distance from wall.
	//Max height == height of the screen.
	
	// render_minimap(game);
	// render_3d(game);

/*
Get distance to the wall to the player
*/
// void	calculate_distance()
// {

// }

// int get_next_vertical_pixel()
// {

// }

