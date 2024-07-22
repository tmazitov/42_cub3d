/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:12:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/22 14:52:50 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_point	*make_point(float x, float y)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

float	point_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + (pow(p1.y - p2.y, 2))));
}

int		point_is_equal(t_point p1, t_point p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

void	*free_point(t_point	*point)
{
	free(point);
	return (NULL);
}