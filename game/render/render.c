/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 14:29:55 by tmazitov         ###   ########.fr       */
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
	// printf("FRAME BEING MADE-----------------------------------------------\n");
	// print_time_since_last_call();
	mlx_clear_window(game->mlx, game->window);
	// render_scene(game); //Calling render scene before minimap for now,
							// Need separate minimap_ray_render and scene render later;
	render_window_scene(game);
	render_minimap(game);
	render_player(game);

	img_draw(game->window, game->scene->image, 0, 0);
	mlx_do_sync(game->mlx);
	return (0);
}
