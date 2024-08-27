/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d_sprite_render.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:35:12 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 18:37:40 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

// Function to darken a color based on distance
uint32_t	darken_color(uint32_t clr, double min_d, double max_d, double cur_d)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	double	factor;

	red = (clr >> 16) & 0xFF;
	green = (clr >> 8) & 0xFF;
	blue = clr & 0xFF;
	if (min_d == max_d)
		min_d -= 1.0;
	factor = 1.0 - (cur_d - min_d) / (max_d - min_d);
	factor = clamp_double(factor, 0.0, 1.0);
	red = (uint8_t)(red * factor);
	green = (uint8_t)(green * factor);
	blue = (uint8_t)(blue * factor);
	return ((red << 16) | (green << 8) | blue);
}

// Basic checks for < 0 && > window dimensions
void	line_value_adjust(t_game *game, t_line *line)
{
	if (line->start.x > game->width)
		line->start.x = game->width;
	if (line->start.y > game->height)
		line->start.y = game->height;
	if (line->start.x < 0)
		line->start.x = 0;
	if (line->start.y < 0)
		line->start.y = 0;
	if (line->end.x > game->width)
		line->end.x = game->width;
	if (line->end.y > game->height)
		line->end.y = game->height;
	if (line->end.x < 0)
		line->end.x = 0;
	if (line->end.y < 0)
		line->end.y = 0;
}

void	draw__middle_aim(t_game *game)
{
	t_point	screen_center;
	int		aim_size;
	int		draw_aim;

	aim_size = AIM_SIZE;
	screen_center.x = game->width / 2;
	screen_center.y = (float)game->height / 2;
	draw_aim = aim_size / 2;
	draw_aim = -draw_aim;
	while (draw_aim < aim_size / 2)
	{
		img_put_pixel(game->scene->image, AIM_COLOR,
			screen_center.x + draw_aim, screen_center.y);
		img_put_pixel(game->scene->image, AIM_COLOR,
			screen_center.x, screen_center.y + draw_aim);
		draw_aim++;
	}
}

void	adjust_disp_coords(t_line *d_crd, t_game *game,
	int rend_x, int rend_y)
{
	d_crd->start.x = rend_x;
	d_crd->start.y = (game->height / 2.0) - (rend_y / 2);
	d_crd->end.x = rend_x;
	d_crd->end.y = (game->height / 2) + (rend_y / 2);
}
