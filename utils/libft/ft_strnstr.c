/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:49:44 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 16:18:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;
	int		substr_is_same;
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	counter = 0;
	substr_is_same = 0;
	while (big[counter] && counter < len)
	{
		if (big[counter] == little[0])
		{
			substr_is_same = ft_strncmp(&big[counter], little, little_len);
			if (substr_is_same == 0 && counter + little_len <= len)
				return (&((char *)big)[counter]);
		}
		counter++;
	}
	return (0);
}
