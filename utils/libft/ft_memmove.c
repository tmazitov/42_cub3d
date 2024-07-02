/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:05:52 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 15:33:30 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	size_t	counter;

	if (!src && !dst) 
		return (dst);
	counter = 0;
	if (src > dst)
	{
		ft_memcpy(dst, src, num);
		return (dst);
	}
	while (num > 0)
	{
		num--;
		*((char *)dst + num) = *((char *)src + num);
	}
	return (dst);
}
