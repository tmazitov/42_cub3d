/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:39 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 20:03:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdlib.h>
# include <math.h>
# include "../../utils/geometry/geometry.h"

# define W_BUTTON 115
# define A_BUTTON 97
# define S_BUTTON 119
# define D_BUTTON 100

# define PLAYER_SIZE 24
# define PLAYER_SPEED 5
# define PLAYER_ROTATION_SPEED 0.1

# define PLAYER_ICON_SIZE 48

typedef struct s_player
{
	t_point	*pos;
	float	rotation;
}		t_player;

t_player	*make_player(t_point start_pos, t_direction direction);
void 		*free_player(t_player *player);


// BEHAVIOR


int			player_move(t_player *player, int keycode);

#endif