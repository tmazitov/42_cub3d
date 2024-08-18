/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:16:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/18 22:00:45 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

# include "../game.h"

typedef struct s_vector_fork
{
	t_line			*player_path1;
	t_line			*player_path2;
	t_line			*player_path3;
	t_line			*inter_wall1;
	t_line			*inter_wall2;
	t_line			*inter_wall3;
}	t_vector_fork;

int		update_hook(t_game *game);
void	update_player(t_game *game);
void	update_minimap(t_game *game);
void	update_enemies(t_game *game);
#endif