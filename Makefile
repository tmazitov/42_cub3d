# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/29 23:58:22 by tmazitov          #+#    #+#              #
#    Updated: 2024/07/06 17:04:01 by tmazitov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS =	cmd/main.c \
		game/game.c \
		game/minimap/minimap.c \
		game/minimap/minimap_update.c \
		game/minimap/minimap_update_image.c \
		game/update/update.c \
		game/update/update_player.c \
		game/update/update_minimap.c \
		game/render/render.c \
		game/render/render_minimap.c \
		game/scene/scene.c \
		game/objs/wall/wall.c \
		game/player/player.c \
		game/player/player_icon.c \
		game/player/player_control.c \
		game/player/player_behavior.c \
		game/map/map.c \
		game/map/map_raw.c \
		game/map/map_parse.c \
		game/map/map_textures.c \
		game/map/map_textures_utils.c \
		game/map/map_walls.c \
		utils/image/image.c \
		utils/image/image_buffer.c \
		utils/image/image_content.c \
		utils/image/image_draw.c \
		utils/image/image_get.c \
		utils/image/image_put.c \
		utils/error/error.c \
		utils/geometry/point.c \
		utils/rgb/rgb.c \
		utils/gnl/get_next_line.c \
		utils/gnl/get_next_line_utils.c \
		utils/libft/ft_memcpy.c \
		utils/libft/ft_isdigit.c \
		utils/libft/ft_strlen.c \
		utils/libft/ft_strlcpy.c \
		utils/libft/ft_strlcat.c \
		utils/libft/ft_strchr.c \
		utils/libft/ft_strrchr.c \
		utils/libft/ft_strdup.c \
		utils/libft/ft_strncmp.c \
		utils/libft/ft_strnstr.c \
		utils/libft/ft_atoi.c \
		utils/libft/ft_substr.c \
		utils/libft/ft_strjoin.c \
		utils/libft/ft_memset.c \
		utils/libft/ft_bzero.c \
		utils/libft/ft_calloc.c \
		utils/libft/ft_split.c \
		utils/libft/ft_itoa.c \

OBJS = $(SRCS:.c=.o)

NAME = cub3d

.PHONY: all clean

all: $(NAME)

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

re: fclean all

clean:
	rm -f $(OBJS) $(TARGET)

fclean: clean
	rm -rf $(NAME)
	