/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/27 22:03:20 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include <sys/time.h>
void	print_time_since_last_call()
{
	static struct	timeval last_time;
	struct timeval			current_time;
	long int				elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000 + (current_time.tv_usec - last_time.tv_usec) / 1000;
	printf("Elapsed time: %ld ms\n", elapsed_time);
	last_time = current_time;
}

// tried to recenter cursor
// void recenter_cursor(t_game *game)
// {
//     int x;
//     int y;

// 	x = game->width / 2;
// 	y = game->height / 2;
//     mlx_mouse_hide(game->mlx);
//     mlx_mouse_move(game->mlx, x, y);
//     mlx_mouse_show(game->mlx);
// }

int	render_hook(t_game *game)
{
	// printf("FRAME BEING MADE-----------------------------------------------\n");
	// print_time_since_last_call();
	// recenter_cursor(game);
	mlx_clear_window(game->mlx, game->window);
	render_window_scene(game);
	render_minimap(game);
	// render_player(game);

	// recenter_cursor(game); // Tried to recenter cursor

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
