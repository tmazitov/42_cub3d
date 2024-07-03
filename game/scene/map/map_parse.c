/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:35:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/03 14:13:33 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int		check_sprite_line(char	**line_parts)
{
	int	count;

	count = 0;
	while (line_parts[count])
		count++;
	if (count != 2)
		return (0);
	return (1);
}

int		parse_sprites(void *mlx, t_map *map, int fd)
{
	char	*line;
	char	**line_parts;
	int		is_created;
	
	while (sprite_storage_length(map->sprites) < SPRITES_COUNT)
	{
		line = get_next_line(fd);
		if (!line)
			return (print_error("invalid map file"), 0);
		if (*line == '\n')
		{
			free(line);
			continue;
		}
		line[ft_strlen(line) - 1] = '\0';
		line_parts = ft_split(line, ' ');
		free(line);
		if (!line_parts)
			return (print_error("invalid memory alloc"), 1);
		if (!check_sprite_line(line_parts))
			return (free_split(line_parts), print_error("invalid sprite line"), 0);
		if (ft_strchr(line_parts[1], ','))
			is_created = add_color_sprite(line_parts[0], \
				make_rgb_by_string(line_parts[1]), map->sprites);
		else
			is_created = add_texture_sprite(mlx, line_parts[0], line_parts[1], \
				map->sprites);
		free_split(line_parts);
		if (!is_created)
			return (0);
		printf("\t-- %s sprite added\n", get_last_sprite(map->sprites)->name);
	}
	return (1);
}

int		parse_map(void *mlx, t_map *map, char *path)
{
	int		fd;

	if (access(path, R_OK) == -1)
		return (print_error("file does not exist"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error("file does not exist"), 1);
	if (!parse_sprites(mlx, map, fd))
		return (0);
	return (1);
}