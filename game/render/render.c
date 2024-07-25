/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 04:52:01 by tmazitov         ###   ########.fr       */
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

	t_a_point		*src;
	t_a_point		*dest;
	t_player		*pl;
	t_enemy			*en;
	t_path			*path;
	t_point_node	*node;
	t_point			p1;
	t_point			p2;

	pl = game->scene->player;
	en = game->scene->enemies->enemies[0];
	if (!en)
		return 0;
	src = make_a_point(en->pos->x, en->pos->y, NULL);
	dest = make_a_point((int)(pl->pos->x / 64) * 64, (int)(pl->pos->y / 64) * 64 , NULL);
	if (!src || !dest )
		return 0;
	path = calc_path(src, dest, game->scene->objs_points);
	// printf("\t path from (%d, %d) to (%d, %d) is %p\n", src->x, src->y, dest->x, dest->y, path);
	if (!path)
		return 0;
	node = path->point_list->points;
	while (node && node->next)
	{
		p1.x = node->point->x;
		p1.y = node->point->y;
		node = node->next;
		p2.x = node->point->x;
		p2.y = node->point->y;

		p1.x /= 4;
		p1.y /= 4;
		p1.x += MINIMAP_BORDER_SIZE;
		p1.y += MINIMAP_BORDER_SIZE;
		p2.x /= 4;
		p2.y /= 4;
		p2.x += MINIMAP_BORDER_SIZE;
		p2.y += MINIMAP_BORDER_SIZE;
		img_put_line(game->scene->minimap->image, 0xa83264, p1, p2);
	}
	free_path(path);
	mlx_do_sync(game->mlx);
	return (0);
}
