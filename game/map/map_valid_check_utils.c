/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:57:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/09/01 00:25:09 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	check_sprite_by_name(char *name, t_sprite_storage *sprites, int is_color)
{
	t_sprite_node	*sprite;

	if (!name || !sprites)
		return (0);
	sprite = get_sprite_by_name(sprites, name);
	if (!sprite
		|| (is_color && !sprite->color)
		|| (!is_color && !sprite->image))
	{
		printf("\xE2\x9D\x8C - '%s' not found or invalid\n", name);
		return (0);
	}
	printf("\xE2\x9C\x85 - '%s' sprite successfully parsed\n", name);
	return (1);
}

int is_allowed_char(char ch)
{
	return (!!ft_strchr(" 01NEWSZBD", ch));
}