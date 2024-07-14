/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:15:08 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 00:06:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../geometry/geometry.h"
# include "../error/error.h"

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

typedef struct s_image_border
{
	int	size;
	int color;
	int radius;
}		t_image_border;

t_image	*make_image(void *mlx);
void	*free_image(t_image *image);

int		img_create(t_image *img, int width, int height);
int		img_load(t_image *img, char *path);
void	img_clear(t_image *img);
int		img_scale(t_image **img, int scale);

int		*img_buffer(t_image *image);
void	img_draw(void *win, t_image *img, int x, int y);
int		img_get_pixel(t_image *img, int x, int y);

void	img_put_img(t_image *dest, t_image *src, t_point pos, double angle);
void	img_put_line(t_image *img, int color, t_point p1, t_point p2);
void 	img_put_pixel(t_image *img, int color, int x, int y);
void	img_put_rectangle(t_image* img, t_rectangle rect, int color);

void	img_paint_border(t_image *image, t_image_border border);

#endif // !IMAGE_H