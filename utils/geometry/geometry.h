/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:11:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 16:00:24 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdlib.h>
# include <math.h>

# define PI 3.14159265359
#define fpart(x) (x - floor(x))
#define rfpart(x) (1 - fpart(x))
typedef struct s_point
{
	float	x;
	float	y;
}		t_point;

typedef struct s_line
{
	t_point	start;
	t_point	end;
	float	A;
	float	B;
	float	D;
	float	length;
}		t_line;

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



/*POINT*/


t_point				*make_point(float x, float y);
void				*free_point(t_point *point);


/*LINE*/

t_line				*make_line(float x1, float y1, float x2, float y2);
void				*free_line(t_line *line);


/*VECTOR*/


t_vector	*make_vector(int x, int y);
void		*free_vector(t_vector *vector);
void		vector_add(t_vector *vector, float x, float y);


/*COLLIDER*/


/*UTILS*/

int			check_intersection(t_line *line1, t_line *line2);
int			max(int a, int b);
#endif