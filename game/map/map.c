/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:23:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 13:29:49 by tmazitov         ###   ########.fr       */
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
	if (!map_double_array_create(map))
		return (free_map(map));

	// printf("TEST129\n");
	// // temporatu prints to make a map with 2d array and save it.
	// printf("---START PRINTS FROM [map.c]-----------\n\n");
	// char **temp_array = map->map_double_array;
	// size_t size_of_array = 0;
	// while (temp_array[size_of_array])
	// {
	// 	size_of_array++;
	// }
	// printf("size_of_array = [%zu]\n", size_of_array);
	// while (*temp_array)
	// {
	// 	printf("[%s]\n", *temp_array);
	// 	temp_array++;
	// }
	// printf("end of while loop\n");
	// printf("---height = [%d]\n", map->height);
	// printf("---width = [%d]\n", map->width);
	// printf("\n\nEND PRINTS FROM [map.c]-----------");
	// exit(1);
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
	if (map->map_double_array)
		free_2d_array(map->map_double_array, map->height);
	free(map);
	return (NULL);
}
