/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/19 22:12:34 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

//create me a function to convert

//Func to INIT image of Scene
/*

*/

//Func to FILL it with another IMAGE for floor and the sky
/*

*/

//Func to EDIT the IMAGE 
/*


*/

// int	displacement_calculation(float distance)


#include <sys/time.h>
void	print_time_since_last_call();
// {
// 	static struct	timeval last_time;
// 	struct timeval			current_time;
// 	long int				elapsed_time;

// 	gettimeofday(&current_time, NULL);
// 	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_usec - last_time.tv_usec) / 1000;
// 	printf("Elapsed time: %ld ms\n", elapsed_time);
// 	last_time = current_time;
// }

void	render_window_scene(t_game *game)
{
	float	temp_to_rotate = -45;
	float	distance_from_wall;
	int		render_x;
	int 	render_y;
	
	t_line	*ray;
	t_line	display_coordinates;

	img_clear(game->scene->image);
	render_x = 0;
	// printf("STARTING RENDER\n");

	t_line	temp;
	temp.start.x = 0;
	temp.start.y = 0;
	temp.end.x = 1920;
	temp.end.y = 0;
	
	//puts sky and floor color
	// while (temp.end.y < game->height)
	// {
	// 	if (temp.end.y < game->height / 2)
	// 		img_put_line(game->scene->image, 0xcbf7f7, temp.start, temp.end);
	// 	else
	// 		img_put_line(game->scene->image, 0x454545, temp.start, temp.end);
	// 	temp.end.y++;
	// 	temp.start.y++;
	// }
	
	//Testing time it takes to put 1920 lines of 1080 pixels -----Test [1]
	// t_line test;
	// print_time_since_last_call();
	// test.start.x = 0;
	// test.start.y = 0;
	// test.end.x = 1920;
	// test.end.y = 1080;	
	// while (test.start.x <= 1920)
	// {
	// 	img_put_line(game->scene->image, 0xcbf7f7, test.start, test.end);
	// 	test.start.x++;
	// 	test.end.x++;
	// }
	// img_draw(game->window, game->scene->image, 0, 0);
	// print_time_since_last_call();
	// exit(1);

	//TESTING Time it takes 1920*1080 SINGLE pixel puts-------------Test [2]
	int temp_num;
	print_time_since_last_call();
	temp_num = 1920 * 1080;
	int temp_x = 0;
	int temp_y = 0;
	printf("temp_num %d\n", temp_num);

	while (temp_num > 0)
	{
		img_put_pixel(game->scene->image, 0xcbf7f7, 1080, 1080);
		temp_num--;
		temp_x++;
		if (temp_x == 1920)
		{
			temp_x = 0;
			temp_y++;
		}
	}
	img_draw(game->window, game->scene->image, 0, 0);
	print_time_since_last_call();
	exit(1);

	while (temp_to_rotate < 45)
	{
		printf("starting render\n");
		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
		if (ray)
		{
			distance_from_wall = distance_between_points(ray->start, ray->end);

			printf("all values %f %f %f %f\n", display_coordinates.start.x, display_coordinates.start.y, display_coordinates.end.x, display_coordinates.end.y);
			fflush(stdout);
			// Correct the fisheye effect by multiplying with the cosine of the angle difference
			distance_from_wall *= cos(temp_to_rotate * M_PI / 180);

			// Calculate wall height based on distance
			// printf("render y components HEIGHT = %d DIS FROM WALL = %f\n", game->height, distance_from_wall);
			// if (distance_from_wall == 0 || distance_from_wall > 1000)
			// 	// distance_from_wall < -1000)
			// {
			// 	free_line(ray);
			// 	continue;
			// 	// render_y = game->height;
			// }	
			// else
				render_y = (game->height * 64) / distance_from_wall;
			display_coordinates.start.x = render_x;
			display_coordinates.start.y = (game->height / 2.5) - (render_y / 2);
			display_coordinates.end.x = render_x;
			display_coordinates.end.y = (game->height / 2) + (render_y / 2);
			if (display_coordinates.start.y > 1000 || display_coordinates.start.y < -1000 ||
				display_coordinates.end.y > 1000 || display_coordinates.end.y < -1000)
			{
				display_coordinates.start.y = 0;
				display_coordinates.end.y = 0;
			}
			// printf("game->height %d\n", game->height);
			// printf("render_y %d\n", render_y);

			// Draw the wall slice
			if (display_coordinates.start.x <= 1080 ||
				display_coordinates.start.y <= 1920 ||
				display_coordinates.end.x <= 1920 ||
				display_coordinates.end.y <= 1080)
			{
				img_put_line(game->scene->image, 0x9c254f, display_coordinates.start, display_coordinates.end);
			}
			// printf("after check\n");
			// Optionally draw a floor and ceiling
			// Draw ceiling
			// if (display_coordinates.start.y > 0)
			// 	img_fill_rectangle(game->scene->image, 0x87CEEB, render_x, 0, 1, display_coordinates.start.y);

			// Draw floor
			// if (display_coordinates.end.y < game->height)
			// 	img_fill_rectangle(game->scene->image, 0x8B4513, render_x, display_coordinates.end.y, 1, game->height - display_coordinates.end.y);

			free_line(ray);
		}
		temp_to_rotate += (90.0 / (1920.0));  // Adjust the angle increment to cover the FOV properly
		// temp_to_rotate += (90.0 / 485.0);  // Adjust the angle increment to cover the FOV properly
		render_x += 1;
		if (render_x == 1920 || render_y == 0)
			break;
	}
	print_time_since_last_call();
	// printf("ENDING RENDER\n");
	
	img_draw(game->window, game->scene->image, 0, 0);
}


// void	render_window_scene(t_game *game)
// {
// 	float	temp_to_rotate = -45;
// 	float	distance_from_wall;
// 	int		render_x;
// 	int 	render_y;
	
// 	// int		displace;

// 	t_line	*ray;
// 	t_line	display_coordinates;

// 	img_clear(game->scene->image);
// 	render_x = 0;
// 	printf("STARTING RENDER\n");
// 	while (temp_to_rotate < 45)
// 	{
// 		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
// 		// ray = ray_line_getter_y(game, game->scene->minimap->player_rotation + temp_to_rotate);
// 		// ray = ray_line_getter_x(game, game->scene->minimap->player_rotation + temp_to_rotate);
// 		if (ray)
// 		{
// 			distance_from_wall = distance_between_points(ray->start, ray->end);
// 			render_y = (game->scene->map->height * 64) / distance_from_wall;
// 			display_coordinates.start.x = render_x;
// 			display_coordinates.start.y = (game->height / 2) - (render_y / 2);
// 			display_coordinates.end.x = render_x;
// 			display_coordinates.end.y = (game->height / 2) + (render_y / 2);
// 			img_put_line(game->scene->image, 0x34ebbd, display_coordinates.start
// 				, display_coordinates.end);

// 			// img_put_pixel(game->scene->image, 0xe62e31, ray->start.x, ray->start.y);
// 			// img_get_pixel()
// 			t_line test;

// 			test.start.x = 0;
// 			test.start.y = 0;
// 			test.end.x = 800;
// 			test.end.y = 800;

// 			img_put_line(game->scene->image, 0xe62e31, test.start, test.end);
// 			// img_put_line(game->scene->image, 0xe62e31, ray->start, ray->end);
// 			free_line(ray);
// 		}
// 		// printf("RENDERING %d\n", render_x);
// 		temp_to_rotate += (90 / 1920);
// 		render_x++;
// 		if (render_x == 1920)
// 			break;
// 	}
// 	printf("ENDING RENDER\n");
// 	img_draw(game->window, game->scene->image, 0, 0);
// }

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
		return (/*printf("ERROR SOETHING RONG"),*/ '1');
	
	// return (game->scene->map->map_double_array[(int)round(ray.end.y)][(int)round(ray.end.x)]);
	return (game->scene->map->map_double_array[index_y][index_x]);
}


//Check SOLO why check_wall_interaction doesnt respond as it should
			// perhaps because i am too percise with the walls and
			// they dont count as LINE INTERSECTIONS
//Texture identification and putting using 
/*

*/