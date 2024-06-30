/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:30:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 14:52:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "main.h" 

int	main(void)
{
	t_game	*game;
	void	*mlx;
	void	*mlx_win;
	

	game = make_game(1920, 1080, "Hello world!");
	if (!game)
		return (1);
	printf("mlx: %p\n",mlx);
	printf("win: %p\n",mlx_win);
	img_put_pixel(game->scene->minimap->image, 0x00FF0000, 10, 10);
	mlx_loop_hook(game->mlx, render_hook, game);
	mlx_loop(game->mlx);
}