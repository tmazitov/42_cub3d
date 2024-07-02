/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:37:49 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/14 15:00:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	int		counter;
	size_t	str_lenght;
	char	*result;

	if (!str)
		return (NULL);
	str_lenght = ft_strlen(str);
	counter = 0;
	result = malloc(sizeof(char) * (str_lenght + 1));
	if (!result)
		return (NULL);
	while (str[counter])
	{
		result[counter] = f(counter, str[counter]);
		counter++;
	}
	result[counter] = '\0';
	return (result);
}
