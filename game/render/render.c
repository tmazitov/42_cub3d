/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 17:03:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>

void	print_time_since_last_call(void)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	long int				elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000
		+ (current_time.tv_usec - last_time.tv_usec) / 1000;
	printf("Elapsed time: %ld ms\n", elapsed_time);
	last_time = current_time;
}

void	render_move_string(t_game *game)
{
	char	*string_put;

	string_put = ft_strjoin("Player Moves Made: ",
							ft_itoa(game->scene->moves_made));
	mlx_string_put(game->mlx, game->window, game->width - 160, 15, 0xFF014d47,
			string_put);
	free(string_put);
}

int	render_hook(t_game *game)
{
	print_time_since_last_call();
	mlx_clear_window(game->mlx, game->window);
	render_window_scene(game);
	render_minimap(game);
	render_player(game);
	img_draw(game->window, game->scene->image, 0, 0);
	render_move_string(game);
	return (0);
}
