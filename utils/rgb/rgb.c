/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:42:03 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/03 14:18:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

t_rgb	*make_rgb(int r, int g, int b)
{
	t_rgb	*rgb;

	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		return (NULL);
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

static int	check_color_part(char *part)
{
	int		is_equal;
	int		part_num;
	char	*part_test;

	part_num = ft_atoi(part);
	part_test = ft_itoa(part_num);
	if (!part_test)
		return (0);
	is_equal = ft_strncmp(part, part_test, ft_strlen(part)) == 0;
	free(part_test);
	if (!is_equal)
		return (print_error("invalid color part"), 0);
	if (part_num < 0 || part_num > 255)
		return (print_error("invalid value of the color part"), 0);
	return (1);
}

static int	check_color_parts(char **color_parts)
{
	int	count;

	count = 0;
	while (color_parts[count])
		count++;
	if (count != 3)
		return (print_error("invalid color format"), 0);
	count = 0;
	while (color_parts[count])
	{
		if (!check_color_part(color_parts[count]))
			return (0);
		count++;
	}
	return (1);
}

t_rgb	*make_rgb_by_string(char *rgb_string)
{
	int	r;
	int	g;
	int	b;
	char	**color_parts;

	printf("color : %s\n", rgb_string);
	if(!rgb_string)
		return (NULL);
	color_parts = ft_split(rgb_string, ',');
	if (!color_parts)
		return (NULL);
	if (!check_color_parts(color_parts))
		return (free_split(color_parts));
	r = ft_atoi(color_parts[0]);
	g = ft_atoi(color_parts[1]);
	b = ft_atoi(color_parts[2]);
	free_split(color_parts);
	return (make_rgb(r, g, b));
}

void	*free_rgb(t_rgb *rgb)
{
	free(rgb);
	return (NULL);
}