# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/29 23:58:22 by tmazitov          #+#    #+#              #
#    Updated: 2024/07/11 23:57:02 by tmazitov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS =  cmd/main.c \
        game/game.c \
        game/minimap/minimap.c \
        game/minimap/minimap_camera.c \
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
        game/player/player_move.c \
        game/player/player_rotate.c \
        game/player/player_icon.c \
        game/player/player_control.c \
        game/player/player_acceleration.c \
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
        utils/geometry/vector.c \
        utils/geometry/line.c \
        utils/geometry/line_intersection.c \
        utils/geometry/utils.c \
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
        utils/libft/ft_itoa.c

OBJS = $(SRCS:.c=.o)

NAME = cub3d
OS = $(shell uname)

.PHONY: all clean fclean re

ifeq ($(OS), Linux)
    CFLAGS += -I/usr/include -Imlx_linux -O3
    LDFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

else ifeq ($(OS), Darwin)
    CFLAGS += -Imlx -I./mlx_mac
    LDFLAGS += -L./mlx_mac -lmlx -framework OpenGL -framework AppKit
    
    # Modify B_BUTTON for macOS
    CFLAGS += -DW_BUTTON=1  # Assuming B_BUTTON should be 1 on macOS
    CFLAGS += -DA_BUTTON=0  # Assuming B_BUTTON should be 1 on macOS
    CFLAGS += -DS_BUTTON=13  # Assuming B_BUTTON should be 1 on macOS
    CFLAGS += -DD_BUTTON=2  # Assuming B_BUTTON should be 1 on macOS
    CFLAGS += -DLEFT_ARROW=123
    CFLAGS += -DRIGHT_ARROW=124
else
    $(error Unsupported operating system: $(OS))
endif

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

