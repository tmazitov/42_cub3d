/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:23:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 01:24:10 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	init_map(t_map *map)
{
	map->walls = NULL;
	map->sprites = NULL;
	map->raw = NULL;
	map->height = 0;
	map->width = 0;
	map->player_start = 0;
}

t_map	*make_map(void *mlx,char *path)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	init_map(map);
	map->walls = make_wall_storage();
	if (!map->walls)
		return (free_map(map));
	map->sprites = make_sprite_storage();
	if (!map->sprites)
		return (free_map(map));
	if (!parse_map(mlx, map, path))
		return (free_map(map));
	return (map);
}

void	*free_map(t_map *map)
{
	if (!map)
		return (NULL);
	if (map->walls)
		free_wall_storage(map->walls);
	if (map->sprites)
		free_sprite_storage(map->sprites);
	if (map->raw)
		free_map_raw_item(map->raw);
	free(map);
	return (NULL);
}