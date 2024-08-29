/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:08:33 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/29 14:10:18 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	is_white_space(char ch)
{
	return (ft_strchr(" \t\n\r\v\f", ch) != NULL);
}

int	is_whitespace_line(char *line)
{
	int	counter;

	counter = 0;
	while (line[counter])
	{
		if (!is_white_space(line[counter]))
			return (0);
		counter++;
	}
	return (1);
}
