/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:35:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/29 14:10:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	sprite_line_parts_is_valid(char **line_parts, t_map *map)
{
	int	count;

	count = 0;
	while (line_parts[count])
		count++;
	if (count != 2)
		return (0);
	if (get_sprite_by_name(map->sprites, line_parts[0]))
		return (0);
	return (1);
}

char	**get_line_parts(int fd)
{
	char	*line;
	char	**result;

	line = get_next_line(fd);
	if (!line)
		return (print_error("invalid map file"), NULL);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while (*line == '\0' || is_whitespace_line(line))
	{
		free(line);
		line = get_next_line(fd);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	result = ft_split(line, ' ');
	if (!result)
		print_error("invalid memory alloc");
	free(line);
	return (result);
}

int	parse_sprites(void *mlx, t_map *map, int fd)
{
	char	**parts;
	int		stat;

	while (sprite_storage_length(map->sprites) < SPRITES_COUNT)
	{
		parts = get_line_parts(fd);
		if (!parts)
			return (0);
		if (!sprite_line_parts_is_valid(parts, map))
			return (free_split(parts), print_error("invalid sprite line"), 0);
		if (ft_strchr(parts[1], ','))
			stat = add_color_sprite(parts[0], make_rgb_by_string(parts[1]),
					map->sprites);
		else
			stat = add_texture_sprite(mlx, parts[0], parts[1], map->sprites);
		free_split(parts);
		if (!stat)
			return (0);
	}
	return (1);
}

int	parse_walls_raw(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (!ft_strchr(line, '1'))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (print_error("invalid map file"), 0);
	while (line && ft_strchr(line, '1'))
	{
		map->height += 1;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map->width = max(map->width, ft_strlen(line));
		if (!add_map_raw_item(map, line))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}

int	parse_map(void *mlx, t_map *map, char *path)
{
	int	fd;

	if (access(path, R_OK) == -1)
		return (print_error("file does not exist"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error("file does not exist"), 1);
	if (!parse_sprites(mlx, map, fd))
		return (0);
	if (!parse_walls_raw(map, fd))
		return (0);
	if (!convert_raw_to_objs(map))
		return (0);
	return (1);
}
