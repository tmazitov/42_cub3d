/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/16 23:17:35 by kshamsid         ###   ########.fr       */
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
	printf("STARTING RENDER\n");

	t_line	temp;
	temp.start.x = 0;
	temp.start.y = 0;
	temp.end.x = 1920;
	temp.end.y = 0;
	
	while (temp.end.y < game->height)
	{
		if (temp.end.y < game->height / 2)
			img_put_line(game->scene->image, 0xcbf7f7, temp.start, temp.end);
		else
			img_put_line(game->scene->image, 0x454545, temp.start, temp.end);
		temp.end.y++;
		temp.start.y++;
	}

	
	while (temp_to_rotate < 45)
	{
		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
		if (ray)
		{
			distance_from_wall = distance_between_points(ray->start, ray->end);

			// Correct the fisheye effect by multiplying with the cosine of the angle difference
			distance_from_wall *= cos(temp_to_rotate * M_PI / 180);

			// Calculate wall height based on distance
			render_y = (game->height * 64) / distance_from_wall;
			display_coordinates.start.x = render_x;
			display_coordinates.start.y = (game->height / 2) - (render_y / 2);
			display_coordinates.end.x = render_x;
			display_coordinates.end.y = (game->height / 2) + (render_y / 2);

			// Draw the wall slice
			img_put_line(game->scene->image, 0x9c254f, display_coordinates.start, display_coordinates.end);

			// Optionally draw a floor and ceiling
			// Draw ceiling
			// if (display_coordinates.start.y > 0)
			// 	img_fill_rectangle(game->scene->image, 0x87CEEB, render_x, 0, 1, display_coordinates.start.y);

			// Draw floor
			// if (display_coordinates.end.y < game->height)
			// 	img_fill_rectangle(game->scene->image, 0x8B4513, render_x, display_coordinates.end.y, 1, game->height - display_coordinates.end.y);

			free_line(ray);
		}
		temp_to_rotate += (90.0 / 1920.0);  // Adjust the angle increment to cover the FOV properly
		render_x++;
		if (render_x == 1920)
			break;
	}
	printf("ENDING RENDER\n");
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
		return (printf("ERROR SOETHING RONG"), '1');
	
	// return (game->scene->map->map_double_array[(int)round(ray.end.y)][(int)round(ray.end.x)]);
	return (game->scene->map->map_double_array[index_y][index_x]);
}


//Check SOLO why check_wall_interaction doesnt respond as it should
			// perhaps because i am too percise with the walls and
			// they dont count as LINE INTERSECTIONS
//Texture identification and putting using 
/*

*/