/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/21 22:32:26 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
		img_put_pixel(game->scene->image, AIM_COLOR, screen_center.x + draw_aim, screen_center.y);
		img_put_pixel(game->scene->image, AIM_COLOR, screen_center.x, screen_center.y + draw_aim);
		draw_aim++;
	}
}

static void adjust_disp_coords(t_line *disp_coords, t_game *game, int rend_x, int rend_y)
{
	disp_coords->start.x = rend_x;
	disp_coords->start.y = (game->height / 2.0) - (rend_y / 2);
	disp_coords->end.x = rend_x;
	disp_coords->end.y = (game->height / 2) + (rend_y / 2);
}

static int get_vert_of_texture(t_point ray_end, float angle_ray)
{
	if (angle_ray <= 0)
		angle_ray += 360;
	if (angle_ray >= 360)
		angle_ray -= 360;
	ray_end.x = round(fmod(ray_end.x, 64));
	ray_end.y = round(fmod(ray_end.y, 64));
	if (ray_end.x == 64)
		ray_end.x = 0;
	if (ray_end.y == 64)
		ray_end.y = 0;
	if (ray_end.x == 0)
	{
		// if (angle_ray > 270 || angle_ray < 90)
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
	return (printf("get_vert_error occured"), 0);
}

typedef struct s_window_walls
{
	t_line	*ray;
	float	distance_from_wall;
	int		width_of_screen;
}	t_window_walls;


#define NONE_COLOR 0xFFFFFFFF  // Assuming 0xFFFFFFFF represents the 'None' color

// //zombie render_scene is below.
/*
	RENDER FUNC that had ISSUE with LOCATION and Angle_to_Sprite
*/
void render_sprite(t_game *game, t_point sprite_pos, t_image *sprite_image, float sprite_distance, float *dist_to_wall_vert_line)
{
	t_point player_pos = game->scene->minimap->player_pos;

	float angle_to_sprite = 0;
	angle_to_sprite = atan2(sprite_pos.y - player_pos.y, sprite_pos.x - player_pos.x) * 180 / M_PI;
	angle_to_sprite -= game->scene->minimap->player_rotation;
	angle_to_sprite += 180;

	// printf("angle_to_sprite = %f\n", angle_to_sprite);
	if (angle_to_sprite < -180)
		angle_to_sprite += 360;
	if (angle_to_sprite > 180)
		angle_to_sprite -= 360;
	if (fabs(angle_to_sprite) < PLAYER_FOV + 10 / 2)
	{
		// Calculate sprite screen size
		float sprite_screen_size = (game->height * 64) / sprite_distance;
		
		// Calculate sprite screen position
		int sprite_screen_x = (int)((game->width / 2) * (1 + tan(angle_to_sprite * M_PI / 180) / tan((PLAYER_FOV / 2) * M_PI / 180)));
		int sprite_screen_y = game->height / 2 - sprite_screen_size / 2;

			// Render the sprite (small square for simplicity)
		for (int x = 0; x < sprite_screen_size; x++)
		{
			for (int y = 0; y < sprite_screen_size; y++)
			{
				int screen_x = sprite_screen_x + x - sprite_screen_size / 2;
				int screen_y = sprite_screen_y + y;
				if (screen_x >= 0 && screen_x < game->width - 1 && sprite_distance < dist_to_wall_vert_line[screen_x] )
				{
					if (screen_x >= 0 && screen_x < game->width && screen_y >= 0 && screen_y < game->height)
					{
						uint32_t color = img_get_pixel(sprite_image, (int)((float)x / sprite_screen_size * sprite_image->width), (int)((float)y / sprite_screen_size * sprite_image->height));
						if (color != (uint32_t)(-16777216))
							img_put_pixel(game->scene->image, darken_color(color, SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE, sprite_distance) , screen_x, screen_y);
					}
				}
			}
		}
	}
	angle_to_sprite = dist_to_wall_vert_line[0];
}

void render_chest(t_game *game, t_point sprite_pos, t_image *sprite_image, float sprite_distance, float *dist_to_wall_vert_line)
{
	t_point player_pos = game->scene->minimap->player_pos;
	
	float angle_to_sprite = 0;
	angle_to_sprite = atan2(sprite_pos.y - player_pos.y, sprite_pos.x - player_pos.x) * 180 / M_PI;
	angle_to_sprite -= game->scene->minimap->player_rotation;
	angle_to_sprite += 180;
	
	// Normalize the angle
	if (angle_to_sprite < -180)
		angle_to_sprite += 360;
	if (angle_to_sprite > 180)
		angle_to_sprite -= 360;

	if (fabs(angle_to_sprite) < PLAYER_FOV + 10 / 2)
	{
		float sprite_screen_size = (game->height * 16) / sprite_distance;

		int sprite_screen_x = (int)((game->width / 2) * (1 + tan(angle_to_sprite * M_PI / 180) / tan((PLAYER_FOV / 2) * M_PI / 180)));
		int sprite_screen_y = (game->height / 2) - (sprite_screen_size / 2)  + ((64 / sprite_distance) * game->height / 2);
		// sprite_screen_y += 100;
			// Render the sprite (small square for simplicity)
			for (int x = 0; x < sprite_screen_size; x++)
			{
				for (int y = 0; y < sprite_screen_size; y++)
				{
					int screen_x = sprite_screen_x + x - sprite_screen_size / 2;
					int screen_y = sprite_screen_y + y;
					if (screen_x >= 0 && screen_x < game->width - 1 && sprite_distance < dist_to_wall_vert_line[screen_x] )
					{
						if (screen_x >= 0 && screen_x < game->width && screen_y >= 0 && screen_y < game->height)
						{
							uint32_t color = img_get_pixel(sprite_image, (int)((float)x / sprite_screen_size * sprite_image->width), (int)((float)y / sprite_screen_size * sprite_image->height));
							if (color != (uint32_t)(-16777216))
								img_put_pixel(game->scene->image, darken_color(color, SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE, sprite_distance) , screen_x, screen_y);
						}
					}
				}
				
			}
	}
	angle_to_sprite = dist_to_wall_vert_line[0];
}

float	calc_dis_for_two_points(t_point zombie_pos, t_point player_pos)
{
	float	dx;
	float	dy;

	dx = zombie_pos.x - player_pos.x;
	dy = zombie_pos.y - player_pos.y;
	return (sqrt(dx * dx + dy * dy));
}

/*
	Adjust RENDER_TEST_ANIMATION with added vars
*/
// static void	render_test_animation(t_game *game, t_point render_pos, int zombie_number, float dist_to_sprite)
// {
// 	t_enemy	*enemy;
// 	t_image	*anime_image;
// 	// t_point	pos;

// 	if (!game->scene->enemies)
// 		return ;
// 	enemy = game->scene->enemies->enemies[zombie_number];
// 	if (!enemy)
// 		return ;
// 	anime_image = anime_current_frame(enemy->move_anime);
// 	if (!anime_image)
// 		return ;


// 	// pos.x = game->width - anime_image->width;
// 	// pos.y = 0;

// 	render_pos.x = render_pos.x - anime_image->width / 2;
// 	render_pos.y = render_pos.y - anime_image->height / 2;
	
//     // printf("angle_to_sprite = %f\n", angle_to_sprite);

// 	// printf("calculate angle = %f\n", calculate_angle(player_pos, sprite_pos));
// 	// exit(1);

//     // if (fabs(angle_to_sprite) < PLAYER_FOV / 2)
// 	// {
	
// 	// float perpendicular_distance = sprite_distance / cos(angle_to_sprite * M_PI / 180);
//     // Calculate sprite screen size
//     float sprite_screen_size = (game->height * 64) / dist_to_sprite;

//     // Calculate sprite screen position
//     int sprite_screen_x = (int)((game->width / 2) * (1 + tan(0 * M_PI / 180) / tan((PLAYER_FOV / 2) * M_PI / 180)));
//     int sprite_screen_y = game->height / 2 - sprite_screen_size / 2;
// 	for (int y = 0; y < anime_image->height; y++)
// 	{
// 		for (int x = 0; x < anime_image->width; x++)
// 		{
// 			int screen_x = sprite_screen_x + x - sprite_screen_size / 2;
// 			int screen_y = sprite_screen_y + y;
// 			uint32_t color = img_get_pixel(anime_image, x, y);
			
// 			if (screen_x >= 0 && screen_x < game->width && screen_y >= 0 && screen_y < game->height)
// 			{
// 				if (color != (uint32_t)(-16777216))
// 					img_put_pixel(game->scene->image, darken_color(color, SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE, dist_to_sprite) , render_pos.x + x, render_pos.y + y);
// 			}
// 			// if ()
// 			// img_put_pixel(game->scene->image, img_get_pixel(anime_image, x, y), render_pos.x + x, render_pos.y + y);
// 		}
// 	}
	
// 	// }
	
	
// 	// img_put_img(game->scene->image, anime_image, render_pos, 0);
// }

/*
	EXPERIMENT FUNC THAT CASTS ON CORRECT POSITION// CORRECT MATRIX
*/

void	draw_chests(t_game *game, float *dist_to_wall_vert_line)
{
	t_treasure_storage *chestz;
	t_point sprite_position;
	t_point player_pos;
	t_point sprite_display_pos;
	float	cos_value; 
	float	sin_value;
	float	z_height_value;

	z_height_value = 100;
	chestz = game->scene->treasures;
	int chestie_iter = 0;	
	while (chestie_iter < chestz->size)
	{
		sprite_position = *chestz->boxes[chestie_iter]->pos;
		player_pos = game->scene->minimap->player_pos;
		sprite_position.x += 32;
		sprite_position.y += 32;

		cos_value = cos(game->scene->minimap->player_rotation * M_PI / 180);
		sin_value = sin(game->scene->minimap->player_rotation * M_PI / 180);
		sprite_display_pos.x = (sprite_position.y - player_pos.y) * cos_value - (sprite_position.x - player_pos.x) * sin_value;
		sprite_display_pos.y = (sprite_position.x - player_pos.x) * cos_value + (sprite_position.y - player_pos.y) * sin_value;
		sprite_display_pos.x = sprite_display_pos.x*(108)/sprite_display_pos.y + 120 / 2;
		sprite_display_pos.y = z_height_value*(108)/sprite_display_pos.y + 80 / 2;

		t_image chest_image;
		if (chestz->items[chestie_iter] == NULL || chestz->items[chestie_iter]->items[0]->amount == 0)
			chest_image = *get_sprite_by_name(game->scene->map->sprites, "TB_EMPTY")->image;
		else
			chest_image = *get_sprite_by_name(game->scene->map->sprites, "TB")->image;
		render_chest(game, sprite_position, &chest_image, calc_dis_for_two_points(sprite_position, player_pos), dist_to_wall_vert_line);
		chestie_iter++;
	}
}

//TRYING TO DRAW FARTHEST TO CLOSEST ZOMBIE
// void	draw_zombie(t_game *game, float *dist_to_wall_vert_line)
// {
// 	t_enemy_storage *zombz;
// 	t_point sprite_position;
// 	t_point player_pos;
// 	t_point sprite_display_pos;
// 	float	cos_value; 
// 	float	sin_value;
// 	float	z_height_value;
// 	t_image	*image;

// 	z_height_value = 100;
// 	zombz = game->scene->enemies;
// 	int zombie_iter = 0;	
	
// 	float temp_dist_to_sprite = 0;
// 	int loop_iter;
// 	int far_zomb = 0;
// 	// temp_dist_to_sprite = INT_MAX;


// 	// while (zombie_iter < zombz->size)
// 	// {
// 	// 	zombie_iter = 0;
// 	// 	sprite_position = *zombz->enemies[zombie_iter]->pos;
// 	// 	player_pos = game->scene->minimap->player_pos;
// 	// 	sprite_position.x += 32;
// 	// 	sprite_position.y += 32;
// 	// 	temp_dist_to_sprite = calc_dis_for_two_points(sprite_position, player_pos)
// 	// 	if (temp_dist_to_sprite)

		
// 	while (zombie_iter < zombz->size)
// 	{
// 		loop_iter = 0;
// 		temp_dist_to_sprite = 0;
// 		while (loop_iter < zombz->size)
// 		{
// 			sprite_position = *zombz->enemies[loop_iter]->pos;
// 			player_pos = game->scene->minimap->player_pos;
// 			sprite_position.x += 32;
// 			sprite_position.y += 32;
// 			// temp_dist_to_sprite = calc_dis_for_two_points(sprite_position, player_pos);
// 			if (temp_dist_to_sprite < calc_dis_for_two_points(*zombz->enemies[loop_iter]->pos, player_pos))
// 				far_zomb = loop_iter;
// 			loop_iter++;
// 		}
// 		sprite_position = *zombz->enemies[far_zomb]->pos;
// 		cos_value = cos(game->scene->minimap->player_rotation * M_PI / 180);
// 		sin_value = sin(game->scene->minimap->player_rotation * M_PI / 180);
// 		sprite_display_pos.x = (sprite_position.y - player_pos.y) * cos_value - (sprite_position.x - player_pos.x) * sin_value;
// 		sprite_display_pos.y = (sprite_position.x - player_pos.x) * cos_value + (sprite_position.y - player_pos.y) * sin_value;
// 		sprite_display_pos.x = sprite_display_pos.x*(108)/sprite_display_pos.y + 120 / 2;
// 		sprite_display_pos.y = z_height_value*(108)/sprite_display_pos.y + 80 / 2;
// 		if (!zombz->enemies[far_zomb]->alive)
// 			image = get_sprite_by_name(game->scene->map->sprites, "ENEMY_DIED")->image;
// 		else
// 			image = enemy_get_image(zombz->enemies[far_zomb]);
// 		render_sprite(game, sprite_position, image, calc_dis_for_two_points(sprite_position, player_pos), dist_to_wall_vert_line);
// 		zombie_iter++;
// 	}
// }


//ORIG?
void	draw_zombie(t_game *game, float *dist_to_wall_vert_line)
{
	t_enemy_storage *zombz;
	t_point sprite_position;
	t_point player_pos;
	// t_point sprite_display_pos;
	// float	cos_value; 
	// float	sin_value;
	// float	z_height_value;
	t_image	*image;

	// z_height_value = 100;
	zombz = game->scene->enemies;
	int zombie_iter = 0;	
	float temp_dist_to_sprite;
	
	// temp_dist_to_sprite = INT_MAX;


	// while (zombie_iter < zombz->size)
	// {
	// 	zombie_iter = 0;
	// 	sprite_position = *zombz->enemies[zombie_iter]->pos;
	// 	player_pos = game->scene->minimap->player_pos;
	// 	sprite_position.x += 32;
	// 	sprite_position.y += 32;
	// 	temp_dist_to_sprite = calc_dis_for_two_points(sprite_position, player_pos)
	// 	if (temp_dist_to_sprite)

	// cos_value = cos(game->scene->minimap->player_rotation * M_PI / 180);
	// sin_value = sin(game->scene->minimap->player_rotation * M_PI / 180);
		
	player_pos = game->scene->minimap->player_pos;
	
	while (zombie_iter < zombz->size)
	{
		sprite_position = *zombz->enemies[zombie_iter]->pos;
		sprite_position.x += 32;
		sprite_position.y += 32;
		temp_dist_to_sprite = calc_dis_for_two_points(sprite_position, player_pos);
		// while ()
		// sprite_display_pos.x = (sprite_position.y - player_pos.y) * cos_value - (sprite_position.x - player_pos.x) * sin_value;
		// sprite_display_pos.y = (sprite_position.x - player_pos.x) * cos_value + (sprite_position.y - player_pos.y) * sin_value;
		// sprite_display_pos.x = sprite_display_pos.x*(108)/sprite_display_pos.y + 120 / 2;
		// sprite_display_pos.y = z_height_value*(108)/sprite_display_pos.y + 80 / 2;
		if (!zombz->enemies[zombie_iter]->alive)
			image = get_sprite_by_name(game->scene->map->sprites, "ENEMY_DIED")->image;
		else
			image = enemy_get_image(zombz->enemies[zombie_iter]);
		render_sprite(game, sprite_position, image, calc_dis_for_two_points(sprite_position, player_pos), dist_to_wall_vert_line);


		zombie_iter++;
	}
}

//ADDING

//func to convert given params in CUB file to color.
uint32_t rgb_to_color(t_rgb color)
{
	uint32_t result;
    // Ensure the RGB values are within the valid range
    if (color.r < 0) color.r = 0;
    if (color.r > 255) color.r = 255;

    if (color.g < 0) color.g = 0;
    if (color.g > 255) color.g = 255;

    if (color.b < 0) color.b = 0;
    if (color.b > 255) color.b = 255;

    // Combine the RGB values into a single 0xRRGGBB format
    result = (color.r << 16) | (color.g << 8) | color.b;

    return (result);
}

int	get_wall_side(float ray_angle, t_point ray_end)
{
	if (ray_angle < 0)
		ray_angle += 360;
	if (ray_angle > 360)
		ray_angle -= 360;
	ray_end.x = (fmod(ray_end.x, 64));
	ray_end.y = (fmod(ray_end.y, 64));
	if (round(ray_end.x) == 64)
		ray_end.x = 0;
	if (round(ray_end.y) == 64)
		ray_end.y = 0;
	if (ray_angle >= 0 && ray_angle < 180 && ray_end.y == 0)
		return (0);
	else if (ray_angle >= 180 && ray_angle < 360 && ray_end.y == 0)
		return (1);
	else if ((ray_angle >= 270 || ray_angle < 90) && ray_end.x == 0)
		return (2);
	else if (ray_angle >= 90 && ray_angle < 270 && ray_end.x == 0)
		return (3);
	return (0);
}

//ZOMBIE ADD TRYING, zombie func above.
void render_window_scene(t_game *game)
{
	float player_fov = 90;
	float temp_to_rotate;
	float distance_from_wall;
	t_point screen_render;
	t_line *ray;
	t_line display_coordinates;

	float	dist_to_wall_vert_line[game->width];
	int		vert_wall_iter = 0;
	img_clear(game->scene->image);

	player_fov = PLAYER_FOV;
	screen_render.x = 0;
	screen_render.y = 0;
	temp_to_rotate = -player_fov / 2;

	t_image temp_image[4];
	temp_image[0] = *get_sprite_by_name(game->scene->map->sprites, "NO")->image;
	temp_image[1] = *get_sprite_by_name(game->scene->map->sprites, "SO")->image;
	temp_image[2] = *get_sprite_by_name(game->scene->map->sprites, "WE")->image;
	temp_image[3] = *get_sprite_by_name(game->scene->map->sprites, "EA")->image;

	//Need a function and a int var to get the value of the sprite that we need to render 0-4
	int wall_select = 0;

	uint32_t ceiling_color = rgb_to_color(*get_sprite_by_name(game->scene->map->sprites, "C")->color);
	uint32_t floor_color = rgb_to_color(*get_sprite_by_name(game->scene->map->sprites, "F")->color);
	while (temp_to_rotate < player_fov / 2)
	{
		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
		wall_select = get_wall_side(game->scene->minimap->player_rotation + temp_to_rotate, ray->end);
		dist_to_wall_vert_line[vert_wall_iter] = distance_between_points(ray->start, ray->end);
		if (ray)
		{
			distance_from_wall = distance_between_points(ray->start, ray->end);
			distance_from_wall *= cos(temp_to_rotate * M_PI / 180);
			screen_render.y = (game->height * 64) / distance_from_wall;
			adjust_disp_coords(&display_coordinates, game, screen_render.x, screen_render.y);
			int ceiling_iter = 0;
			while (ceiling_iter < display_coordinates.start.y)
			{
				img_put_pixel(game->scene->image, ceiling_color, display_coordinates.start.x, ceiling_iter);
				ceiling_iter++;
			}
			float vert_height = display_coordinates.end.y - display_coordinates.start.y;
			float vert_iter = 64 / vert_height;
			float y_offsett = 0;
			if (vert_height > game->height)
			{
				y_offsett = (vert_height - game->height) / 2;
				vert_height = game->height;
			}
			line_value_adjust(game, &display_coordinates);
			
			int texture_x_pos = get_vert_of_texture(ray->end, game->scene->minimap->player_rotation + temp_to_rotate);
			float texture_y_pos = y_offsett * vert_iter;
			while (display_coordinates.start.y < display_coordinates.end.y)
			{
				img_put_pixel(game->scene->image, darken_color(img_get_pixel(&temp_image[wall_select], texture_x_pos, texture_y_pos),
					SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE, distance_from_wall),
					display_coordinates.start.x, display_coordinates.start.y);				
				display_coordinates.start.y++;
				texture_y_pos += vert_iter;
			}
			while (display_coordinates.start.y < game->height)
			{
				img_put_pixel(game->scene->image, floor_color, display_coordinates.start.x, display_coordinates.start.y);
				display_coordinates.start.y++;
			}
		}
		temp_to_rotate += (player_fov / (game->width));
		screen_render.x += 1;
		vert_wall_iter++;
		if (screen_render.x == game->width || screen_render.y == 0)
			break;
	}
	draw_zombie(game, dist_to_wall_vert_line);
	draw_chests(game, dist_to_wall_vert_line);
	draw__middle_aim(game);
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