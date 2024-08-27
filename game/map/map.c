/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:23:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 19:38:25 by kshamsid         ###   ########.fr       */
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
	map->map_double_array = NULL;
}

static void	count_zombies(t_map *map)
{
	char	**temp_array;
	int		zombie_counter;
	int		iter;

	temp_array = map->map_double_array;
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

static int	check_for_multiple_p_chars(t_map *map)
{
	char	**temp_array;
	int		iter;
	int		p_counter;

	temp_array = map->map_double_array;
	p_counter = 0;
	while (*temp_array)
	{
		iter = 0;
		while ((*temp_array)[iter] != '\0')
		{
			if ((*temp_array)[iter] == 'N' || (*temp_array)[iter] == 'S'
				|| (*temp_array)[iter] == 'W' || (*temp_array)[iter] == 'E')
				p_counter++;
			iter++;
		}
		temp_array++;
	}
	if (p_counter > 1)
		return (0);
	return (1);
}

t_map	*make_map(void *mlx, char *path)
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
	if (!check_for_multiple_p_chars(map))
		return (print_error("Multiple N,S,W,Es found in map"),
			free_map(map));
	count_zombies(map);
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
