/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/25 19:23:09 by kshamsid         ###   ########.fr       */
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

// // 2 DARKER COLOR FUNCTIONS
// int clamp(int value, int min, int max) {
//     if (value < min) return min;
//     if (value > max) return max;
//     return value;
// }

// // Function to darken a color based on distance
// uint32_t darken_color(uint32_t color, double min_distance, double max_distance, double current_distance) {
//     // Extract RGB components from hex color
//     uint8_t red = (color >> 16) & 0xFF;
//     uint8_t green = (color >> 8) & 0xFF;
//     uint8_t blue = color & 0xFF;

//     // Calculate the darkening factor based on the distance
//     double factor = 1.0 - (current_distance - min_distance) / (max_distance - min_distance);
//     factor = clamp(factor, 0.0, 1.0);

//     // Apply the darkening factor to each color component
//     red = (uint8_t)(red * factor);
//     green = (uint8_t)(green * factor);
//     blue = (uint8_t)(blue * factor);

//     // Combine the components back into a single hex color
//     return (red << 16) | (green << 8) | blue;
// }

double clamp_double(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Function to darken a color based on distance
uint32_t darken_color(uint32_t color, double min_distance, double max_distance, double current_distance) {
    // Extract RGB components from hex color
    uint8_t red = (color >> 16) & 0xFF;
    uint8_t green = (color >> 8) & 0xFF;
    uint8_t blue = color & 0xFF;

    // Handle case when min_distance equals max_distance
    if (min_distance == max_distance)
	{
        min_distance -= 1.0;  // Set a very small range to avoid division by zero
    }

    // Calculate the darkening factor based on the distance
    double factor = 1.0 - (current_distance - min_distance) / (max_distance - min_distance);
    factor = clamp_double(factor, 0.0, 1.0);

    // Apply the darkening factor to each color component
    red = (uint8_t)(red * factor);
    green = (uint8_t)(green * factor);
    blue = (uint8_t)(blue * factor);

    // Combine the components back into a single hex color
    return (red << 16) | (green << 8) | blue;
}

// Basic checks for < 0 && > window dimensions
void	line_value_adjust(t_game *game, t_line *line)
{
	if (line->start.x > game->width)
		line->start.x = game->width;
	if (line->start.y > game->height)
		line->start.y = game->height;
	if (line->start.x < 0)
		line->start.x = 0;
	if (line->start.y < 0)
		line->start.y = 0;
	if (line->end.x > game->width)
		line->end.x = game->width;
	if (line->end.y > game->height)
		line->end.y = game->height;
	if (line->end.x < 0)
		line->end.x = 0;
	if (line->end.y < 0)
		line->end.y = 0;
}

void	draw__middle_aim(t_game *game)
{
	t_point	screen_center;
	int		aim_size;
	int		draw_aim;

	aim_size = AIM_SIZE;
	screen_center.x = game->width / 2;
	screen_center.y = (float)game->height / 2;
	draw_aim = aim_size / 2;
	draw_aim = -draw_aim;
	while (draw_aim < aim_size / 2)
	{
		img_put_pixel(game->scene->image, 0x98b9ed, screen_center.x + draw_aim, screen_center.y);
		img_put_pixel(game->scene->image, 0x98b9ed, screen_center.x, screen_center.y + draw_aim);
		draw_aim++;
	}
}

	// t_line	temp;
	// temp.start.x = 0;
	// temp.start.y = 0;
	// temp.end.x = 1920;
	// temp.end.y = 0;

	// // puts sky and floor color
	// while (temp.end.y < game->height)
	// {
	// 	if (temp.end.y < game->height / 2)
	// 	{
	// 		int i = 0;
	// 		while (i < game->width)
	// 		{
	// 			img_put_pixel(game->scene->image, 0x011421, i, temp.end.y);
	// 			i++;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		int i = 0;
	// 		while (i < game->width)
	// 		{
	// 			img_put_pixel(game->scene->image, 0x191a19, i, temp.end.y);
	// 			i++;
	// 		}
	// 	}
	// 	temp.end.y++;
	// 	temp.start.y++;
	// }

static void adjust_disp_coords(t_line *disp_coords, t_game *game, int rend_x, int rend_y)
{
	disp_coords->start.x = rend_x;
	disp_coords->start.y = (game->height / 2.0) - (rend_y / 2);
	disp_coords->end.x = rend_x;
	disp_coords->end.y = (game->height / 2) + (rend_y / 2);
}

static int get_vert_of_texture(t_point ray_end, float angle_ray)
{
	// float player_angle = game->scene->minimap->player_rotation;
	if (angle_ray < 0)
		angle_ray += 360;
	if (angle_ray > 360)
		angle_ray -= 360;
	ray_end.x = round(fmod(ray_end.x, 64));
	ray_end.y = round(fmod(ray_end.y, 64));
	if (ray_end.x == 64)
		ray_end.x = 0;
	if (ray_end.y == 64)
		ray_end.y = 0;
	if (ray_end.x == 0)
	{
		if ((angle_ray > 270 && angle_ray <= 360)
			|| (angle_ray >= 0 && angle_ray < 90))
			return (63 - ray_end.y);
		else
			return (ray_end.y);
	}
	else if (ray_end.y == 0)
	{
		if (angle_ray > 180 && angle_ray < 360)
			return (63 - ray_end.x);
		return (ray_end.x);
	}
	return (-1);
}

void	render_window_scene(t_game *game)
{
	float	player_fov = 90;
	float	temp_to_rotate;
	float	distance_from_wall;
	t_point	screen_render;
	t_line	*ray;
	t_line	display_coordinates;

	img_clear(game->scene->image);
	player_fov = PLAYER_FOV;
	screen_render.x = 0;
	screen_render.y = 0;
	temp_to_rotate = -player_fov / 2;

	// float test;
	// test = 64;

	// test = round(fmod(test, 64));
	// printf("test = %f\n", test);
	// exit(1);

	t_sprite_node *temp_sprite = get_sprite_by_name(game->scene->map->sprites, "NO");
	t_image *temp_image = temp_sprite->image;
	while (temp_to_rotate < player_fov / 2)
	{
		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
		if (ray)
		{
			// float	vert_height = display_coordinates.end.y - display_coordinates.start.y;
			distance_from_wall = distance_between_points(ray->start, ray->end);
			distance_from_wall *= cos(temp_to_rotate * M_PI / 180);
			screen_render.y = (game->height * 64) / distance_from_wall;
			adjust_disp_coords(&display_coordinates, game, screen_render.x, screen_render.y);

			float	vert_height = display_coordinates.end.y - display_coordinates.start.y;
			float	vert_iter = 64 / vert_height; //VERT HEIGHT = 128 // ITER = 2
			float	y_offsett = 0;
			if (vert_height > game->height)
			{
				y_offsett = (vert_height - game->height) / 2;
				vert_height = game->height;
			}
			line_value_adjust(game, &display_coordinates);

			int		texture_x_pos = get_vert_of_texture(ray->end, game->scene->minimap->player_rotation + temp_to_rotate); // gotten texture y pos
			float	texture_y_pos = y_offsett * vert_iter; // gotten texture y pos
			while (display_coordinates.start.y < display_coordinates.end.y)// PUTS VERTICAL TEXUTURED LINE
			{
				img_put_pixel(game->scene->image, darken_color(img_get_pixel(temp_image, texture_x_pos, texture_y_pos),
					SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE, distance_from_wall),
					display_coordinates.start.x, display_coordinates.start.y);
				display_coordinates.start.y++;
				texture_y_pos += vert_iter;
			}
			// while (display_coordinates.start.y < game->height) // PUTS FLOOR
			// {
			// 	img_put_pixel(game->scene->image, 0x000000, display_coordinates.start.x, display_coordinates.start.y);
			// 	display_coordinates.start.y++;
			// }
			// while (display_coordinates.start.y < game->height) // PUTS FLOOR TEXTURES
            // {
            //     float row_distance = (game->height / (2.0 * display_coordinates.start.y - game->height));
            //     float floor_x = game->scene->minimap->player_pos.x + row_distance * cos(temp_to_rotate * M_PI / 180);
            //     float floor_y = game->scene->minimap->player_pos.y + row_distance * sin(temp_to_rotate * M_PI / 180);

            //     int floor_tex_x = (int)(floor_x * 128) % 128;
            //     int floor_tex_y = (int)(floor_y * 128) % 128;

            //     uint32_t floor_color = img_get_pixel(temp_image, floor_tex_x, floor_tex_y);
            //     img_put_pixel(game->scene->image, floor_color, display_coordinates.start.x, display_coordinates.start.y);
            //     display_coordinates.start.y++;
            // }
		temp_to_rotate += (player_fov / (game->width));  // Adjust the angle increment to cover the FOV properly
		screen_render.x += 1;
		if (screen_render.x == game->width || screen_render.y == 0 /*|| screen_render.y > game->height*/)
			break ;
		}
	}
	draw__middle_aim(game);

	print_time_since_last_call();
	// printf("ENDING RENDER\n");
}

//Find end of line equivalent of CHAR in 2d array map
char	get_array_map_value(t_line ray, t_game *game)
{
	int index_y;
	int index_x;

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
	return (game->scene->map->map_double_array[index_y][index_x]);
}
