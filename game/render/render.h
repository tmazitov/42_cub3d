/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:15:53 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 19:10:12 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../game.h"
# include "../../utils/image/image.h"
# include "../scene/scene.h"

# define PLAYER_FOV 				60
# define PLAYER_VIEW_DEPTH 			12
//guide using FOV60, need to find values to scale for 75 without issues

# define AIM_SIZE 					15
# define AIM_COLOR 					0x98b9ed
# define SHADE_MIN_DISTANCE			-200
# define SHADE_MAX_DISTANCE			450
// By setting SHADE_MIN to negative,
// we start to shade blocks that are even
// INFRONT of uf (MAKE EVERYTHING DARKER)
# define BULLET_HIT_CHECK_ITERATION	4.0
# define BULLET_MAX_ITERATIONS		160
//		Total bullet distance travel is (B_M_I * Z_H_W)

# define ZOMBIE_HITBOX_WIDTH		15
// BODY HITBOX = 10 (not including hands)
// BODY + HANDS HITBOX = 15

typedef struct s_ray_struct
{
	float	y_iteration;
	float	x_iteration;
	int		iterations;
	float	angle_in_pie;
}	t_ray_struct;

typedef struct s_hue_to_hex
{
	float		s;
	float		l;
	float		q;
	float		p;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
}	t_hue_to_hex;

typedef struct s_render_mini
{
	void			*img;
	t_sprite_node	*treasure_sprite;
	t_sprite_node	*treasure_sprite_empty;
}		t_render_mini;

typedef struct s_render_window
{
	float		player_fov;
	t_point		screen_render;
	float		temp_to_rotate;
	float		distance_from_wall;
	t_line		display_coordinates;
	int			vert_wall_iter;
	int			wall_select;
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	float		vert_height;
	float		vert_iter;
	float		y_offsett;
	int			texture_x_pos;
	float		texture_y_pos;
	int			ceiling_iter;
}		t_render_window;

typedef struct render_sprite_params
{
	t_image	*sprite_image;
	float	sprite_distance;
	float	*dist_to_wall_vert_line;
}		t_render_sprite_params;

typedef struct s_render_disp_params
{
	int			screen_x;
	int			screen_y;
	uint32_t	color;
	int			sprite_screen_x;
	int			sprite_screen_y;
	int			loop_x;
	int			loop_y;
}		t_render_disp_params;

typedef struct s_sprite_pos_info
{
	t_point		s_p;
	float		sprite_distance;
	int			sprite_iter;
}			t_sprite_pos_info;

typedef struct s_sprite_pos_info_zm
{
	t_point		sp_pos;
	float		sprite_distance;
	int			zombie_iter;
	int			far_zomb;
}			t_sprite_pos_info_zm;

typedef struct s_enemy_storage		t_enemy_storage;

typedef struct s_treasure_storage	t_treasure_storage;

float		distance_between_points(t_point start, t_point end);
void		init_ray_struct(t_ray_struct *ray_struct, float *angle_in_degrees);

int			render_hook(t_game *game);
void		render_minimap(t_game *game);
void		render_player(t_game *game);
void		render_window_scene(t_game *game);

void		render_minimap_rays(t_game *game);

t_line		*ray_line_getter_x(t_game *game, float angle_in_degrees);
t_line		*ray_line_getter_y(t_game *game, float angle_in_degrees);
t_line		*ray_line_shortest_xy(t_game *game, float angle_in_degrees);

float		distance_between_points(t_point start, t_point end);
char		get_array_map_value(t_line ray, t_game *game);
void		line_shortener_for_minimap(t_line *ray, t_game *game);
void		bullet_shoot_func(t_game *game, float angle_in_degrees);

void		minimap_draw_walls(t_game *game);
void		minimap_draw_enemies(t_game *game);

double		clamp_double(double value, double min, double max);
void		line_value_adjust(t_game *game, t_line *line);
void		draw__middle_aim(t_game *game);
void		adjust_disp_coords(t_line *d_crd, t_game *game,
				int rend_x, int rend_y);
uint32_t	darken_color(uint32_t clr, double min_d,
				double max_d, double cur_d);

void		helper_get_vert(t_point *ray_end);
int			get_vert_of_texture(t_point ray_end, float angle_ray);
void		helper_render_sprite(float *angle_to_sprite, t_point sprite_pos,
				t_point player_pos, t_game *game);
void		helper_rnd_chest_off_loop(t_render_sprite_params *prm,
				t_render_disp_params *pr_disp, float sprite_screen_size,
				t_game *game);
void		helper_rnd_chest_offset_display(t_game *game,
				t_render_sprite_params *prm, float sprite_screen_size,
				float angle_to_sprite);

void		helper_rnd_chest_off_loop_sp(t_render_sprite_params *prm,
				t_render_disp_params *pr_disp, float sprite_screen_size,
				t_game *game);
void		helper_rnd_chest_offset_display_sp(t_game *game,
				t_render_sprite_params *prm, float sprite_screen_size,
				float angle_to_sprite);
void		init_t_render_sprite_params(t_render_sprite_params *params,
				t_image *sprite_image, float sprite_distance,
				float *dist_to_wall_vert_line);
void		render_sprite(t_game *game, t_image *sprite_image,
				float *dist_to_wall_vert_line, t_sprite_pos_info_zm *zmb);
void		render_chest(t_game *game, t_image *sprite_image,
				float *dist_to_wall_vert_line, t_sprite_pos_info *sp);

float		calc_dis_for_two_points(t_point zombie_pos, t_point player_pos);
void		chest_pos_setup(t_point *sp_pos, t_treasure_storage *chest,
				int sp_select);
void		draw_chests(t_game *game, float *dist_to_wall_vert_line);
int			find_farthest_zombie(t_game *game,
				t_enemy_storage *zombz, int *processed);
void		draw_zombie_helper_sp_pos_setup(t_point *sp_pos,
				t_enemy_storage *zombz, int far_zomb);

void		zombie_image_setter(t_image **img, t_enemy_storage *zombz,
				int far_zomb, t_game *game);
void		draw_zombie(t_game *game, float *ds_t_wall);
uint32_t	rgb_to_color(t_rgb color);
int			get_wall_side(float ray_angle, t_point ray_end);
void		set_temp_image(t_image *temp_image, t_game *game);

void		update_screen_values(t_render_window *r_w, t_game *game);
void		update_w_slct_and_d_t_wll(t_render_window *r_w, t_game *game,
				t_line *ray, float *d_t_wall);
char		get_array_map_value(t_line ray, t_game *game);

#endif // RENDER_H