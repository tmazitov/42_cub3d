/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:37 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 16:45:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	init_scene(t_scene *scene)
{
	scene->minimap = NULL;
	scene->player = NULL;
	scene->map = NULL;
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
	free(scene);
	return (NULL);
}
