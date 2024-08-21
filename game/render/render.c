/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 19:39:52 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// static void	render_test_animation(t_game *game)
// {
// 	t_enemy	*enemy;
// 	t_image	*anime_image;
// 	t_point	pos;

// 	if (!game->scene->enemies)
// 		return ;
// 	enemy = game->scene->enemies->enemies[0];
// 	if (!enemy)
// 		return ;
// 	anime_image = anime_current_frame(enemy->move_anime);
// 	if (!anime_image)
// 		return ;
// 	pos.x = game->width - anime_image->width;
// 	pos.y = 0;
// 	img_put_img(game->scene->image, anime_image, pos, 0);
// }

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

int	render_hook(t_game *game)
{
	// printf("FRAME BEING MADE-----------------------------------------------\n");
	print_time_since_last_call();

	mlx_clear_window(game->mlx, game->window);
	render_window_scene(game);
	render_minimap(game);
	render_player(game);

	// // ATTEMPTING to draw bullet trajectory--------
	// t_line bul_line;
	// bul_line = *bullet_shoot_func(game, game->scene->minimap->player_rotation);
	// // printf("coordinates BEF shorten = %f %f, %f %f\n", bul_line.start.x, bul_line.start.y, bul_line.end.x, bul_line.end.y);
	// line_shortener_for_minimap(&bul_line, game);
	// bul_line.start.x += 20;
	// bul_line.start.y += 10;
	// bul_line.end.x += 20;
	// bul_line.end.y += 10;
	// // printf("coordinates AFTER shorten = %f %f, %f %f\n", bul_line.start.x, bul_line.start.y, bul_line.end.x, bul_line.end.y);
	// img_put_line(game->scene->image, 0xff0303, bul_line.start, bul_line.end);


	// render_test_animation(game);

	// render_player_road(game);
	// render_exit(game);
	// render_chests(game);
	// render_scene_objs(game);
	// render_enemy_health_bar(game);
	// render_player_health_bar(game);
	// render_player_money(game);
	// render_player_score(game);
	img_draw(game->window, game->scene->image, 0, 0);
	// mlx_do_sync(game->mlx);
	return (0);
}
