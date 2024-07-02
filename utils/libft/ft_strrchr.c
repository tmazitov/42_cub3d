/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:46:19 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/06 21:33:26 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int ch)
{
	int		counter;
	char	*result;

	result = 0;
	counter = 0;
	while (str[counter])
	{
		if (str[counter] == ch)
			result = (char *)str + counter;
		counter++;
	}
	if (str[counter] == ch)
		result = (char *)str + counter;
	return (result);
}
