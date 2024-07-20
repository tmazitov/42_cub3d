/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:36:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/16 21:01:08 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include <stdlib.h>
# include "../../../utils/geometry/geometry.h"

# define WALL_THICKNESS 4
# define WALL_HEIGHT 64
# define WALL_WIDTH 64

typedef enum e_wall_type
{
	WALL,
	DOOR,
	SECRET_DOOR
}			t_wall_type;

typedef struct s_wall
{
	t_wall_type 		type;
	t_direction			direction;
	t_point				*start;
	t_point				*end;
}			t_wall;

t_wall	*make_wall(int x, int y, t_wall_type type, \
					t_direction direction);
void	*free_wall(t_wall *wall);
t_line	*wall_to_direction_line(t_wall *wall, t_direction direction);
t_line	*wall_to_line(t_wall *wall);
#endif