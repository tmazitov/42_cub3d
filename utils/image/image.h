/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:15:08 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/02 18:27:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>

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

int		*img_buffer(t_image *image);
void	img_draw(void *win, t_image *img, int x, int y);
void 	img_put_pixel(t_image *img, int color, int x, int y);
#endif // !IMAGE_H