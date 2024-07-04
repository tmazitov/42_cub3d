/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:15:08 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/04 15:38:42 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>

# include "../geometry/geometry.h"

typedef struct s_image
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		height;
	int		width;
	void	*content;
	int		*buffer;
	void	*mlx;
}			t_image;

t_image	*make_image(void *mlx);
void	*free_image(t_image *image);

int		img_create(t_image *img, int width, int height);
int		img_load(t_image *img, char *path);
void	img_clear(t_image *img);

int		*img_buffer(t_image *image);
void	img_draw(void *win, t_image *img, int x, int y);
void 	img_put_pixel(t_image *img, int color, int x, int y);
void	img_put_line(t_image *img, int color, t_point p1, t_point p2);
void	img_put_rectangle(t_image* img, t_rectangle rect, int color);

#endif // !IMAGE_H