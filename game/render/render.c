/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/10 15:22:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	render_hook(t_game *game)
{
	if (game->blocker)
	{
		return (1);
	}
	mlx_clear_window(game->mlx, game->window);
	render_minimap(game);
	// render_scene(game);
	// render_player_road(game);
	// render_exit(game);
	// render_chests(game);
	// render_enemy(game);
	// render_player(game);
	// render_scene_objs(game);
	// render_enemy_health_bar(game);
	// render_player_health_bar(game);
	// render_player_money(game);
	// render_player_score(game);
	mlx_do_sync(game->mlx);
	return (0);
}