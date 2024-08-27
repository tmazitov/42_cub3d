/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:16:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 19:41:48 by kshamsid         ###   ########.fr       */
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

#endif