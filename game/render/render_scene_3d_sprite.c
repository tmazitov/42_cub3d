/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d_sprite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:47:57 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 18:48:33 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	helper_rnd_chest_off_loop_sp(t_render_sprite_params *prm,
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

void	helper_rnd_chest_offset_display_sp(t_game *game,
	t_render_sprite_params *prm, float sprite_screen_size,
	float angle_to_sprite)
{
	t_render_disp_params	pr_disp;

	pr_disp.sprite_screen_x = (int)((game->width / 2)
			* (1 + tan(angle_to_sprite * M_PI
					/ 180) / tan((PLAYER_FOV / 2) * M_PI / 180)));
	pr_disp.sprite_screen_y = (game->height / 2)
		- (sprite_screen_size / 2);
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

void	init_t_render_sprite_params(t_render_sprite_params *params,
	t_image *sprite_image, float sprite_distance,
	float *dist_to_wall_vert_line)
{
	params->sprite_image = sprite_image;
	params->sprite_distance = sprite_distance;
	params->dist_to_wall_vert_line = dist_to_wall_vert_line;
}

//OLD GIT VERSION making
void	render_sprite(t_game *game, t_image *sprite_image,
	float *dist_to_wall_vert_line, t_sprite_pos_info_zm *zmb)
{
	t_point					player_pos;
	float					angle_to_sprite;
	t_render_sprite_params	params;
	float					sprite_screen_size;

	player_pos = game->scene->minimap->player_pos;
	helper_render_sprite(&angle_to_sprite, zmb->sp_pos, player_pos, game);
	init_t_render_sprite_params(&params, sprite_image,
		zmb->sprite_distance, dist_to_wall_vert_line);
	if (fabs(angle_to_sprite) < PLAYER_FOV + 10 / 2)
	{
		sprite_screen_size = (game->height * 64) / zmb->sprite_distance;
		helper_rnd_chest_offset_display_sp(game, &params,
			sprite_screen_size, angle_to_sprite);
	}
}

void	render_chest(t_game *game, t_image *sprite_image,
	float *dist_to_wall_vert_line, t_sprite_pos_info *sp)
{
	t_point					player_pos;
	float					angle_to_sprite;
	t_render_sprite_params	params;
	float					sprite_screen_size;

	player_pos = game->scene->minimap->player_pos;
	helper_render_sprite(&angle_to_sprite, sp->s_p, player_pos, game);
	init_t_render_sprite_params(&params, sprite_image,
		sp->sprite_distance, dist_to_wall_vert_line);
	if (fabs(angle_to_sprite) < PLAYER_FOV + 10 / 2)
	{
		sprite_screen_size = (game->height * 16) / sp->sprite_distance;
		helper_rnd_chest_offset_display(game, &params,
			sprite_screen_size, angle_to_sprite);
	}
}
