/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:11:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/08 13:26:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdlib.h>

# define PI 3.14159265359
#define fpart(x) (x - floor(x))
#define rfpart(x) (1 - fpart(x))
typedef struct s_point
{
	float	x;
	float	y;
}		t_point;

typedef struct s_vector
{
	float	x;
	float	y;
	t_point	start;
	t_point	end;	
}		t_vector;

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


t_point		*make_point(float x, float y);
void		*free_point(t_point *point);

t_vector	*make_vector(int x, int y);
void		*free_vector(t_vector *vector);
void		vector_add(t_vector *vector, float x, float y);

#endif