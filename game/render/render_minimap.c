/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:45:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 15:31:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_minimap(t_game *game)
{
	void	*win;
	void	*img;

	minimap_update(game->scene->minimap);
	win = game->window;
	img = game->scene->minimap->image;
	img_draw(win, img, MINIMAP_POS_X, MINIMAP_POS_Y);
}