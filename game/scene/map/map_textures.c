/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:14:15 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/02 20:42:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_sprite_storage	*make_sprite_storage(void)
{
	t_sprite_storage	*storage;

	storage = malloc(sizeof(t_sprite_storage));
	if (!storage)
		return (NULL);
	storage->start = NULL;
	return (storage);
}

int add_texture_sprite(void *mlx, char *name, char *path, \
				t_sprite_storage *storage)
{
	t_sprite_node	*node;

	if (!name || !path)
		return (0);
	node = malloc(sizeof(t_sprite_node));
	if (!node)
		return (0);
	node->next = NULL;
	node->image = NULL;
	node->color	= NULL;
	node->name = ft_strdup(name);
	if (!node->name)
		return (free_sprite_node(node), 0);
	node->image = make_image(mlx);
	if (!node->image)
		return (free_sprite_node(node), 0);
	if (!img_load(node->image, path))
		return (free_sprite_node(node), 0);
	if (storage->start == NULL)
		storage->start = node;
	else
		get_last_sprite(storage)->next = node;
	return (1);
}

int add_color_sprite(char *name, t_rgb *color, \
				t_sprite_storage *storage)
{
	t_sprite_node	*node;

	if (!name || !color)
		return (0);
	node = malloc(sizeof(t_sprite_node));
	if (!node)
		return (0);
	node->next = NULL;
	node->image = NULL;
	node->color = color;
	node->name = ft_strdup(name);
	if (!node->name)
		return (0);
	if (storage->start == NULL)
		storage->start = node;
	else
		get_last_sprite(storage)->next = node;
	return (1);
}

void	*free_sprite_node(t_sprite_node *node)
{
	if (!node)
		return (NULL);
	if (node->image)
		free_image(node->image);
	if (node->name)
		free(node->name);
	if (node->color)
		free_rgb(node->color);
	free(node);
	return (NULL);
}

void	*free_sprite_storage(t_sprite_storage *storage)
{
	t_sprite_node	*node;
	t_sprite_node	*next;

	node = storage->start;
	while (node)
	{
		next = node->next;
		free_sprite_node(node);
		node = next;
	}
	free(storage);
	return (NULL);
}