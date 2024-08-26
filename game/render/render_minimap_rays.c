/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_rays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:04:01 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/26 19:13:06 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include <math.h>
#include <stdint.h>

uint32_t	hue_to_rgb(float p, float q, float t)
{
	if (t < 0.0f)
		t += 1.0f;
	if (t > 1.0f)
		t -= 1.0f;
	if (t < 1.0f / 6.0f)
		return ((p + (q - p) * 6.0f * t) * 255.0f);
	if (t < 1.0f / 2.0f)
		return (q * 255.0f);
	if (t < 2.0f / 3.0f)
		return ((p + (q - p) * (2.0f / 3.0f - t) * 6.0f) * 255.0f);
	return (p * 255.0f);
}

uint32_t hue_to_hex(float hue)
{
	t_hue_to_hex	h_s;

	h_s.s = 1.0f;
	h_s.l = 0.5f;
	h_s.s = 1.0f;
	if (h_s.l < 0.5f)
		h_s.q = h_s.l * (1.0f + h_s.s);
	else
		h_s.q = h_s.l + h_s.s - h_s.l * h_s.s;
	h_s.p = 2.0f * h_s.l - h_s.q;

	h_s.r = hue_to_rgb(h_s.p, h_s.q, hue + 1.0f / 3.0f);
	h_s.g = hue_to_rgb(h_s.p, h_s.q, hue);
	h_s.b = hue_to_rgb(h_s.p, h_s.q, hue - 1.0f / 3.0f);

	return ((h_s.r << 16) | (h_s.g << 8) | h_s.b);
}

uint32_t	get_gradual_hue_color(float length)
{
	float	hue;

	hue = fmod(length / 64.0f, 1.0f);
	return (hue_to_hex(hue));
}

void	line_shortener_for_minimap(t_line *ray, t_game *game)
{
	ray->start.x /= 4;
	ray->start.y /= 4;
	ray->start.x += MINIMAP_BORDER_SIZE - game->scene->minimap->camera->x;
	ray->start.y += MINIMAP_BORDER_SIZE - game->scene->minimap->camera->y;
	ray->end.x /= 4;
	ray->end.y /= 4;
	ray->end.x += MINIMAP_BORDER_SIZE - game->scene->minimap->camera->x;
	ray->end.y += MINIMAP_BORDER_SIZE - game->scene->minimap->camera->y;
}

// void	render_minimap_rays(t_game *game)
// {
// 	float	temp_to_rotate;
// 	t_line	*ray;
// 	int		ray_count;

// 	ray_count = 0;
// 	temp_to_rotate = -PLAYER_FOV / 2;
// 	while (ray_count < 2)
// 	{
// 		ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
// 		if (ray)
// 		{
// 			line_shortener_for_minimap(ray, game);
// 			img_put_line(game->scene->minimap->image, MINIMAP_BORDER_COLOR, ray->start, ray->end);
// 			free_line(ray);
// 		}
// 		temp_to_rotate += PLAYER_FOV;
// 		ray_count++;
// 	}
// 	ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation);
// 	if (ray)
// 	{
// 		line_shortener_for_minimap(ray, game);
// 		img_put_line(game->scene->minimap->image, MINIMAP_BORDER_COLOR, ray->start, ray->end);
// 		free_line(ray);
// 	}
// }