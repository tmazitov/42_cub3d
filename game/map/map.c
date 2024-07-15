/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:23:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 21:13:09 by kshamsid         ###   ########.fr       */
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

	// temporatu prints to make a map with 2d array and save it.
	t_map_raw_list *temp = map->raw;
	while (temp)
	{
		printf("[%s]\n", temp->value);
		temp = temp->next;
	}
	printf("height = [%d]\n", map->height);
	printf("width = [%d]\n", map->width);
	exit(1);
	return (map);
}

void	free_2d_array(char **array, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
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
