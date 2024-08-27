/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:05:52 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 19:47:25 by kshamsid         ###   ########.fr       */
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
