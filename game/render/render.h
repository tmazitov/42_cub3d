/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:15:53 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 18:40:28 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../game.h"
# include "../../utils/image/image.h"
# include "../scene/scene.h"

# define PLAYER_FOV 				60
# define PLAYER_VIEW_DEPTH 			12
//guide using FOV60, need to find values to scale for 75 without issues

# define AIM_SIZE 					15
# define AIM_COLOR 					0x98b9ed
# define SHADE_MIN_DISTANCE			-200
# define SHADE_MAX_DISTANCE			450
// By setting SHADE_MIN to negative,
// we start to shade blocks that are even
// INFRONT of uf (MAKE EVERYTHING DARKER)


# define BULLET_HIT_CHECK_ITERATION	4.0
# define BULLET_MAX_ITERATIONS		160
//		Total bullet distance travel is (B_M_I * Z_H_W)

# define ZOMBIE_HITBOX_WIDTH		15
// BODY HITBOX = 10 (not including hands)
// BODY + HANDS HITBOX = 15


int		render_hook(t_game *game);
void	render_minimap(t_game *game);
void	render_player(t_game *game);
void	render_window_scene(t_game *game);

void	render_minimap_rays(t_game *game);

t_line	*ray_line_getter_x(t_game *game, float angle_in_degrees);
t_line	*ray_line_getter_y(t_game *game, float angle_in_degrees);
t_line	*ray_line_shortest_xy(t_game *game, float angle_in_degrees);

float	distance_between_points(t_point start, t_point end);
char	get_array_map_value(t_line ray, t_game *game);
void	line_shortener_for_minimap(t_line *ray, t_game *game);


void	bullet_shoot_func(t_game *game, float angle_in_degrees);

#endif // RENDER_H