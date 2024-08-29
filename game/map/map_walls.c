/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:15:11 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/29 13:55:05 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_wall_node	*get_last_wall(t_wall_storage *storage)
{
	t_wall_node	*node;

	node = storage->start;
	while (node->next)
		node = node->next;
	return (node);
}

t_wall_storage	*make_wall_storage(void)
{
	t_wall_storage	*storage;

	storage = malloc(sizeof(t_wall_storage));
	if (!storage)
		return (NULL);
	storage->start = NULL;
	return (storage);
}

int	add_wall(t_point pos, t_wall_type type, t_direction direction,
		t_wall_storage *storage)
{
	t_wall_node	*node;

	node = malloc(sizeof(t_wall_node));
	if (!node)
		return (0);
	node->next = NULL;
	node->wall = make_wall(pos.x, pos.y, type, direction);
	if (!node->wall)
		return (0);
	if (storage->start == NULL)
		storage->start = node;
	else
		get_last_wall(storage)->next = node;
	return (1);
}

void	*free_wall_node(t_wall_node *node)
{
	if (!node)
		return (NULL);
	if (node->wall)
		free_wall(node->wall);
	free(node);
	return (NULL);
}

void	*free_wall_storage(t_wall_storage *storage)
{
	t_wall_node	*node;
	t_wall_node	*next;

	node = storage->start;
	while (node)
	{
		next = node->next;
		free_wall_node(node);
		node = next;
	}
	free(storage);
	return (NULL);
}
