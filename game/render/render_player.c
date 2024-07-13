/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:23:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/13 21:23:44 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_player_bullets(t_game *game)
{
	char	*str_value;
	char	*total_string;

	if (!game->writer)
		return ;
	str_value = ft_itoa(game->scene->player->inventory->bullets);
	if (!str_value)
		return ;
	total_string = ft_strjoin("bullets ", str_value);
	free(str_value);
	if (!total_string)
		return ;
	mlx_print(game->writer, total_string, 280, 20);
	free(total_string);
}	