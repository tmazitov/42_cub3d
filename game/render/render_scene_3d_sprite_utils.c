/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d_sprite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:44:07 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 18:45:43 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	helper_get_vert(t_point *ray_end)
{
	ray_end->x = round(fmod(ray_end->x, 64));
	ray_end->y = round(fmod(ray_end->y, 64));
	if (ray_end->x == 64)
		ray_end->x = 0;
	if (ray_end->y == 64)
		ray_end->y = 0;
}

int	get_vert_of_texture(t_point ray_end, float angle_ray)
{
	angle_ray = fmod(angle_ray, 360.0);
	if (angle_ray <= 0)
		angle_ray += 360;
	if (angle_ray >= 360)
		angle_ray -= 360;
	helper_get_vert(&ray_end);
	if (ray_end.x == 0 && ray_end.y == 0)
		return (0);
	if (ray_end.x == 0)
	{
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

// //zombie render_scene is below.
/*
	RENDER FUNC that had ISSUE with LOCATION and Angle_to_Sprite
*/
void	helper_render_sprite(float *angle_to_sprite, t_point sprite_pos,
	t_point player_pos, t_game *game)
{
	(*angle_to_sprite)
		= atan2(sprite_pos.y - player_pos.y,
			sprite_pos.x - player_pos.x) * 180 / M_PI;
	(*angle_to_sprite) -= game->scene->minimap->player_rotation;
	(*angle_to_sprite) += 180;
	if ((*angle_to_sprite) < -180)
		(*angle_to_sprite) += 360;
	if ((*angle_to_sprite) > 180)
		(*angle_to_sprite) -= 360;
}

void	helper_rnd_chest_off_loop(t_render_sprite_params *prm,
	t_render_disp_params *pr_disp, float sprite_screen_size,
	t_game *game)
{
	pr_disp->screen_x = pr_disp->sprite_screen_x
		+ pr_disp->loop_x - sprite_screen_size / 2;
	pr_disp->screen_y = pr_disp->sprite_screen_y + pr_disp->loop_y;
	if (pr_disp->screen_x >= 0 && pr_disp->screen_x < game->width - 1
		&& prm->sprite_distance
		< prm->dist_to_wall_vert_line[pr_disp->screen_x])
	{
		if (pr_disp->screen_x >= 0 && pr_disp->screen_x
			< game->width && pr_disp->screen_y >= 0
			&& pr_disp->screen_y < game->height)
		{
			pr_disp->color = img_get_pixel(prm->sprite_image,
					(int)((float)pr_disp->loop_x / sprite_screen_size
						* prm->sprite_image->width),
					(int)((float)pr_disp->loop_y
						/ sprite_screen_size * prm->sprite_image->height));
			if (pr_disp->color != (uint32_t)(-16777216))
				img_put_pixel(game->scene->image,
					darken_color(pr_disp->color, SHADE_MIN_DISTANCE,
						SHADE_MAX_DISTANCE, prm->sprite_distance),
					pr_disp->screen_x, pr_disp->screen_y);
		}
	}
	pr_disp->loop_y++;
}

void	helper_rnd_chest_offset_display(t_game *game,
	t_render_sprite_params *prm, float sprite_screen_size,
	float angle_to_sprite)
{
	t_render_disp_params	pr_disp;

	pr_disp.sprite_screen_x = (int)((game->width / 2)
			* (1 + tan(angle_to_sprite * M_PI
					/ 180) / tan((PLAYER_FOV / 2) * M_PI / 180)));
	pr_disp.sprite_screen_y = (game->height / 2)
		- (sprite_screen_size / 2)
		+ (64 / prm->sprite_distance * game->height / 2);
	pr_disp.loop_x = 0;
	while (pr_disp.loop_x < sprite_screen_size)
	{
		pr_disp.loop_y = 0;
		while (pr_disp.loop_y < sprite_screen_size)
		{
			helper_rnd_chest_off_loop(prm, &pr_disp,
				sprite_screen_size, game);
		}
		pr_disp.loop_x++;
	}
}
