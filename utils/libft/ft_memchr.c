/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:22:16 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 15:41:33 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			counter;
	unsigned char	*src_str;

	if (n == 0)
		return (NULL);
	counter = 0;
	src_str = (unsigned char *)src;
	while (counter < n)
	{
		if (src_str[counter] == (unsigned char)c)
			return (&src_str[counter]);
		counter++;
	}
	return (NULL);
}
