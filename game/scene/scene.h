/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 23:48:25 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../../utils/path/path.h"
# include "../enemy/enemy.h"
# include "../items/items.h"
# include "../map/map.h"
# include "../minimap/minimap.h"
# include "../objs/treasure/treasure.h"
# include "../player/player.h"
# include <pthread.h>
# include <stdlib.h>

# define COLLECT_DISTANCE 80
# define ENEMY_DEFAULT_HEALTH 10

typedef struct s_player	t_player;

typedef struct s_enemy_storage
{
	t_enemy				**enemies;
	int					size;
	int					alive;
}						t_enemy_storage;

typedef struct s_treasure_storage
{
	t_treasure			**boxes;
	t_item_collection	**items;
	int					size;
}						t_treasure_storage;

typedef struct s_scene
{
	t_map				*map;
	t_player			*player;
	t_minimap			*minimap;
	t_treasure_storage	*treasures;
	t_enemy_storage		*enemies;
	t_point_list		*objs_points;
	t_image				*image;
	int					moves_made;
	float				prev_speed;
}						t_scene;

int						treasure_collect(t_treasure_storage *storage,
							t_treasure *box, t_player *player);
int						feel_objs_points(t_point_list *point,
							t_map_raw_list *raw_map);
int						feel_treasure_storage(t_treasure_storage *storage,
							t_map_raw_list *raw_map);
t_scene					*make_scene(void *mlx, char *path);
void					*free_scene(t_scene *scene);

t_treasure_storage		*make_treasure_storage(t_map_raw_list *raw_map);
void					*free_treasure_storage(t_treasure_storage *storage);

t_enemy_storage			*make_enemy_storage(void *mlx, t_map_raw_list *raw_map);
int						feel_enemy_storage(void *mlx, t_enemy_storage *storage,
							t_map_raw_list *raw_map);
void					*free_enemy_storage(t_enemy_storage *storage);
void 					set_active_objs_points(t_point_list *list,
							int x, int y, int value);

#endif // SCENE_H