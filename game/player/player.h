/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:39 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/13 18:17:32 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdlib.h>
# include <math.h>
# include "../../utils/geometry/geometry.h"
# include "../../utils/image/image.h"
# include "../../utils/libft/libft.h"
# include "inventory/inventory.h"
# include "../../utils/keyboard.h"
# include "../../utils/mouse.h"


# define PLAYER_SIZE 24

# ifndef PLAYER_MAX_SPEED
	# define PLAYER_MAX_SPEED 4
# endif 

# define PLAYER_ACCELERATION_ITERS 10
# define PLAYER_ROTATION_SPEED 0.3

# define PLAYER_DEFAULT_BULLETS_COUNT 42
# define PLAYER_INV_CELL_AMOUNT 6

# define PLAYER_ICON_SIZE 48

typedef struct s_player
{
	t_point		*pos;
	t_image 	*icon;
	double		rotation;
	int			*pressed_buttons;
	t_vector	*move_vector;
	float		move_speed;
	t_inventory	*inventory;
	int			update_count;
}		t_player;

typedef struct s_scene t_scene;

typedef struct s_game t_game;


# include "../render/render.h"

t_player	*make_player(void *mlx, t_point start_pos, t_direction direction);
void 		*free_player(t_player *player);
t_image		*load_icon(void *mlx);


// CONTROL (KEYBOARD)


int			player_control_set(int keycode, t_player *player);
int			player_control_unset(int keycode, t_player *player);
t_vector	*player_move_vector(t_player *player);
void		player_move_update(t_player *player, t_vector *move_vector);
void		player_rotate(t_player *player);
int			is_player_move(t_player *player);
float		player_speed(t_player *player);


// CONTROL (MOUSE)

int			player_mouse_scroll(int button, int x, int y, t_game *player);
int			player_mouse_move(int x, int y, t_player *player);
void		*shoot_sound_func(void *arg);


// INVENTORY


int			player_add_bullets(t_player *player, int amount);
int			player_add_weapon(t_player *player, t_item_type type);

#endif