/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:37 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/16 15:13:14 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	init_scene(t_scene *scene)
{
	scene->minimap = NULL;
	scene->player = NULL;
	scene->map = NULL;
	scene->treasures = NULL;
	scene->image = NULL;
	scene->objs_points = NULL;
}

static int	setup_scene_objs(void *mlx, t_scene *scene)
{
	scene->treasures = make_treasure_storage(scene->map->raw);
	if (!scene->treasures)
		return (0);
	scene->enemies = make_enemy_storage(mlx, scene->map->raw);
	if (!scene->enemies)
		return (0);
	scene->objs_points = make_point_list();
	if (!scene->objs_points)
		return (0);
	if (!feel_objs_points(scene->objs_points, scene->map->raw))
		return (0);
	return (1);
}

static int	setup_player_inventory(t_player *player)
{
	if (!player || !player_add_weapon(player, PISTOL))
		return (0);
	return (1);
}


t_scene	*make_scene(void *mlx, char *path)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	init_scene(scene);
	scene->minimap = make_minimap(mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!scene->minimap)
		return (free_scene(scene));
	scene->map = make_map(mlx, path);
	if (!scene->map)
		return (free_scene(scene));
	if (!scene->map->player_start)
		return (print_error("undefined player position"), free_scene(scene));
	scene->player = make_player(mlx, *scene->map->player_start, scene->map->player_direction);
	scene->map->player_start = free_point(scene->map->player_start);
	if (!scene->player || !setup_player_inventory(scene->player))
		return (free_scene(scene));
	scene->image = make_image(mlx);
	if (!scene->image)
		return (free_scene(scene));
	if (!setup_scene_objs(mlx, scene))
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
	if (scene->objs_points)
		free_point_list(scene->objs_points);
	free(scene);
	return (NULL);
}
