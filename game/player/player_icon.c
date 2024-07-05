/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_icon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:35:53 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 23:38:52 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

t_image	*load_icon(void *mlx)
{
	t_image	*icon;

	if (access("textures/player_icon.xpm", R_OK) == -1)
		return (NULL);
	icon = make_image(mlx);
	if (!icon)
		return (NULL);
	if (!img_load(icon, "textures/player_icon.xpm"))
		return (free_image(icon));
	return (icon);
}