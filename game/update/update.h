/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:16:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/28 20:45:30 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

# include "../game.h"

int		update_hook(t_game *game);
void	update_player(t_game *game);
void	update_minimap(t_game *game);
void	update_enemies(t_game *game);

void	player_collect(t_game *game, t_player *player);
void	player_inventory_update(t_game *game);

void	player_door_update(t_game *game);
int		is_player_can_move(t_game *game, t_vector move,
			t_line move_x, t_line move_y);
#endif