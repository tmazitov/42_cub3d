/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:15:53 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 21:26:04 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../game.h"
# include "../../utils/image/image.h"
# include "../scene/scene.h"

# define PLAYER_FOV 75
# define AIM_SIZE 15
# define AIM_COLOR 0x98b9ed
# define SHADE_MIN_DISTANCE -100
# define SHADE_MAX_DISTANCE 600

// By setting SHADE_MIN to negative,
// we start to shade blocks that are even
// INFRONT of uf (MAKE EVERYTHING DARKER)

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

#endif // RENDER_H