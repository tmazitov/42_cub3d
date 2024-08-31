/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 19:01:51 by tmazitov         ###   ########.fr       */
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
	mlx_string_put(game->mlx, game->window, game->width - 160,
		15, 0xFF014d47, string_put);
	free(string_put);
}

int	all_enemies_dead(t_game *game)
{
	int	i;

	i = 0;
	if (game->scene->enemies->size == 0)
		return (1);
	while (i < game->scene->enemies->size)
	{
		if (game->scene->enemies->enemies[i]->hb->current > 0)
			return (1);
		i++;
	}
	return (0);
}

void	game_finish_func(t_game *game)
{
	t_image	game_finish_image;

	game->blocker = 1;
	game->scene->player->blocker = 1;
	mlx_clear_window(game->mlx, game->window);
	if (game->scene->player->inventory->health_bar->current <= 0)
	{
		game_finish_image = *get_sprite_by_name(game->scene->map->sprites,
				"GAME_OVER_SCREEN")->image;
		img_draw(game->window, &game_finish_image, 200, 150);
	}
	else if (all_enemies_dead(game) == 0)
	{
		game_finish_image = *get_sprite_by_name(game->scene->map->sprites,
				"GAME_WIN_SCREEN")->image;
		img_draw(game->window, &game_finish_image, 0, 0);
	}
}

int	render_hook(t_game *game)
{
	if ((game->scene->enemies->size != 0 && game->blocker == 1)
		|| game->scene->player->inventory->health_bar->current <= 0
		|| all_enemies_dead(game) == 0)
		return (game_finish_func(game), 0);
	mlx_clear_window(game->mlx, game->window);
	render_window_scene(game);
	render_minimap(game);
	render_player(game);
	render_move_string(game);
	img_draw(game->window, game->scene->image, 0, 0);
	render_move_string(game);
	return (0);
}
	// mlx_do_sync(game->mlx);
	//DO SYNC reduces performance from 86(ms/frame)(good) to 100(ms/frame)(bad)

// render_test_animation(game);

// render_player_road(game);
// render_exit(game);
// render_chests(game);
// render_scene_objs(game);
// render_enemy_health_bar(game);
// render_player_health_bar(game);
// render_player_money(game);
// render_player_score(game);

// img_draw(game->window, game->scene->image, 0, 0);

// mlx_pixel_put(game->mlx, game->window, game->width/2, 500, 0x00FFFFFF);
// render_move_string(game);
