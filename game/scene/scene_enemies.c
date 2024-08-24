/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:29:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 16:44:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	init_enemy_storage(t_enemy_storage *storage)
{
	storage->enemies = NULL;
	storage->size = 0;
	storage->alive = 0;
}

t_enemy_storage	*make_enemy_storage(void *mlx, t_map_raw_list *raw_map)
{
	t_enemy_storage	*storage;

	storage = malloc(sizeof(t_enemy_storage));
	if (!storage)
		return (NULL);
	init_enemy_storage(storage);
	storage->size = count_of_objs(raw_map, 'Z');
	if (storage->size == 0)
		return (storage);
	if (!feel_enemy_storage(mlx, storage, raw_map))
		return (free_enemy_storage(storage));
	return (storage);
}

static t_enemy	*make_zombie(t_enemy_storage *storage, void *mlx, int x, int y)
{
	t_point	pos;
	t_enemy	*enemy;

	pos.x = x * 64;
	pos.y = y * 64;
	enemy = make_enemy(mlx, pos, ENEMY_DEFAULT_HEALTH);
	if (!enemy)
		return (NULL);
	printf("\t|'-'| ZOMBIE added at (%f, %f)\n", pos.x, pos.y);
	return (enemy);
}

int	feel_enemy_storage(void *mlx, t_enemy_storage *storage,
		t_map_raw_list *raw_map)
{
	int	x;
	int	y;
	int	created;

	storage->enemies = ft_calloc(storage->size + 1, sizeof(t_enemy *));
	if (!storage->enemies)
		return (0);
	y = 0;
	created = 0;
	while (raw_map && created < storage->size)
	{
		x = 0;
		while (raw_map->value[x])
		{
			if (raw_map->value[x] == 'Z' && !make_zombie(storage, mlx, x, y))
				return (0);
			if (raw_map->value[x] == 'Z')
				created++;
			x++;
		}
		y++;
		raw_map = raw_map->next;
	}
	storage->enemies[created] = NULL;
	return (1);
}

void	*free_enemy_storage(t_enemy_storage *storage)
{
	int	counter;

	if (!storage)
		return (NULL);
	if (storage->enemies)
	{
		counter = 0;
		while (storage->enemies[counter])
		{
			free_enemy(storage->enemies[counter]);
			counter++;
		}
		free(storage->enemies);
	}
	free(storage);
	return (NULL);
}
