/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:41:40 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 22:42:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

t_wall	*make_wall(int x, int y, t_wall_type type, \
					t_wall_direction direction)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	if (!wall)
		return (NULL);
	wall->x = x;
	wall->y = y;
	wall->type = type;
	wall->direction = direction;
	return (wall);
}

void	*free_wall(t_wall *wall)
{
	free(wall);
	return (NULL);
}