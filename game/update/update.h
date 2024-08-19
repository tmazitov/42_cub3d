/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:16:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 16:41:33 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

# include "../game.h"

int		update_hook(t_game *game);
void	update_player(t_game *game);
void	update_minimap(t_game *game);
void	update_enemies(t_game *game);
#endif