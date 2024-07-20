/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_double_array_create.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:29:16 by kshamsid          #+#    #+#             */
/*   Updated: 2024/07/15 22:02:45 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

//In case of overalloction with the 2d array,
//this func replaces extra NULLS with 1s.
void	replace_nulls_with_1(char *str, size_t length)
{
	size_t i;

	if (length == 0 || str == NULL)
		return ;
	i = 0;
	while (i < length - 1)
	{
		if (str[i] == '\0')
		{
			str[i] = '1';
		}
		i++;
	}
}

//ft_strlcpy just replace space with 1
static size_t ft_strlcpy_map(char *dst, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	result;

	counter = 0;
	result = ft_strlen(src);
	if (dstsize < 1)
		return (result);
	while (src[counter] && counter < dstsize - 1)
	{
		if (src[counter] == ' ')
			dst[counter] = '1';
		else
			dst[counter] = src[counter];
		counter++;
	}

	dst[counter] = '\0';
	return (result);
}

// Basic allocation of 2d array for height and width.
char	**allocate_2d_array(int width, int height)
{
	char	**array;
	int		i;

	array = (char **)calloc((height * sizeof(char *) + 1), sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		array[i] = (char *)calloc((width * sizeof(char) + 1), sizeof(char));
		if (array[i] == NULL)
		{
			free_2d_array(array, i);
			return (NULL);
		}
		i++;
	}
	array[height] = NULL;
	return (array);
}

// Main double array creation function
char	**map_double_array_create(t_map *map)
{
	t_map_raw_list	*temp;
	int				i;

	map->map_double_array = allocate_2d_array(map->width, map->height);
	if (!map->map_double_array)
		return (NULL);
	temp = map->raw;
	i = 0;
	while (temp)
	{
		ft_strlcpy_map(map->map_double_array[i], temp->value, map->width);
		replace_nulls_with_1(map->map_double_array[i], map->width);
		temp = temp->next;
		i++;
	}
	return (map->map_double_array);
}

// Basic free of 2d array
void	free_2d_array(char **array, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
