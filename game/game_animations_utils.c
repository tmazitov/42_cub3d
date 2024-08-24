/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animations_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:51:59 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 22:52:07 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	feel_game_animations(t_game *game)
{
	if (game->scene->map->zombie_count && !feel_enemies_animations(game))
		return (0);
	return (1);
}
