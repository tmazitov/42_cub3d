/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:35:15 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/07 19:18:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_str;
	const char	*src_str;
	size_t		counter;

	if (!dst && !src)
		return (0);
	dst_str = (char *)dst;
	src_str = (char *)src;
	counter = 0;
	while (counter < n)
	{
		dst_str[counter] = src_str[counter];
		counter++;
	}
	return (dst);
}
