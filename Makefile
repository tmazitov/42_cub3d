# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/29 23:58:22 by tmazitov          #+#    #+#              #
#    Updated: 2024/06/30 16:56:51 by tmazitov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm

SRCS = ./cmd/main.c \
		./game/game.c \
		./game/minimap/minimap.c \
		./game/minimap/minimap_update.c \
		./game/minimap/minimap_update_image.c \
		./game/render/render.c \
		./game/render/render_minimap.c \
		./game/scene/scene.c \
		./utils/image/image.c \
		./utils/image/image_buffer.c \
		./utils/image/image_content.c \
		./utils/image/image_draw.c \
		./utils/image/image_fill.c 

OBJS = $(SRCS:.c=.o)

NAME = cub3d

.PHONY: all clean

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

re: clean all

clean:
	rm -f $(OBJS) $(TARGET)