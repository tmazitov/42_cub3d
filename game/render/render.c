/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 19:10:27 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include <sys/time.h>
void	print_time_since_last_call();



int	render_hook(t_game *game)
{
	// printf("FRAME BEING MADE-----------------------------------------------\n");
	print_time_since_last_call();
	mlx_clear_window(game->mlx, game->window);
	// render_scene(game); //Calling render scene before minimap for now,
							// Need separate minimap_ray_render and scene render later;
	render_window_scene(game);
	render_minimap(game);

	render_player(game);

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
	img_draw(game->window, game->scene->image, 0, 0);
	mlx_do_sync(game->mlx);
	return (0);
}
