/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d_zombie_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:51:29 by kshamsid          #+#    #+#             */
/*   Updated: 2024/09/01 00:57:42 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
void	chest_pos_setup(t_point *sp_pos, t_treasure_storage *chest,
		int sp_select)
{
	(*sp_pos) = *chest->boxes[sp_select]->pos;
	(*sp_pos).x += 32;
	(*sp_pos).y += 32;
}

//OLD VERSION FROM GIT
void	draw_chests(t_game *game, float *dist_to_wall_vert_line)
{
	t_treasure_storage	*chestz;
	t_point				p_s;
	t_image				chest_image;
	t_sprite_pos_info	ch_s;

	chestz = game->scene->treasures;
	ch_s.sprite_iter = 0;
	while (ch_s.sprite_iter < chestz->size)
	{
		ch_s.s_p = *chestz->boxes[ch_s.sprite_iter]->pos;
		p_s = game->scene->minimap->player_pos;
		ch_s.s_p.x += 32;
		ch_s.s_p.y += 32;
		if (chestz->items[ch_s.sprite_iter] == NULL
			|| chestz->items[ch_s.sprite_iter]->items[0]->amount == 0)
			chest_image = *get_sprite_by_name(game
					->scene->map->sprites, "TB_EMPTY")->image;
		else
			chest_image = *get_sprite_by_name(game->scene
					->map->sprites, "TB")->image;
		ch_s.sprite_distance = calc_dis_for_two_points(ch_s.s_p, p_s);
		render_chest(game, &chest_image, dist_to_wall_vert_line, &ch_s);
		ch_s.sprite_iter++;
	}
}

int	find_farthest_zombie(t_game *game, t_enemy_storage *zombz, int *processed)
{
	float	farthest_zombie;
	int		farthest_zombie_index;
	int		i;
	float	distance;

	farthest_zombie = 0;
	i = 0;
	farthest_zombie_index = -1;
	while (i < zombz->size)
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

void	draw_zombie_helper_sp_pos_setup(t_point *sp_pos,
	t_enemy_storage *zombz, int far_zomb)
{
	(*sp_pos) = *zombz->enemies[far_zomb]->pos;
	(*sp_pos).x += 32;
	(*sp_pos).y += 32;
}
