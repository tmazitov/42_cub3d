/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:20:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 15:17:33 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	init_minimap(t_minimap *map)
{
	map->image = NULL;
}	

t_minimap	*make_minimap(void *mlx, int width, int height)
{
	t_minimap	*map;

	map = malloc(sizeof(t_minimap));
	if (!map)
		return (NULL);
	init_minimap(map);
	map->width = width;
	map->height = height;
	map->image = make_image(mlx);
	if (!map->image)
		return (free_minimap(map));
	if (img_create(map->image, map->width, map->height))
		return (free_minimap(map));
	return (map);
}

void	*free_minimap(t_minimap *map)
{
	if (!map)
		return (NULL);
	if (map->image)
		free_image(map->image);
	free(map);
	return (NULL);
}