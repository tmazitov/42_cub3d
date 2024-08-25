/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/25 23:42:19 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

// Function to darken a color based on distance
uint32_t	darken_color(uint32_t clr, double min_d, double max_d, double cur_d)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	double	factor;

	red = (clr >> 16) & 0xFF;
	green = (clr >> 8) & 0xFF;
	blue = clr & 0xFF;
	if (min_d == max_d)
		min_d -= 1.0;
	factor = 1.0 - (cur_d - min_d) / (max_d - min_d);
	factor = clamp_double(factor, 0.0, 1.0);
	red = (uint8_t)(red * factor);
	green = (uint8_t)(green * factor);
	blue = (uint8_t)(blue * factor);
	return ((red << 16) | (green << 8) | blue);
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
		img_put_pixel(game->scene->image, AIM_COLOR,
			screen_center.x + draw_aim, screen_center.y);
		img_put_pixel(game->scene->image, AIM_COLOR,
			screen_center.x, screen_center.y + draw_aim);
		draw_aim++;
	}
}

static void	adjust_disp_coords(t_line *d_crd, t_game *game,
	int rend_x, int rend_y)
{
	d_crd->start.x = rend_x;
	d_crd->start.y = (game->height / 2.0) - (rend_y / 2);
	d_crd->end.x = rend_x;
	d_crd->end.y = (game->height / 2) + (rend_y / 2);
}

// static void	helper_get_vert(t_point *ray_end)
// {
// 	ray_end->x = round(fmod(ray_end->x, 64));
// 	ray_end->y = round(fmod(ray_end->y, 64));
// 	if (ray_end->x == 64)
// 		ray_end->x = 0;
// 	if (ray_end->y == 64)
// 		ray_end->y = 0;
// }

// static int	get_vert_of_texture(t_point ray_end,
// 	float angle_ray)
// {
// 	if (angle_ray < -180)
// 		angle_ray += 360;
// 	if (angle_ray > 180)
// 		angle_ray -= 360;
// 	angle_ray = fmod(angle_ray, 360.0);
// 	helper_get_vert(&ray_end);
// 	if (ray_end.x == 0 && ray_end.y == 0)
// 		return (0);
// 	if (ray_end.x == 0)
// 	{
// 		if ((angle_ray > 270 && angle_ray < 90))
// 			return (63 - ray_end.y);
// 		else
// 			return (63 - ray_end.y);
// 	}
// 	else if (ray_end.y == 0)
// 	{
// 		if (angle_ray > 180 && angle_ray < 360)
// 			return (ray_end.x);
// 		else
// 			return (63 - ray_end.x);
// 	}
// 	return (0);
// }

static int get_vert_of_texture(t_point ray_end, float angle_ray)
{
	angle_ray = fmod(angle_ray, 360.0);
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
	if (ray_end.x == 0 && ray_end.y == 0)
		return (0);
	if (ray_end.x == 0)
	{
		// if ((angle_ray > 270 && angle_ray <= 360)
		// 	|| (angle_ray >= 0 && angle_ray < 90))
		if (angle_ray > 270 || angle_ray < 90)
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
	return (0);
}

// static int get_vert_of_texture_debug(t_point ray_end, float angle_ray)
// {
// 	angle_ray = fmod(angle_ray, 360.0);
// 	if (angle_ray <= 0)
// 		angle_ray += 360;
// 	if (angle_ray >= 360)
// 		angle_ray -= 360;
// 	printf("ORIG ray_end.x = %f, ray_end.y = %f\n", ray_end.x, ray_end.y);
// 	ray_end.x = round(fmod(ray_end.x, 64));
// 	ray_end.y = round(fmod(ray_end.y, 64));
// 	if (ray_end.x == 64)
// 		ray_end.x = 0;
// 	if (ray_end.y == 64)
// 		ray_end.y = 0;
// 	printf("AFTER ray_end.x = %f, ray_end.y = %f\n", ray_end.x, ray_end.y);
// 	if (ray_end.x == 0 && ray_end.y == 0)
// 		return (0);
// 	if (ray_end.x == 0)
// 	{
// 		// if ((angle_ray > 270 && angle_ray <= 360)
// 		// 	|| (angle_ray >= 0 && angle_ray < 90))
// 		if (angle_ray > 270 || angle_ray < 90)
// 			return (63 - ray_end.y);
// 		else
// 			return (ray_end.y);
// 	}
// 	else if (ray_end.y == 0)
// 	{
// 		if (angle_ray > 180 && angle_ray < 360)
// 			return (63 - ray_end.x);
// 		return (ray_end.x);
// 	}
// 	return (0);
// }



		// if ((angle_ray > 270 && angle_ray < 90))

		// if ((angle_ray > 270 && angle_ray <= 360)
			// || (angle_ray >= 0 && angle_ray < 90))

// //zombie render_scene is below.
/*
	RENDER FUNC that had ISSUE with LOCATION and Angle_to_Sprite
*/
void	helper_render_sprite(float *angle_to_sprite, t_point sprite_pos,
	t_point player_pos, t_game *game)
{
	(*angle_to_sprite) = atan2(sprite_pos.y - player_pos.y, sprite_pos.x - player_pos.x) * 180 / M_PI;
	(*angle_to_sprite) -= game->scene->minimap->player_rotation;
	(*angle_to_sprite) += 180;
	if ((*angle_to_sprite) < -180)
		(*angle_to_sprite) += 360;
	if ((*angle_to_sprite) > 180)
		(*angle_to_sprite) -= 360;
}

typedef struct render_sprite_params
{
	t_image *sprite_image;
	float sprite_distance;
	float *dist_to_wall_vert_line;
}		t_render_sprite_params;


//sprite distance, image and dist_to_wall_vert_line are coming from params
void	helper_rnd_sprt_display(t_game *game, t_render_sprite_params *prm,
	float sprite_screen_size, float angle_to_sprite)
{
	int				screen_x;
	int				screen_y;
	uint32_t		color;
	int				sprite_screen_x;
	int				sprite_screen_y;

	sprite_screen_x = (int)((game->width / 2) * (1 + tan(angle_to_sprite * M_PI / 180) / tan((PLAYER_FOV / 2) * M_PI / 180)));
	sprite_screen_y = game->height / 2 - sprite_screen_size / 2;

	for (int x = 0; x < sprite_screen_size; x++)
	{
		for (int y = 0; y < sprite_screen_size; y++)
		{
			screen_x = sprite_screen_x + x - sprite_screen_size / 2;
			screen_y = sprite_screen_y + y;
			if (screen_x >= 0 && screen_x < game->width - 1 && prm->sprite_distance < prm->dist_to_wall_vert_line[screen_x] )
			{
				if (screen_x >= 0 && screen_x < game->width && screen_y >= 0 && screen_y < game->height)
				{
					color = img_get_pixel(prm->sprite_image, (int)((float)x / sprite_screen_size * prm->sprite_image->width),
						(int)((float)y / sprite_screen_size * prm->sprite_image->height));
					if (color != (uint32_t)(-16777216))
						img_put_pixel(game->scene->image, darken_color(color, SHADE_MIN_DISTANCE,
								SHADE_MAX_DISTANCE, prm->sprite_distance) , screen_x, screen_y);
				}
			}
		}
	}
}

void	init_t_render_sprite_params(t_render_sprite_params *params, t_image *sprite_image, float sprite_distance,
	float *dist_to_wall_vert_line)
{
	params->sprite_image = sprite_image;
	params->sprite_distance = sprite_distance;
	params->dist_to_wall_vert_line = dist_to_wall_vert_line;
}

void render_sprite(t_game *game, t_point sprite_pos, t_image *sprite_image,
	float sprite_distance, float *dist_to_wall_vert_line)
{
	t_point					player_pos;
	float					angle_to_sprite;
	t_render_sprite_params	params;
	float					sprite_screen_size;

	player_pos = game->scene->minimap->player_pos;
	helper_render_sprite(&angle_to_sprite, sprite_pos, player_pos, game);
	init_t_render_sprite_params(&params, sprite_image,
		sprite_distance, dist_to_wall_vert_line);
	if (fabs(angle_to_sprite) < PLAYER_FOV + 10 / 2)
	{
		sprite_screen_size = (game->height * 64) / sprite_distance;
		helper_rnd_sprt_display(game, &params, sprite_screen_size, angle_to_sprite);
	}
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

int find_farthest_zombie(t_game *game, t_enemy_storage *zombz, int *processed)
{
	float	farthest_zombie;
	int		farthest_zombie_index;
	int		i;
	float	distance;

	farthest_zombie = 0;
	i = 0;
	farthest_zombie_index = -1;
	while (i < zombz->size != 0)
	{
		if (processed[i] == 0)
		{
			distance = calc_dis_for_two_points(game->scene->minimap->player_pos,
					*zombz->enemies[i]->pos);
			if (distance > farthest_zombie)
			{
				farthest_zombie = distance;
				farthest_zombie_index = i;
			}
		}
		i++;
	}
	return (farthest_zombie_index);
}

//CORRECT because of dereferencing the value itself ?
//HOW was it affecting the original value
//understandble that i am takinga * and then doing "." instead of "->"
//but how did it get to the original value ?
// void	draw_zombie_helper_sp_pos_setup(t_point *sp_pos,

// seems to be that that using the local * and the "." affects it just for the poitner copy ?
void	draw_zombie_helper_sp_pos_setup(t_point *sp_pos,
	t_enemy_storage *zombz, int far_zomb)
{
	(*sp_pos) = *zombz->enemies[far_zomb]->pos;
	(*sp_pos).x += 32;
	(*sp_pos).y += 32;
}

//WRONG and affecting core values ? 
// void	draw_zombie_helper_sp_pos_setup(t_point *sp_pos,
// 	t_enemy_storage *zombz, int far_zomb)
// {
// 	sp_pos = zombz->enemies[far_zomb]->pos;
// 	sp_pos->x += 32;
// 	sp_pos->y += 32;
// }

void	draw_zombie(t_game *game, float *ds_t_wall)
{
	t_enemy_storage *zombz;
	t_point sp_pos;
	t_image	*img;
	int far_zomb;
	int *processed;
	int zombie_iter;

	zombz = game->scene->enemies;
	zombie_iter = 0;
	processed = calloc(zombz->size, sizeof(int));
	while (zombie_iter < zombz->size)
	{
		far_zomb = find_farthest_zombie(game, zombz, processed);
		if (far_zomb == -1)
			break ;
		processed[far_zomb] = 1;
		draw_zombie_helper_sp_pos_setup(&sp_pos, zombz, far_zomb);
		if (!zombz->enemies[far_zomb]->alive)
			img = get_sprite_by_name(game->scene->map->sprites,
					"ENEMY_DIED")->image;
		else
			img = enemy_get_image(zombz->enemies[far_zomb]);
		render_sprite(game, sp_pos, img, calc_dis_for_two_points(sp_pos,
				game->scene->minimap->player_pos), ds_t_wall);
		zombie_iter++;
	}
	free(processed);
}

//func to convert given params in CUB file to color.
uint32_t	rgb_to_color(t_rgb color)
{
	uint32_t	result;

	if (color.r < 0)
		color.r = 0;
	if (color.r > 255)
		color.r = 255;
	if (color.g < 0)
		color.g = 0;
	if (color.g > 255)
		color.g = 255;
	if (color.b < 0)
		color.b = 0;
	if (color.b > 255)
		color.b = 255;
	result = (color.r << 16) | (color.g << 8) | color.b;
	return (result);
}

int	get_wall_side(float ray_angle, t_point ray_end)
{
	if (ray_angle < 0)
		ray_angle += 360;
	if (ray_angle > 360)
		ray_angle -= 360;
	ray_end.x = (fmod(round(ray_end.x), 64));
	ray_end.y = (fmod(round(ray_end.y), 64));
	if (ray_end.x == 0)
	{
		if (ray_angle > 270 || ray_angle < 90)
			return (2);
		else
			return (3);
	}
	else if (ray_end.y == 0)
	{
		if (ray_angle > 180 && ray_angle < 360)
			return (1);
		return (0);
	}
	return (0);
}

// #include <math.h>
 
// int	get_wall_side_debug(float ray_angle, t_point ray_end)
// {
// 	if (ray_angle < 0)
// 		ray_angle += 360;
// 	if (ray_angle > 360)
// 		ray_angle -= 360;
// 	ray_end.x = (fmod(round(ray_end.x), 64));
// 	ray_end.y = (fmod(round(ray_end.y), 64));
// 	// round(ray_end.x);
// 	// round(ray_end.y);
// 	printf("ray_end.x = %f, ray_end.y = %f\n", ray_end.x, ray_end.y);
// 	printf("angle = %f\n", ray_angle);
// 	if (ray_end.x == 0)
// 	{
// 		if (ray_angle > 270 || ray_angle < 90)
// 			return (2);
// 		else
// 			return (3);
// 	}
// 	else if (ray_end.y == 0)
// 	{
// 		if (ray_angle > 180 && ray_angle < 360)
// 			return (1);
// 		return (0);
// 	}
// 	return (printf("ERROR CASE g_w_s \n"), 0);
// }

void	set_temp_image(t_image *temp_image, t_game *game)
{
	temp_image[0] = *get_sprite_by_name(game->scene->map->sprites, "NO")->image;
	temp_image[1] = *get_sprite_by_name(game->scene->map->sprites, "SO")->image;
	temp_image[2] = *get_sprite_by_name(game->scene->map->sprites, "WE")->image;
	temp_image[3] = *get_sprite_by_name(game->scene->map->sprites, "EA")->image;
	temp_image[4] = *get_sprite_by_name(game->scene->map->sprites,
			"DOOR")->image;
}

typedef struct s_render_window
{
	float		player_fov;
	t_point		screen_render;
	float		temp_to_rotate;
	float		distance_from_wall;
	t_line		display_coordinates;
	int			vert_wall_iter;
	int			wall_select;
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	float		vert_height;
	float		vert_iter;
	float		y_offsett;
	int			texture_x_pos;
	float		texture_y_pos;
	int			ceiling_iter;
}		t_render_window;

float	*render_window_init(t_render_window *r_w,
	t_game *game)
{
	float	*temp;

	r_w->player_fov = PLAYER_FOV;
	r_w->screen_render.x = 0;
	r_w->screen_render.y = 0;
	r_w->temp_to_rotate = -(PLAYER_FOV) / 2;
	r_w->vert_wall_iter = 0;
	r_w->ceiling_color = rgb_to_color(*get_sprite_by_name(game->scen
				->map->sprites, "C")->color);
	r_w->floor_color = rgb_to_color(*get_sprite_by_name(game->scene
				->map->sprites, "F")->color);
	temp = malloc(sizeof(float) * game->width);
	if (!temp)
	{
		free_game(game);
		exit(1);
	}
	return (temp);
}

void	helper_render_window_1(t_render_window *r_w, t_game *game,
		t_line *ray)
{
	r_w->distance_from_wall = distance_between_points(ray->start, ray->end);
	r_w->distance_from_wall *= cos(r_w->temp_to_rotate * M_PI / 180);
	r_w->screen_render.y = (game->height * 64) / r_w->distance_from_wall;
	adjust_disp_coords(&(r_w->display_coordinates),
		game, r_w->screen_render.x, r_w->screen_render.y);

	r_w->ceiling_iter = 0;
	while (r_w->ceiling_iter < r_w->display_coordinates.start.y)
	{
		img_put_pixel(game->scene->image, r_w->ceiling_color,
			r_w->display_coordinates.start.x, r_w->ceiling_iter);
		r_w->ceiling_iter++;
	}
	r_w->vert_height = r_w->display_coordinates.end.y
		- r_w->display_coordinates.start.y;
	r_w->vert_iter = 64 / r_w->vert_height;
	r_w->y_offsett = 0;
	if (r_w->vert_height > game->height)
	{
		r_w->y_offsett = (r_w->vert_height - game->height) / 2;
		r_w->vert_height = game->height;
	}
	line_value_adjust(game, &(r_w->display_coordinates));
}

void	helper_render_window_2(t_render_window *r_w, t_game *game,
	t_line *ray, t_image *temp_image)
{
	if (get_array_map_value(*ray, game) == '1')
	{
		img_put_pixel(game->scene->image,
			darken_color(img_get_pixel(&temp_image[r_w->wall_select],
					r_w->texture_x_pos, r_w->texture_y_pos),
				SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE,
				r_w->distance_from_wall),
			r_w->display_coordinates.start.x,
			r_w->display_coordinates.start.y);
	}
	else
	{
		img_put_pixel(game->scene->image,
			darken_color(img_get_pixel(&temp_image[4],
					r_w->texture_x_pos, r_w->texture_y_pos),
				SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE,
				r_w->distance_from_wall),
			r_w->display_coordinates.start.x,
			r_w->display_coordinates.start.y);
	}
	r_w->display_coordinates.start.y++;
	r_w->texture_y_pos += r_w->vert_iter;
}

//OLD ONE, GOT NEW ONE THAT ENCOMPASSES WHOE RAY IF
// void	helper_render_window_3(t_render_window *r_w, t_game *game,
// 	t_line *ray, t_image *temp_image)
// {
// 	helper_render_window_1(r_w, game, ray);			
// 	r_w->texture_x_pos = get_vert_of_texture(ray->end, game->scene->minimap->player_rotation + r_w->temp_to_rotate);
// 	r_w->texture_y_pos = r_w->y_offsett * r_w->vert_iter;
// 	while (r_w->display_coordinates.start.y < r_w->display_coordinates.end.y)
// 		helper_render_window_2(r_w, game, ray, temp_image);
// 	while (r_w->display_coordinates.start.y < game->height)
// 	{
// 		img_put_pixel(game->scene->image, r_w->floor_color, r_w->display_coordinates.start.x, r_w->display_coordinates.start.y);
// 		r_w->display_coordinates.start.y++;
// 	}
// }

void	helper_render_window_3(t_render_window *r_w, t_game *game,
	t_line *ray, t_image *temp_image)
{
	helper_render_window_1(r_w, game, ray);
	r_w->texture_x_pos = get_vert_of_texture(ray->end,
			game->scene->minimap->player_rotation + r_w->temp_to_rotate);
	r_w->texture_y_pos = r_w->y_offsett * r_w->vert_iter;
	while (r_w->display_coordinates.start.y
		< r_w->display_coordinates.end.y)
		helper_render_window_2(r_w, game, ray, temp_image);
	while (r_w->display_coordinates.start.y < game->height)
	{
		img_put_pixel(game->scene->image, r_w->floor_color,
			r_w->display_coordinates.start.x,
			r_w->display_coordinates.start.y);
		r_w->display_coordinates.start.y++;
	}
}

void	update_screen_values(t_render_window *r_w, t_game *game)
{
	r_w->temp_to_rotate += (r_w->player_fov / (game->width));
	r_w->screen_render.x += 1;
	r_w->vert_wall_iter++;
}

void	update_w_slct_and_d_t_wll(t_render_window *r_w, t_game *game,
	t_line *ray, float *d_t_wall)
{
	r_w->wall_select = get_wall_side(game->scene
			->minimap->player_rotation + r_w->temp_to_rotate, ray->end);
	d_t_wall[r_w->vert_wall_iter]
		= distance_between_points(ray->start, ray->end);
}

//NEW NORMINETTE NORMINETTE NORMINETTE NORMINETTE NORMINETTE NORMINETTE
//ZOMBIE ADD TRYING, zombie func above.
void		render_window_scene(t_game *game)
{
	t_render_window	r_w;
	float			*d_t_wall;
	t_line			*ray;
	t_image			temp_image[5];

	img_clear(game->scene->image);
	set_temp_image(temp_image, game);
	d_t_wall = render_window_init(&r_w, game);
	while (r_w.temp_to_rotate < r_w.player_fov / 2)
	{
		ray = ray_line_shortest_xy(game,
				game->scene->minimap->player_rotation + r_w.temp_to_rotate);
		update_w_slct_and_d_t_wll(&r_w, game, ray, d_t_wall);
		if (ray)
			helper_render_window_3(&r_w, game, ray, temp_image);
		update_screen_values(&r_w, game);
		if (r_w.screen_render.x == game->width || r_w.screen_render.y == 0)
			break ;
	}
	draw_chests(game, d_t_wall);
	draw_zombie(game, d_t_wall);
	draw__middle_aim(game);
	free(d_t_wall);
}

//---------------------------------------------------------------------
							// STOPP!!!!!!!!11111111
//---------------------------------------------------------------------
//ORIGINAL RENDER FUNC //ORIGINAL //ORIGINAL //ORIGINAL
//ZOMBIE ADD TRYING, zombie func above.
// void		render_window_scene(t_game *game)
// {
// 	float		player_fov;
// 	t_point		screen_render;
// 	float		temp_to_rotate;
// 	float		distance_from_wall;
// 	float		dist_to_wall_vert_line[game->width];//DO MALLOC and assign it , since cant do it directly

// 	t_line		*ray;
// 	t_line		display_coordinates;

// 	int		vert_wall_iter = 0;
// 	img_clear(game->scene->image);

// 	//ASSIGN THESE VALUES TO THE RENDER_STRUCT in a separate FUNC
// 	player_fov = PLAYER_FOV;
// 	screen_render.x = 0;
// 	screen_render.y = 0;
// 	temp_to_rotate = -(PLAYER_FOV) / 2;

// 	//image setup, can be added to the func above
// 	t_image temp_image[5];
// 	set_temp_image(temp_image, game);

// 	int wall_select;
// 	uint32_t ceiling_color;
// 	uint32_t floor_color;

// 	ceiling_color = rgb_to_color(*get_sprite_by_name(game->scene->map->sprites,
// 				"C")->color);
// 	floor_color = rgb_to_color(*get_sprite_by_name(game->scene->map->sprites,
// 				"F")->color);
// 	while (temp_to_rotate < player_fov / 2)
// 	{
// 		//RAY CASTING---====----=====----====-----====----=====----====----====----====----=====----
// 		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
// 		wall_select = get_wall_side(game->scene->minimap->player_rotation + temp_to_rotate, ray->end);
// 		dist_to_wall_vert_line[vert_wall_iter] = distance_between_points(ray->start, ray->end);
// 		if (ray)
// 		{
// 			//DISTANCE_VALUES_SET---====----=====----====-----====----=====----====----====----====----=====----
// 			distance_from_wall = distance_between_points(ray->start, ray->end);
// 			distance_from_wall *= cos(temp_to_rotate * M_PI / 180);
// 			screen_render.y = (game->height * 64) / distance_from_wall;
// 			adjust_disp_coords(&display_coordinates, game, screen_render.x, screen_render.y);

// 			//CEILING RENDERING---====----=====----====-----====----=====----====----====----====----=====----
// 			int ceiling_iter = 0;
// 			while (ceiling_iter < display_coordinates.start.y)
// 			{
// 				img_put_pixel(game->scene->image, ceiling_color, display_coordinates.start.x, ceiling_iter);
// 				ceiling_iter++;
// 			}

// 			//VALUES PREP---====----=====----====-----====----=====----====----====----====----=====----
// 			float vert_height = display_coordinates.end.y - display_coordinates.start.y;
// 			float vert_iter = 64 / vert_height;
// 			float y_offsett = 0;
// 			if (vert_height > game->height)
// 			{
// 				y_offsett = (vert_height - game->height) / 2;
// 				vert_height = game->height;
// 			}
// 			line_value_adjust(game, &display_coordinates);

// 			//MAIN JUICY PART OF SCENERY RENDERING ---====----=====----====-----====----=====----====----====----====----=====----
// 			int texture_x_pos = get_vert_of_texture(ray->end, game->scene->minimap->player_rotation + temp_to_rotate);
// 			float texture_y_pos = y_offsett * vert_iter;
// 			while (display_coordinates.start.y < display_coordinates.end.y)
// 			{
// 				if (get_array_map_value(*ray, game) == '1')
// 				{
// 					img_put_pixel(game->scene->image,
// 						darken_color(img_get_pixel(&temp_image[wall_select],
// 								texture_x_pos, texture_y_pos),
// 							SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE,
// 							distance_from_wall),
// 						display_coordinates.start.x,
// 						display_coordinates.start.y);
// 				}
// 				else
// 				{
// 					img_put_pixel(game->scene->image,
// 						darken_color(img_get_pixel(&temp_image[4],
// 								texture_x_pos, texture_y_pos),
// 							SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE,
// 							distance_from_wall),
// 						display_coordinates.start.x,
// 						display_coordinates.start.y);
// 				}
// 				display_coordinates.start.y++;
// 				texture_y_pos += vert_iter;
// 			}
// 			//FLOOR RENDERING---====----=====----====-----====----=====----====----====----====----=====----
// 			while (display_coordinates.start.y < game->height)
// 			{
// 				img_put_pixel(game->scene->image, floor_color, display_coordinates.start.x, display_coordinates.start.y);
// 				display_coordinates.start.y++;
// 			}
// 		}
// 		temp_to_rotate += (player_fov / (game->width));
// 		screen_render.x += 1;
// 		vert_wall_iter++;
// 		if (screen_render.x == game->width || screen_render.y == 0)
// 			break ;
// 	}
// 	draw_chests(game, dist_to_wall_vert_line);
// 	draw_zombie(game, dist_to_wall_vert_line);
// 	draw__middle_aim(game);
// }


//---------------------------------------------------------------------
							// STOPP2222222!!!!!!!!

//Find end of line equivalent of CHAR in 2d array map
char	get_array_map_value(t_line ray, t_game *game)
{
	int	index_y;
	int	index_x;

	ray.start.x /= 64;
	ray.start.y /= 64;
	ray.end.x /= 64;
	ray.end.y /= 64;
	index_x = (int)((ray.end.x  - fmod(ray.end.x, 1)));
	index_y = (int)((ray.end.y  - fmod(ray.end.y, 1)));
	if (ray.end.x < 0 || ray.end.y < 0
		|| ray.end.x >= game->scene->map->width
		|| ray.end.y >= game->scene->map->height)
		return ('1');
	return (game->scene->map->map_double_array[index_y][index_x]);
}
