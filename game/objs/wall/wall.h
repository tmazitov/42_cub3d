/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:36:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 17:26:40 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include "../../../utils/geometry/geometry.h"
# include <stdlib.h>

# define WALL_THICKNESS 4
# define WALL_HEIGHT 64
# define WALL_WIDTH 64

typedef enum e_wall_type
{
	WALL,
	DOOR,
	SECRET_DOOR
}				t_wall_type;

typedef struct s_wall
{
	t_wall_type	type;
	t_direction	direction;
	t_point		*start;
	t_point		*end;
}				t_wall;

t_wall			*make_wall(int x, int y, t_wall_type type,
					t_direction direction);
void			*free_wall(t_wall *wall);
t_line			*wall_to_direction_line(t_wall *wall, t_direction direction);
t_line			*wall_to_line(t_wall *wall);
#endif