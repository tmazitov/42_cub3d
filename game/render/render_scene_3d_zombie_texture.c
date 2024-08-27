/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d_zombie_texture.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:07:09 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 19:08:38 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	zombie_image_setter(t_image **img, t_enemy_storage *zombz,
	int far_zomb, t_game *game)
{
	if (!(zombz->enemies[far_zomb]->alive))
		(*img) = get_sprite_by_name(game->scene->map->sprites,
				"ENEMY_DIED")->image;
	else
		(*img) = enemy_get_image(zombz->enemies[far_zomb]);
}

//OLD GIT VERSION
void	draw_zombie(t_game *game, float *ds_t_wall)
{
	t_enemy_storage			*zombz;
	t_image					*img;
	int						*processed;
	t_sprite_pos_info_zm	zmb;

	zombz = game->scene->enemies;
	zmb.zombie_iter = 0;
	processed = calloc(zombz->size, sizeof(int));
	while (zmb.zombie_iter < zombz->size)
	{
		zmb.far_zomb = find_farthest_zombie(game, zombz, processed);
		if (zmb.far_zomb == -1)
			break ;
		processed[zmb.far_zomb] = 1;
		draw_zombie_helper_sp_pos_setup(&(zmb.sp_pos), zombz, zmb.far_zomb);
		zombie_image_setter(&img, zombz, zmb.far_zomb, game);
		zmb.sprite_distance = calc_dis_for_two_points(zmb.sp_pos,
				game->scene->minimap->player_pos);
		render_sprite(game, img, ds_t_wall, &zmb);
		zmb.zombie_iter++;
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
	ray_end.x = (fmod(ray_end.x, 64));
	ray_end.y = (fmod(ray_end.y, 64));
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

void	set_temp_image(t_image *temp_image, t_game *game)
{
	temp_image[0] = *get_sprite_by_name(game->scene->map->sprites, "NO")->image;
	temp_image[1] = *get_sprite_by_name(game->scene->map->sprites, "SO")->image;
	temp_image[2] = *get_sprite_by_name(game->scene->map->sprites, "WE")->image;
	temp_image[3] = *get_sprite_by_name(game->scene->map->sprites, "EA")->image;
	temp_image[4] = *get_sprite_by_name(game->scene->map->sprites,
			"DOOR")->image;
}
