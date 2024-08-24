/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:09:46 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 22:49:57 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static char	*get_char_image_name(char ch)
{
	char	*ch_str;
	char	*name;
	char	ch_big;

	if (ch >= 'a' && ch <= 'z')
		ch_big = ch - 32;
	else
		ch_big = ch;
	ch_str = ft_strdup(" ");
	if (!ch_str)
		return (NULL);
	ch_str[0] = ch_big;
	name = ft_strjoin("CH_", ch_str);
	free(ch_str);
	return (name);
}

int	setup_writer(t_writer *writer, t_sprite_storage *storage, char from,
		char to)
{
	char			ch;
	char			*name;
	t_image			*image;
	t_sprite_node	*node;

	if (!writer || !storage)
		return (0);
	ch = from;
	while (ch <= to)
	{
		name = get_char_image_name(ch);
		if (!name)
			return (0);
		node = get_sprite_by_name(storage, name);
		free(name);
		if (!node || !node->image || !img_scale(&node->image, 3))
			return (0);
		image = node->image;
		if (!writer_add_symbol(writer, ch, image))
			return (0);
		ch++;
	}
	return (1);
}
