/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 20:31:45 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include "../map/map.h"
# include "../player/player.h"
# include "../minimap/minimap.h"
# include "../objs/treasure/treasure.h"
# include "../items/items.h"

# define TREASURE_COLLECT_DISTANCE 80
typedef struct s_treasure_storage
{
	t_treasure			**boxes;
	t_item_collection	**items;
	int 				size;	
}		t_treasure_storage;

typedef struct s_scene
{
	t_map				*map;
	t_player			*player;
	t_minimap			*minimap;
	t_treasure_storage 	*treasures;
	t_image		*image;
}			t_scene;


t_scene	*make_scene(void *mlx, char *path);
void	*free_scene(t_scene *scene);

t_treasure_storage	*make_treasure_storage(t_map_raw_list *raw_map);
void				*free_treasure_storage(t_treasure_storage *storage);
int					treasure_collect(t_treasure_storage *storage, t_treasure *box, t_player *player);


#endif // SCENE_H