/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:12:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/28 19:54:50 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	*render_window_init(t_render_window *r_w,
	t_game *game)
{
	float	*temp;

	r_w->player_fov = PLAYER_FOV;
	r_w->screen_render.x = 0;
	r_w->screen_render.y = 0;
	r_w->temp_to_rotate = -(PLAYER_FOV) / 2;
	r_w->vert_wall_iter = 0;
	r_w->ceiling_color = rgb_to_color(*get_sprite_by_name(game->scene
				->map->sprites, "C")->color);
	r_w->floor_color = rgb_to_color(*get_sprite_by_name(game->scene
				->map->sprites, "F")->color);
	temp = malloc(sizeof(float) * game->width);
	if (!temp)
	{
		free_game(game);
		exit(1);
	}
	return (temp);
}

void	helper_render_window_1(t_render_window *r_w, t_game *game,
		t_line *ray)
{
	r_w->distance_from_wall = distance_between_points(ray->start, ray->end);
	r_w->distance_from_wall *= cos(r_w->temp_to_rotate * M_PI / 180);
	r_w->screen_render.y = (game->height * 64) / r_w->distance_from_wall;
	adjust_disp_coords(&(r_w->display_coordinates),
		game, r_w->screen_render.x, r_w->screen_render.y);
	r_w->ceiling_iter = 0;
	while (r_w->ceiling_iter < r_w->display_coordinates.start.y)
	{
		img_put_pixel(game->scene->image, r_w->ceiling_color,
			r_w->display_coordinates.start.x, r_w->ceiling_iter);
		r_w->ceiling_iter++;
	}
	r_w->vert_height = r_w->display_coordinates.end.y
		- r_w->display_coordinates.start.y;
	r_w->vert_iter = 64 / r_w->vert_height;
	r_w->y_offsett = 0;
	if (r_w->vert_height > game->height)
	{
		r_w->y_offsett = (r_w->vert_height - game->height) / 2;
		r_w->vert_height = game->height;
	}
	line_value_adjust(game, &(r_w->display_coordinates));
}

void	helper_render_window_2(t_render_window *r_w, t_game *game,
	t_line *ray, t_image *temp_image)
{
	if (get_array_map_value(*ray, game) == '1')
	{
		img_put_pixel(game->scene->image,
			darken_color(img_get_pixel(&temp_image[r_w->wall_select],
					r_w->texture_x_pos, r_w->texture_y_pos),
				SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE,
				r_w->distance_from_wall),
			r_w->display_coordinates.start.x,
			r_w->display_coordinates.start.y);
	}
	else
	{
		img_put_pixel(game->scene->image,
			darken_color(img_get_pixel(&temp_image[4],
					r_w->texture_x_pos, r_w->texture_y_pos),
				SHADE_MIN_DISTANCE, SHADE_MAX_DISTANCE,
				r_w->distance_from_wall),
			r_w->display_coordinates.start.x,
			r_w->display_coordinates.start.y);
	}
	r_w->display_coordinates.start.y++;
	r_w->texture_y_pos += r_w->vert_iter;
}

void	helper_render_window_3(t_render_window *r_w, t_game *game,
	t_line *ray, t_image *temp_image)
{
	helper_render_window_1(r_w, game, ray);
	r_w->texture_x_pos = get_vert_of_texture(ray->end,
			game->scene->minimap->player_rotation + r_w->temp_to_rotate);
	r_w->texture_y_pos = r_w->y_offsett * r_w->vert_iter;
	while (r_w->display_coordinates.start.y
		< r_w->display_coordinates.end.y)
		helper_render_window_2(r_w, game, ray, temp_image);
	while (r_w->display_coordinates.start.y < game->height)
	{
		img_put_pixel(game->scene->image, r_w->floor_color,
			r_w->display_coordinates.start.x,
			r_w->display_coordinates.start.y);
		r_w->display_coordinates.start.y++;
	}
}

//NEW NORMINETTE NORMINETTE NORMINETTE NORMINETTE NORMINETTE NORMINETTE
//ZOMBIE ADD TRYING, zombie func above.
void	render_window_scene(t_game *game)
{
	t_render_window	r_w;
	float			*d_t_wall;
	t_line			*ray;
	t_image			temp_image[5];

	img_clear(game->scene->image);
	set_temp_image(temp_image, game);
	d_t_wall = render_window_init(&r_w, game);
	while (r_w.temp_to_rotate < r_w.player_fov / 2)
	{
		ray = ray_line_shortest_xy(game,
				game->scene->minimap->player_rotation + r_w.temp_to_rotate);
		update_w_slct_and_d_t_wll(&r_w, game, ray, d_t_wall);
		if (ray)
			helper_render_window_3(&r_w, game, ray, temp_image);
		update_screen_values(&r_w, game);
		if (ray)
			ray = free_line(ray);
		if (r_w.screen_render.x == game->width || r_w.screen_render.y == 0)
			break ;
	}
	draw_chests(game, d_t_wall);
	draw_zombie(game, d_t_wall);
	draw__middle_aim(game);
	free(d_t_wall);
}
