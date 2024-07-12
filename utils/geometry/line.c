/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:01:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 15:35:55 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_line	*make_line(float x1, float y1, float x2, float y2)
{
	t_line	*line;
	t_point	dir;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
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
	return (line);
}

void	*free_line(t_line *line)
{
	free(line);
	return (NULL);
}
