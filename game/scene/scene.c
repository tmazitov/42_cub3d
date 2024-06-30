/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:37 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 15:20:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	init_scene(t_scene *scene)
{
	scene->minimap = NULL;
}

t_scene	*make_scene(void *mlx)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	init_scene(scene);
	scene->minimap = make_minimap(mlx, 200, 200);
	if (!scene->minimap)
		return (free_scene(scene));
	return (scene);
}

void	*free_scene(t_scene *scene)
{
	if (!scene)
		return (NULL);
	if (scene->minimap)
		free_minimap(scene->minimap);
	free(scene);
	return (NULL);
}
