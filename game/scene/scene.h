/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/16 22:56:11 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include "../map/map.h"
# include "../player/player.h"
# include "../minimap/minimap.h"
# include "../game.h"

typedef struct s_scene
{
	t_map		*map;
	t_player	*player;
	t_minimap	*minimap;
	t_image		*image;
}			t_scene;

t_scene	*make_scene(void *mlx, char *path);
void	*free_scene(t_scene *scene);

#endif // SCENE_H