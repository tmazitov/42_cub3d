/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:00:52 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/22 19:22:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memres(int n1, int n2)
{
	if (n1 - n2 > 0)
		return (1);
	if (n1 - n2 < 0)
		return (-1);
	return (0);
}

int	ft_memcmp(const void *memptr1, const void *memptr2, size_t num)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			counter;

	str1 = (unsigned char *)memptr1;
	str2 = (unsigned char *)memptr2;
	counter = 0;
	while (counter < num)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
		counter++;
	}
	return (0);
}
