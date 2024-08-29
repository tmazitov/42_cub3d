/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:54:46 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/29 13:52:49 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_font_sprites(t_sprite_storage *sprites)
{
	if (!check_sprite_by_name("CH_H", sprites, 0)
		|| !check_sprite_by_name("CH_I", sprites, 0)
		|| !check_sprite_by_name("CH_J", sprites, 0)
		|| !check_sprite_by_name("CH_K", sprites, 0)
		|| !check_sprite_by_name("CH_L", sprites, 0)
		|| !check_sprite_by_name("CH_M", sprites, 0)
		|| !check_sprite_by_name("CH_N", sprites, 0)
		|| !check_sprite_by_name("CH_O", sprites, 0)
		|| !check_sprite_by_name("CH_P", sprites, 0)
		|| !check_sprite_by_name("CH_Q", sprites, 0)
		|| !check_sprite_by_name("CH_R", sprites, 0)
		|| !check_sprite_by_name("CH_S", sprites, 0)
		|| !check_sprite_by_name("CH_T", sprites, 0)
		|| !check_sprite_by_name("CH_U", sprites, 0)
		|| !check_sprite_by_name("CH_V", sprites, 0)
		|| !check_sprite_by_name("CH_W", sprites, 0)
		|| !check_sprite_by_name("CH_X", sprites, 0)
		|| !check_sprite_by_name("CH_Y", sprites, 0)
		|| !check_sprite_by_name("CH_Z", sprites, 0))
		return (0);
	return (1);
}

static int	check_player_sprites(t_sprite_storage *sprites)
{
	if (!check_sprite_by_name("INV_SLOT", sprites, 0)
		|| !check_sprite_by_name("INV_SLOT_ACTIVE", sprites, 0)
		|| !check_sprite_by_name("INV_BULLET", sprites, 0)
		|| !check_sprite_by_name("PISTOL_ICON", sprites, 0)
		|| !check_sprite_by_name("PISTOL_SHOT_1", sprites, 0)
		|| !check_sprite_by_name("PISTOL_SHOT_2", sprites, 0)
		|| !check_sprite_by_name("PISTOL_SHOT_3", sprites, 0)
		|| !check_sprite_by_name("PISTOL_SHOT_4", sprites, 0)
		|| !check_sprite_by_name("GAME_OVER_SCREEN", sprites, 0)
		|| !check_sprite_by_name("GAME_WIN_SCREEN", sprites, 0)
		|| !check_sprite_by_name("DOOR", sprites, 0)
		|| !check_sprite_by_name("TB", sprites, 0)
		|| !check_sprite_by_name("TB_EMPTY", sprites, 0)
		|| !check_sprite_by_name("TB_MINI", sprites, 0)
		|| !check_sprite_by_name("TB_MINI_EMPTY", sprites, 0))
		return (0);
	return (1);
}

static int	check_enemy_sprites(t_sprite_storage *sprites)
{
	if (!check_sprite_by_name("ENEMY_ICON", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_0", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_1", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_2", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_3", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_4", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_5", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_6", sprites, 0)
		|| !check_sprite_by_name("ENEMY_MOVE_7", sprites, 0)
		|| !check_sprite_by_name("ENEMY_ATTACK_0", sprites, 0)
		|| !check_sprite_by_name("ENEMY_ATTACK_1", sprites, 0)
		|| !check_sprite_by_name("ENEMY_ATTACK_2", sprites, 0)
		|| !check_sprite_by_name("ENEMY_ATTACK_3", sprites, 0)
		|| !check_sprite_by_name("ENEMY_ATTACK_4", sprites, 0)
		|| !check_sprite_by_name("ENEMY_ATTACK_5", sprites, 0)
		|| !check_sprite_by_name("ENEMY_DIED", sprites, 0))
		return (0);
	return (1);
}

static int	check_mandatory_sprites(t_sprite_storage *sprites)
{
	if (!check_sprite_by_name("NO", sprites, 0)
		|| !check_sprite_by_name("SO", sprites, 0)
		|| !check_sprite_by_name("WE", sprites, 0)
		|| !check_sprite_by_name("EA", sprites, 0)
		|| !check_sprite_by_name("F", sprites, 1)
		|| !check_sprite_by_name("C", sprites, 1)
		|| !check_sprite_by_name("CH_0", sprites, 0)
		|| !check_sprite_by_name("CH_1", sprites, 0)
		|| !check_sprite_by_name("CH_2", sprites, 0)
		|| !check_sprite_by_name("CH_3", sprites, 0)
		|| !check_sprite_by_name("CH_4", sprites, 0)
		|| !check_sprite_by_name("CH_5", sprites, 0)
		|| !check_sprite_by_name("CH_6", sprites, 0)
		|| !check_sprite_by_name("CH_7", sprites, 0)
		|| !check_sprite_by_name("CH_8", sprites, 0)
		|| !check_sprite_by_name("CH_9", sprites, 0)
		|| !check_sprite_by_name("CH_A", sprites, 0)
		|| !check_sprite_by_name("CH_B", sprites, 0)
		|| !check_sprite_by_name("CH_C", sprites, 0)
		|| !check_sprite_by_name("CH_D", sprites, 0)
		|| !check_sprite_by_name("CH_E", sprites, 0)
		|| !check_sprite_by_name("CH_F", sprites, 0)
		|| !check_sprite_by_name("CH_G", sprites, 0))
		return (0);
	return (1);
}

int	is_map_valid(t_map *map) 
{
	if (!map->sprites
		|| !check_mandatory_sprites(map->sprites)
		|| !check_enemy_sprites(map->sprites)
		|| !check_player_sprites(map->sprites)
		|| !check_font_sprites(map->sprites))
		return (print_error("invalid map sprites"), 0);
	return (1);
}
