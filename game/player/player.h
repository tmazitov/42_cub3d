/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:39 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/09 18:45:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdlib.h>
# include <math.h>
# include "../../utils/geometry/geometry.h"
# include "../../utils/image/image.h"
# include "../../utils/libft/libft.h"

# ifndef W_BUTTON
#  define W_BUTTON 115
# endif

# ifndef A_BUTTON
#  define A_BUTTON 97
# endif

# ifndef S_BUTTON
#  define S_BUTTON 119
# endif

# ifndef D_BUTTON
#  define D_BUTTON 100
# endif

# ifndef LEFT_ARROW
#  define LEFT_ARROW 65361
# endif
# ifndef RIGHT_ARROW
#  define RIGHT_ARROW 65363
# endif

# define PLAYER_SIZE 24
# define PLAYER_MAX_SPEED 4
# define PLAYER_ACCELERATION_ITERS 10
# define PLAYER_ROTATION_SPEED 4

# define PLAYER_ICON_SIZE 48

typedef struct s_player
{
	t_point		*pos;
	t_image 	*icon;
	double		rotation;
	int			*pressed_buttons;
	t_vector	*move_vector;
	float		move_speed;
}		t_player;

t_player	*make_player(void *mlx, t_point start_pos, t_direction direction);
void 		*free_player(t_player *player);
t_image		*load_icon(void *mlx);


// CONTROL


int			player_control_set(int keycode, t_player *player);
int			player_control_unset(int keycode, t_player *player);
t_vector	*player_move_vector(t_player *player);
void		player_move_update(t_player *player, t_vector *move_vector);
void		player_rotate(t_player *player);
int			is_player_move(t_player *player);
float		player_speed(t_player *player);

#endif