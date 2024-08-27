/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:01:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 20:01:09 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_line	*make_line_by_points(t_point p1, t_point p2)
{
	t_line	*line;
	t_point	dir;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line_update_start(line, p1.x, p1.y);
	line_update_end(line, p2.x, p2.y);
	dir.x = p2.x - p1.x;
	dir.y = p2.y - p1.y;
	line->length = sqrt(dir.x * dir.x + dir.y * dir.y);
	line->a = -dir.y;
	line->b = dir.x;
	line->d = -line->a * p1.x - line->b * p1.y;
	return (line);
}

t_line	*make_line(float x1, float y1, float x2, float y2)
{
	t_line	*line;
	t_point	dir;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line_update_start(line, x1, y1);
	line_update_end(line, x2, y2);
	dir.x = x2 - x1;
	dir.y = y2 - y1;
	line->length = sqrt(dir.x * dir.x + dir.y * dir.y);
	line->a = -dir.y;
	line->b = dir.x;
	line->d = -line->a * x1 - line->b * y1;
	return (line);
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
	line->a = -dir.y;
	line->b = dir.x;
	line->d = -line->a * p1.x - line->b * p1.y;
}

void	*free_line(t_line *line)
{
	free(line);
	return (NULL);
}
