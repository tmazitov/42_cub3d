/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:01:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/16 16:30:25 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_line	*make_line_by_points(t_point p1, t_point p2)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line_update(line, p1.x, p1.y, p2.x, p2.y);
	return (line);
}

t_line	*make_line(float x1, float y1, float x2, float y2)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line_update(line, x1, y1, x2, y2);
	return (line);
}

void	line_update(t_line *line, float x1, float y1, float x2, float y2)
{
	t_point	dir;

	line->start.x = x1;
	line->start.y = y1;
	line->end.x = x2;
	line->end.y = y2;
	dir.x = x2 - x1;
	dir.y = y2 - y1;

	line->length = sqrt(dir.x * dir.x + dir.y * dir.y);
	line->A = -dir.y;
	line->B = dir.x;
	line->D = -line->A * x1 - line->B * y1;
}
void	line_update_by_points(t_line *line, t_point p1, t_point p2)
{
	t_point	dir;

	line->start.x = p1.x;
	line->start.y = p1.y;
	line->end.x = p2.x;
	line->end.y = p2.y;
	dir.x = p2.x - p1.x;
	dir.y = p2.y - p1.y;

	line->length = sqrt(dir.x * dir.x + dir.y * dir.y);
	line->A = -dir.y;
	line->B = dir.x;
	line->D = -line->A * p1.x - line->B * p1.y;
}

void	*free_line(t_line *line)
{
	free(line);
	return (NULL);
}
