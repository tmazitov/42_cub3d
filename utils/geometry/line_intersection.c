/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:11:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/22 14:49:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/// @brief Check an intersection between two lines
/// @param line1 first line
/// @param line2 second line
/// @return if lines have an intersection return 1, else 0
int	check_intersection(t_line *line1, t_line *line2, t_point *inter_point)
{
	float seg1_line2_start = line2->A*line1->start.x + line2->B*line1->start.y + line2->D;
	float seg1_line2_end = line2->A*line1->end.x + line2->B*line1->end.y + line2->D;
	float seg2_line1_start = line1->A*line2->start.x + line1->B*line2->start.y + line1->D;
	float seg2_line1_end = line1->A*line2->end.x + line1->B*line2->end.y + line1->D;

	if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0) 
		return (0);
		
	float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
	inter_point->x = line1->start.x + u * (line1->end.x - line1->start.x);
	inter_point->y = line1->start.y + u * (line1->end.y - line1->start.y); 
	
	return (1);
}