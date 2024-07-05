/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:41:40 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/04 21:52:40 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

t_wall	*make_wall(int x, int y, t_wall_type type, \
					t_direction direction)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	if (!wall)
		return (NULL);
	wall->start = NULL;
	wall->end = NULL;
	wall->type = type;
	wall->direction = direction;
	wall->start = make_point((float)x,(float)y);
	if (!wall->start)
		return (free_wall(wall));
	if (direction == NORTH || direction == SOUTH)
		wall->end = make_point((float)(x + 64), (float)y);
	if (direction == WEST || direction == EAST)
		wall->end = make_point((float)x, (float)(y + 64));
	if (!wall->end)
		return (free_wall(wall));
	return (wall);
}

void	*free_wall(t_wall *wall)
{
	if (wall->start)
		free_point(wall->start);
	if (wall->end)
		free_point(wall->end);
	free(wall);
	return (NULL);
}