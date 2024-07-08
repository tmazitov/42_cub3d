/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:46:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/08 15:04:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"


void img_put_pixel(t_image *img, int color, int x, int y)
{
	int	rel_pixel_index;

	if (!img)
		return ;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	rel_pixel_index =  (y * img->line_bytes) + x;
	img->buffer[rel_pixel_index] = color;
}

void plot(t_image *img, int color, double x, double y, double brightness) {
    if (x < 0 || x >= img->width || y < 0 || y >= img->height) {
        return;
    }
    int alpha = (int)(brightness * 255.0);
    int inv_alpha = 255 - alpha;
    int original_color = img->buffer[(int)y * img->line_bytes + (int)x];
    
    // Separate RGB channels
    int original_r = (original_color >> 16) & 0xFF;
    int original_g = (original_color >> 8) & 0xFF;
    int original_b = original_color & 0xFF;
    
    int new_r = (color >> 16) & 0xFF;
    int new_g = (color >> 8) & 0xFF;
    int new_b = color & 0xFF;

    // Blend colors
    int final_r = (new_r * alpha + original_r * inv_alpha) / 255;
    int final_g = (new_g * alpha + original_g * inv_alpha) / 255;
    int final_b = (new_b * alpha + original_b * inv_alpha) / 255;
    int final_color = (final_r << 16) | (final_g << 8) | final_b;
    
    img_put_pixel(img, final_color, (int)x, (int)y);
    
    // Debug output
    // printf("plot : %f %f %d %08x\n", x, y, alpha, final_color);
}

void img_put_line(t_image *img, int color, t_point p1, t_point p2) {
    int steep = fabs(p2.y - p1.y) > fabs(p2.x - p1.x);

    if (steep) {
        double temp = p1.x;
        p1.x = p1.y;
        p1.y = temp;
        temp = p2.x;
        p2.x = p2.y;
        p2.y = temp;
    }
    if (p1.x > p2.x) {
        double temp = p1.x;
        p1.x = p2.x;
        p2.x = temp;
        temp = p1.y;
        p1.y = p2.y;
        p2.y = temp;
    }

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double gradient = dy / dx;

    // Handle first endpoint
    double xend = round(p1.x);
    double yend = p1.y + gradient * (xend - p1.x);
    double xgap = rfpart(p1.x + 0.5);
    double xpxl1 = xend;
    double ypxl1 = floor(yend);

    if (steep) {
        plot(img, color, ypxl1, xpxl1, rfpart(yend) * xgap);
        plot(img, color, ypxl1 + 1, xpxl1, fpart(yend) * xgap);
    } else {
        plot(img, color, xpxl1, ypxl1, rfpart(yend) * xgap);
        plot(img, color, xpxl1, ypxl1 + 1, fpart(yend) * xgap);
    }

    double intery = yend + gradient;

    // Handle second endpoint
    xend = round(p2.x);
    yend = p2.y + gradient * (xend - p2.x);
    xgap = fpart(p2.x + 0.5);
    double xpxl2 = xend;
    double ypxl2 = floor(yend);

    if (steep) {
        plot(img, color, ypxl2, xpxl2, rfpart(yend) * xgap);
        plot(img, color, ypxl2 + 1, xpxl2, fpart(yend) * xgap);
    } else {
        plot(img, color, xpxl2, ypxl2, rfpart(yend) * xgap);
        plot(img, color, xpxl2, ypxl2 + 1, fpart(yend) * xgap);
    }

    // Main loop
    if (steep) {
        for (double x = xpxl1 + 1; x < xpxl2; x++) {
            plot(img, color, floor(intery), x, rfpart(intery));
            plot(img, color, floor(intery) + 1, x, fpart(intery));
            intery = intery + gradient;
        }
    } else {
        for (double x = xpxl1 + 1; x < xpxl2; x++) {
            plot(img, color, x, floor(intery), rfpart(intery));
            plot(img, color, x, floor(intery) + 1, fpart(intery));
            intery = intery + gradient;
        }
    }
}

void	img_put_rectangle(t_image* img, t_rectangle rect, int color)
{
	int	x;
	int	y;

	y = rect.start.y;
	while (y != rect.start.y + rect.height)
	{
		x = rect.start.x;
		while (x != rect.start.x + rect.width)
		{
			img_put_pixel(img, color, x, y);
			x++;
		}
		y++;
	}
}

void img_put_img(t_image *dest, t_image *src, t_point pos, double angle)
{
    int x, y;
    int dest_x, dest_y;
    int color;
    int new_x, new_y;

    double rad = angle * PI / 180.0;
    
    int cx = src->width / 2;
    int cy = src->height / 2;

    int src_x, src_y;

    for (y = 0; y < src->height; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            src_x = x - cx;
            src_y = y - cy;
            
            // Rotate the pixel
            new_x = (int)(src_x * cos(rad) - src_y * sin(rad)) + cx;
            new_y = (int)(src_x * sin(rad) + src_y * cos(rad)) + cy;

            // Calculate the destination position
            dest_x = new_x + pos.x;
            dest_y = new_y + pos.y;

            // Ensure the new coordinates are within the destination image bounds
            if (new_x >= 0 && new_x < src->width && new_y >= 0 && new_y < src->height)
            {
                color = img_get_pixel(src, x, y);
                if (color != 0xff000000)  // Assuming 0xff000000 is the transparent color
                {
                    img_put_pixel(dest, color, dest_x, dest_y);
                }
            }
        }
    }
}