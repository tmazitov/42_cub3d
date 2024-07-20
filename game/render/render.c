/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 20:34:18 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// #include <sys/time.h>
// void	print_time_since_last_call()
// {
// 	static struct timeval last_time;
// 	struct timeval current_time;
// 	long int elapsed_time;

// 	gettimeofday(&current_time, NULL);
// 	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_usec - last_time.tv_usec) / 1000;
// 	printf("Elapsed time: %ld ms\n", elapsed_time);
// 	last_time = current_time;
// }

int	render_hook(t_game *game)
{
	if (game->blocker)
	{
		return (1);
	}
	// printf("FRAME BEING MADE-----------------------------------------------\n");
	// print_time_since_last_call();
	mlx_clear_window(game->mlx, game->window);
	render_window_scene(game);
	// render_scene(game); //Calling render scene before minimap for now,
							// Need separate minimap_ray_render and scene render later;
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
	mlx_do_sync(game->mlx);
	return (0);
}
