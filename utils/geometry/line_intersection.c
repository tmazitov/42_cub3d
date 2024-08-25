/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:11:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 23:17:09 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/// @brief Check an intersection between two lines
/// @param line1 first line
/// @param line2 second line
/// @return if lines have an intersection return 1, else 0
int	check_intersection(t_line *line1, t_line *line2, t_point *inter_point)
{
	float	seg1_line2_start;
	float	seg1_line2_end;
	float	seg2_line1_start;
	float	seg2_line1_end;
	float	u;

	seg1_line2_start = line2->a * line1->start.x + line2->b * line1->start.y
		+ line2->d;
	seg1_line2_end = line2->a * line1->end.x + line2->b * line1->end.y
		+ line2->d;
	seg2_line1_start = line1->a * line2->start.x + line1->b * line2->start.y
		+ line1->d;
	seg2_line1_end = line1->a * line2->end.x + line1->b * line2->end.y
		+ line1->d;
	if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start
		* seg2_line1_end >= 0)
		return (0);
	u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
	inter_point->x = line1->start.x + u * (line1->end.x - line1->start.x);
	inter_point->y = line1->start.y + u * (line1->end.y - line1->start.y);
	return (1);
}
