/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:15:08 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/28 07:38:40 by tmazitov         ###   ########.fr       */
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


typedef struct s_anime_frame
{
	t_image					*image;
	int						duration;
	struct s_anime_frame	*next;
}			t_anime_frame;

typedef struct s_anime
{
	t_anime_frame	*frames;
	t_anime_frame	*current_frame;
	int				frame_count;
	int				iter;
	int				duration;
}			t_anime;


/* IMAGE */


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


/* ANIMATION PART */
/* Provide you to create your own animation.
-----------------------------------------------------------
Using function `make_anime` you can create (with memory allocation) animation instance. 
To add an animation frame you can use `anime_add_frame` with animation instance, image and 
future frame duration. To free allocated memory of an animation instance you can use `free_anime`. 
*/

// IS_FREE_FRAME_IMAGE - if you want to free image when free frame
# ifndef IS_FREE_FRAME_IMAGE
	# define IS_FREE_FRAME_IMAGE 0
# endif

t_anime	*make_anime();
void	*free_anime(t_anime *anime);

t_anime	*anime_copy(t_anime *anime);
int		anime_add_frame(t_anime *anime, t_image *image, int duration);
t_image	*anime_current_frame(t_anime *anime);
void	*free_frame(t_anime_frame *frame);


#endif // !IMAGE_H