/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:04:20 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 19:58:43 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_line	*line_perpendicular(t_line *line, t_point point)
{
	t_point	perp_point;
	float	d;
	float	denominator;

	if (!line)
		return (NULL);
	d = line->a * point.x + line->b * point.y + line->d;
	denominator = pow(line->a, 2) + pow(line->b, 2);
	perp_point.x = point.x - line->a * d / denominator;
	perp_point.y = point.y - line->b * d / denominator;
	return (make_line_by_points(perp_point, point));
}

void	line_update_start(t_line *line, float x, float y)
{
	line->start.x = x;
	line->start.y = y;
}

void	line_update_end(t_line *line, float x, float y)
{
	line->end.x = x;
	line->end.y = y;
}
