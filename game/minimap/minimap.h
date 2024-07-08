/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:20:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/08 13:31:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdlib.h>
# include <math.h>
# include "../../utils/image/image.h"
# include "../../utils/geometry/geometry.h"
# include "../objs/wall/wall.h"

# define MINIMAP_BORDER_RADIUS 10
# define MINIMAP_BORDER_SIZE 8
# define MINIMAP_POS_X 10
# define MINIMAP_POS_Y 10

// # define MINIMAP_WALLS_COLOR 0x003d3d3d
# define MINIMAP_WALLS_COLOR 0x0042c79a
# define MINIMAP_PLAYER_COLOR 0x003eb58c
# define MINIMAP_BORDER_COLOR 0x0042c79a
# define MINIMAP_BACKGROUND_COLOR 0x00555955
# define MINIMAP_FREE_SPACE_COLOR 0x00d1d1d1

typedef struct s_minimap
{
	t_image		*image;
	t_point		player_pos;
	double		player_rotation;
	int			height;
	int			width;
}			t_minimap;

t_minimap	*make_minimap(void *mlx, int width, int height);
void		*free_minimap(t_minimap *map);

void		minimap_update(t_minimap *minimap, double player_rotation, t_point player_position);
void		minimap_draw_border(t_minimap *minimap);
void		minimap_draw_background(t_minimap *minimap);
void		minimap_draw_wall(t_minimap *minimap, t_wall *wall);
void		minimap_draw_rect(t_minimap *minimap, t_rectangle rect, \
								int color);
void		minimap_draw_image(t_minimap *minimap, t_image *image, t_point pos, double angle);

# endif