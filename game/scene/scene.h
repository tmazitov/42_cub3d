/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/03 20:54:28 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include "../map/map.h"
# include "../minimap/minimap.h"

typedef struct s_scene
{
	t_map		*map;
	t_minimap	*minimap;
}			t_scene;

t_scene	*make_scene(void *mlx, char *path);
void	*free_scene(t_scene *scene);

#endif // SCENE_H