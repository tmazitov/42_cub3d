/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:11:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 20:01:24 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <math.h>
# include <stdlib.h>

# define PI 3.14159265359

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_line
{
	t_point	start;
	t_point	end;
	float	a;
	float	b;
	float	d;
	float	length;
}			t_line;

typedef struct s_vector
{
	float	x;
	float	y;
	t_point	start;
	t_point	end;
}			t_vector;

typedef struct s_rectangle
{
	t_point	start;
	float	width;
	float	height;
}			t_rectangle;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}			t_direction;

/*POINT*/

t_point		*make_point(float x, float y);
void		*free_point(t_point *point);
float		point_distance(t_point p1, t_point p2);
int			point_is_equal(t_point p1, t_point p2);

/*LINE*/

t_line		*make_line(float x1, float y1, float x2, float y2);
t_line		*make_line_by_points(t_point p1, t_point p2);
void		*free_line(t_line *line);
void		line_update_by_points(t_line *line, t_point p1, t_point p2);
t_line		*line_perpendicular(t_line *line, t_point point);
void		line_update_start(t_line *line, float x, float y);
void		line_update_end(t_line *line, float x, float y);

/*VECTOR*/

t_vector	*make_vector(int x, int y);
void		*free_vector(t_vector *vector);
void		vector_add(t_vector *vector, float x, float y);

/*COLLIDER*/

/*UTILS*/

float		distance(float x1, float y1, float x2, float y2);
int			check_intersection(t_line *line1, t_line *line2,
				t_point *inter_point);
int			max(int a, int b);
int			max_delimeter(int value);
int			random_int(int min, int max);

#endif