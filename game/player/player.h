/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:39 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 01:23:07 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdlib.h>
# include <math.h>
# include "../../utils/geometry/geometry.h"
# include "../../utils/image/image.h"

# define W_BUTTON 119
# define A_BUTTON 97
# define S_BUTTON 115
# define D_BUTTON 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define PLAYER_SIZE 24
# define PLAYER_SPEED 5
# define PLAYER_ROTATION_SPEED 1

# define PLAYER_ICON_SIZE 48

typedef struct s_player
{
	t_point	*pos;
	t_image *icon;
	double	rotation;
}		t_player;

t_player	*make_player(void *mlx, t_point start_pos, t_direction direction);
void 		*free_player(t_player *player);
t_image		*load_icon(void *mlx);


// BEHAVIOR


int			player_move(t_player *player, int keycode);

#endif