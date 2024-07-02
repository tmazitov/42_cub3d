/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:42:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/02 19:19:57 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "../error/error.h"

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

t_rgb	*make_rgb(int r, int g, int b);
t_rgb	*make_rgb_by_string(char *rgb_string);
void	*free_rgb(t_rgb *rgb);

#endif // !RGB_H