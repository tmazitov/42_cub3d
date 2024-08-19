/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:23:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 21:37:19 by kshamsid         ###   ########.fr       */
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
	map->zombie_count = 0;
}

static	void count_zombies(t_map *map)
{
	char **temp_array = map->map_double_array;
	int	zombie_counter;
	int iter;
	
	zombie_counter = 0;
	while (*temp_array)
	{
		iter = 0;
		while ((*temp_array)[iter] != '\0')
		{
			if ((*temp_array)[iter] == 'Z')
				zombie_counter++;
			iter++;
		}
		temp_array++;
	}
	map->zombie_count = zombie_counter;
}

//checks 2d array map, for N S W E
// if more than 1 exists, return 0(error case)
static int	check_for_multiple_p_chars(t_map *map)
{
	char **temp_array;
	int	iter;
	int p_counter;

	
	temp_array = map->map_double_array;
	p_counter = 0;
	while (*temp_array)
	{
		iter = 0;
		while ((*temp_array)[iter] != '\0')
		{
			if ((*temp_array)[iter] == 'N'
				|| (*temp_array)[iter] == 'S'
				|| (*temp_array)[iter] == 'W'
				|| (*temp_array)[iter] == 'E')
				p_counter++;
			iter++;
		}
		temp_array++;
	}
	printf("p_counter = [%d]\n", p_counter);
	if (p_counter > 1)
		return (0);
	return (1);
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
	if (!check_for_multiple_p_chars(map))
		return (print_error("Multiple N,S,W,Es found in map"),
			free_map(map));
	count_zombies(map);
	// // temporatu prints to make a map with 2d array and save it.
	printf("---START PRINTS FROM [map.c]-----------\n\n");
	// char **temp_array = map->map_double_array;
	// int	zombie_counter = 0;
	// int iter;
	// while (*temp_array)
	// {
	// 	while (*temp_array[iter] != '\0')
	// 	{
	// 		if (*temp_array[iter] == 'Z')
	// 			zombie_counter++;
	// 		iter++;
	// 	}
	// 	temp_array++;
	// }
	// printf("end of while loop\n");
	// printf("---height = [%d]\n", map->height);
	// printf("---width = [%d]\n", map->width);
	printf("\n\nEND PRINTS FROM [map.c]-----------");
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
