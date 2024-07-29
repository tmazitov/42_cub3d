/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/29 21:51:41 by kshamsid         ###   ########.fr       */
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

int	render_hook(t_game *game)
{
	// printf("FRAME BEING MADE-----------------------------------------------\n");
	mlx_clear_window(game->mlx, game->window);
	render_window_scene(game);
	render_minimap(game);
	
	render_player(game);

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
	mlx_do_sync(game->mlx);
	return (0);
}
