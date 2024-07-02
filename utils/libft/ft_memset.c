/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:26:08 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/06 21:25:43 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	counter;
	char	*temp;

	counter = 0;
	temp = (char *)str;
	while (counter < len)
	{
		temp[counter] = (unsigned char)c;
		counter++;
	}
	return (str);
}
