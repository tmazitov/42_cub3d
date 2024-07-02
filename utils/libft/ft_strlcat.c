/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:25:24 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 16:16:15 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_size <= dst_len)
		return (dst_size + src_len);
	if (dst_size - dst_len <= src_len)
	{
		ft_memcpy(dst + dst_len, src, dst_size - 1);
		dst[dst_size - 1] = '\0';
	}
	else
		ft_memcpy(dst + dst_len, src, src_len + 1);
	return (src_len + dst_len);
}
