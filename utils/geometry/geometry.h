/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:11:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 00:07:52 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdlib.h>

# define PI 3.14159265359

typedef struct s_point
{
	float	x;
	float	y;
}		t_point;

typedef struct s_rectangle
{
	t_point	start;
	float	width;
	float	height;
}		t_rectangle;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_direction;


t_point	*make_point(float x, float y);
void	*free_point(t_point *point);

#endif