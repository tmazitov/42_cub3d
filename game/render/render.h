/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:15:53 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 18:01:33 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../game.h"
# include "../../utils/image/image.h"

void	render_scene(t_game *game);
int		render_hook(t_game *game);
void	render_minimap(t_game *game);

t_line	ray_line_getter_x(t_game *game, float angle_in_degrees);
t_line	ray_line_getter_y(t_game *game, float angle_in_degrees);
t_line	ray_line_shortest_xy(t_game *game, float angle_in_degrees);

float	distance_between_points(t_point start, t_point end);

#endif // RENDER_H