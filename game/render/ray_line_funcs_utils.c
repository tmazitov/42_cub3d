/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_line_funcs_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:08 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/26 18:44:32 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

float	distance_between_points(t_point start, t_point end)
{
	float	dx;
	float	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

void	init_ray_struct(t_ray_struct *ray_struct,
	float *angle_in_degrees)
{
	if ((*angle_in_degrees) < 0)
		(*angle_in_degrees) += 360;
	if ((*angle_in_degrees) > 360)
		(*angle_in_degrees) -= 360;
	ray_struct->y_iteration = 0;
	ray_struct->x_iteration = 0;
	ray_struct->iterations = 0;
	ray_struct->angle_in_pie = (*angle_in_degrees) * PI / 180.0;
}
