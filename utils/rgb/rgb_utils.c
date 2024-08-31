/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:37:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 23:55:48 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

int	rgb_to_int(t_rgb color)
{
	return (((color.r << 16) | (color.g << 8) | color.b));
}

t_rgb	int_to_rgb(int color)
{
	t_rgb	result;

	result.r = (color >> 16) & 0xFF;
	result.g = (color >> 8) & 0xFF;
	result.b = color & 0xFF;
	return (result);
}

int	get_comma_count(char *rgb_string)
{
	int		counter;
	int		comma_count;

	comma_count = 0;
	counter = 0;
	while (rgb_string[counter])
	{
		if (rgb_string[counter] == ',')
			comma_count++;
		counter++;
	}
	return (comma_count);
}

int	check_rgb_chars(char *rgb_string)
{
	int		counter;
	char	ch;

	counter = 0;
	while (rgb_string[counter])
	{
		ch = rgb_string[counter];
		if ((ch < '0' || ch > '9') && (ch != ','))
			return (0);
		counter++;
	}
	return (1);
}
