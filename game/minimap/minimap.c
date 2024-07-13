/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:20:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 20:15:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	init_minimap(t_minimap *map)
{
	map->image = NULL;
	map->camera = NULL;
	map->player_pos.x = 0;
	map->player_pos.y = 0;
	map->player_rotation = 0;
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
	if (!img_create(map->image, map->width, map->height))
		return (free_minimap(map));
	map->camera = make_point(0,0);
	if (!map->camera)
		return (free_minimap(map));
	return (map);
}

void	*free_minimap(t_minimap *map)
{
	if (!map)
		return (NULL);
	if (map->image)
		free_image(map->image);
	if (map->camera)
		free_point(map->camera);
	free(map);
	return (NULL);
}