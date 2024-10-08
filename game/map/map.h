/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:22:50 by tmazitov          #+#    #+#             */
/*   Updated: 2024/09/01 01:00:34 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../../utils/error/error.h"
# include "../../utils/gnl/get_next_line.h"
# include "../../utils/image/image.h"
# include "../../utils/libft/libft.h"
# include "../../utils/rgb/rgb.h"
# include "../objs/wall/wall.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SPRITES_COUNT 73

typedef struct s_map_raw_list
{
	char					*value;
	struct s_map_raw_list	*next;
	struct s_map_raw_list	*prev;
}							t_map_raw_list;

typedef struct s_wall_node
{
	struct s_wall_node		*next;
	t_wall					*wall;
}							t_wall_node;

// Contain all walls in the map
typedef struct s_wall_storage
{
	t_wall_node				*start;
}							t_wall_storage;

typedef struct s_sprite_node
{
	t_image					*image;
	struct s_sprite_node	*next;
	t_rgb					*color;
	char					*name;
}							t_sprite_node;

// Contain all sprites for the map
typedef struct s_sprite_storage
{
	t_sprite_node			*start;
}							t_sprite_storage;

typedef struct s_map
{
	t_wall_storage			*walls;
	t_sprite_storage		*sprites;
	int						height;
	int						width;
	t_map_raw_list			*raw;
	t_point					*player_start;
	t_direction				player_direction;
	char					**map_double_array;
	int						zombie_count;
}							t_map;

t_map						*make_map(void *mlx, char *path);
void						*free_map(t_map *map);
int							parse_map(void *mlx, t_map *map, char *path);

/* WALLS */

t_wall_node					*get_last_wall(t_wall_storage *storage);
t_wall_storage				*make_wall_storage(void);
int							add_wall(t_point pos, t_wall_type type,
								t_direction direction, t_wall_storage *storage);
void						*free_wall_node(t_wall_node *node);
void						*free_wall_storage(t_wall_storage *storage);

/* SPRITES */

t_sprite_storage			*make_sprite_storage(void);
int							add_texture_sprite(void *mlx, char *name,
								char *path, t_sprite_storage *storage);
int							add_color_sprite(char *name, t_rgb *color,
								t_sprite_storage *storage);
void						*free_sprite_node(t_sprite_node *node);
void						*free_sprite_storage(t_sprite_storage *storage);
t_sprite_node				*get_sprite_by_name(t_sprite_storage *storage,
								char *name);
t_sprite_node				*get_last_sprite(t_sprite_storage *storage);
int							sprite_storage_length(t_sprite_storage *storage);

/* RAW CONTENT */

int							add_map_raw_item(t_map *map, char *value);
void						*free_map_raw_item(t_map_raw_list *item);
int							convert_raw_to_objs(t_map *map);
int							count_of_objs(t_map_raw_list *item, char obj_char);

/* MAP Double Array */

char						**map_double_array_create(t_map *map);
char						**allocate_2d_array(int width, int height);
void						free_2d_array(char **array, int height);
int							setup_player_position(t_map *map, char ch, int x,
								int y);
int							is_moveable_area(t_map *map, int x, int y);
char						get_raw_value(t_map *map, int x, int y);
int							add_direction_wall(t_map *map, int x, int y,
								t_map_raw_list *node);

/* Map validation check */

int							check_sprite_by_name(char *name,
								t_sprite_storage *sprites, int is_color);
int							is_map_valid(t_map *map);
int							is_whitespace_line(char *line);
int							is_allowed_char(char ch);

#endif