/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:36:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 22:42:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include <stdlib.h>

typedef enum e_wall_type
{
	WALL,
	DOOR,
	SECRET_DOOR
}			t_wall_type;

typedef enum e_wall_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_wall_direction;

typedef struct s_wall
{
	int					x;
	int					y;
	t_wall_type 		type;
	t_wall_direction	direction;
}			t_wall;


t_wall	*make_wall(int x, int y, t_wall_type type, \
					t_wall_direction direction);
void	*free_wall(t_wall *wall);
#endif