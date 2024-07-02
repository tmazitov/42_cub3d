/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:07:14 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/03 20:14:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	*ft_calloc(size_t length, size_t type_size)
{
	void	*mem;

	mem = malloc(type_size * length);
	if (!mem)
		return (NULL);
	ft_bzero(mem, length * type_size);
	return (mem);
}
