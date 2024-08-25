/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:37:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 19:41:01 by tmazitov         ###   ########.fr       */
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
