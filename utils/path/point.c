/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:13:49 by tmazitov          #+#    #+#             */
/*   Updated: 2023/12/10 21:57:22 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

t_a_point	*make_a_point(int x, int y, t_a_point *origin)
{
	t_a_point	*point;

	point = malloc(sizeof(t_a_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->heuristic_approxim = -1;
	point->origin = NULL;
	point->weight = 0;
	point->passed_way = 0;
	if (origin)
		point->passed_way = origin->passed_way + NEIGHBOUR_DISTANCE;
	point->origin = origin;
	return (point);
}

static int	pnt_calc_distance(t_a_point *point, t_a_point *dest)
{
	int	distance;
	int	x;
	int	y;

	x = point->x;
	y = point->y;
	distance = 0;
	while (x < dest->x || x > dest->x)
	{
		if (x < dest->x)
			x += NEIGHBOUR_DISTANCE;
		else if (x > dest->x)
			x -= NEIGHBOUR_DISTANCE;
		distance++;
	}
	while (y < dest->y || y > dest->y)
	{
		if (y < dest->y)
			y += NEIGHBOUR_DISTANCE;
		else if (y > dest->y)
			y -= NEIGHBOUR_DISTANCE;
		distance++;
	}
	return (distance);
}

void	pnt_calc_weight(t_a_point *point, t_a_point *dest)
{
	if (!point || !dest)
		return ;
	point->heuristic_approxim = pnt_calc_distance(point, dest);
	point->heuristic_approxim *= NEIGHBOUR_DISTANCE;
	point->weight = point->heuristic_approxim + point->passed_way;
}

void	*free_a_point(t_a_point *point)
{
	if (point)
		free(point);
	return (NULL);
}
