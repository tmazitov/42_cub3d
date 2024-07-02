/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:31:49 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 15:00:45 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	int		counter;
	size_t	length;
	char	*result;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	length = ft_strlen(s1);
	while (length > start && ft_strchr(set, s1[length - 1]))
		length--;
	result = malloc(sizeof(char) * (length - start + 1));
	if (!result)
		return (NULL);
	counter = 0;
	while (start < length)
		result[counter++] = s1[start++];
	result[counter] = '\0';
	return (result);
}
