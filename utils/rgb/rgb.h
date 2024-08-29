/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:42:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/29 14:28:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include "../error/error.h"
# include "../libft/libft.h"
# include <stdlib.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}		t_rgba;

t_rgb	*make_rgb(int r, int g, int b);
t_rgb	*make_rgb_by_string(char *rgb_string);
int		rgb_to_int(t_rgb color);
t_rgb	int_to_rgb(int color);
int		get_comma_count(char *rgb_string);
int 	check_rgb_chars(char *rgb_string);
void	*free_rgb(t_rgb *rgb);

#endif // !RGB_H