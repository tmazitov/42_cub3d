/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:11:44 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 14:58:58 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	size_t	src_len;
	int		counter;
	char	*new_str;

	src_len = ft_strlen(src);
	counter = 0;
	new_str = malloc(sizeof(char) * (src_len + 1));
	if (!new_str)
		return (0);
	while (src[counter])
	{
		new_str[counter] = src[counter];
		counter++;
	}
	new_str[counter] = '\0';
	return (new_str);
}
