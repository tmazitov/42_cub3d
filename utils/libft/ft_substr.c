/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:47:26 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 15:01:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	counter;
	size_t	str_len;
	size_t	sub_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (start + len <= str_len)
		sub_len = len;
	else if (str_len - 1 < start)
		sub_len = 0;
	else
		sub_len = str_len - start;
	sub_str = malloc(sizeof(char) * (sub_len + 1));
	if (!sub_str)
		return (NULL);
	counter = 0;
	while (counter < sub_len && str[counter + start])
	{
		sub_str[counter] = str[counter + start];
		counter++;
	}
	sub_str[sub_len] = '\0';
	return (sub_str);
}
