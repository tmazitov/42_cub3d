/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:32:06 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 16:55:29 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_sprite_node	*get_last_sprite(t_sprite_storage *storage)
{
	t_sprite_node	*node;

	node = storage->start;
	while (node->next)
		node = node->next;
	return (node);
}

t_sprite_node	*get_sprite_by_name(t_sprite_storage *storage, char *name)
{
	t_sprite_node	*node;

	if (!name)
		return (NULL);
	node = storage->start;
	while (node)
	{
		if (ft_strncmp(node->name, name, ft_strlen(name)) == 0
			&& node->name[ft_strlen(name)] == '\0')
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	sprite_storage_length(t_sprite_storage *storage)
{
	t_sprite_node	*node;
	int				i;

	i = 0;
	node = storage->start;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}
