/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:37 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 14:44:52 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	init_scene(t_scene *scene)
{
	scene->minimap = NULL;
	scene->player = NULL;
	scene->map = NULL;
	scene->treasures = NULL;
}

t_scene	*make_scene(void *mlx, char *path)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	init_scene(scene);
	scene->minimap = make_minimap(mlx, 200, 200);
	if (!scene->minimap)
		return (free_scene(scene));
	scene->map = make_map(mlx, path);
	if (!scene->map)
		return (free_scene(scene));
	if (!scene->map->player_start)
		return (print_error("undefined player position"), free_scene(scene));
	scene->player = make_player(mlx, *scene->map->player_start, scene->map->player_direction);
	scene->map->player_start = free_point(scene->map->player_start);
	if (!scene->player)
		return (free_scene(scene));
	scene->minimap->player_pos.x = scene->player->pos->x;
	scene->minimap->player_pos.y = scene->player->pos->y;
	scene->treasures = make_treasure_storage(scene->map->raw);
	if (!scene->treasures)
		return (free_scene(scene));
	return (scene);
}

void	*free_scene(t_scene *scene)
{
	if (!scene)
		return (NULL);
	if (scene->minimap)
		free_minimap(scene->minimap);
	if (scene->map)
		free_map(scene->map);
	if (scene->player)
		free_player(scene->player);
	if (scene->treasures)
		free_treasure_storage(scene->treasures);
	free(scene);
	return (NULL);
}
