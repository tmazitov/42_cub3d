/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:14:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 13:19:29 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int	calc_num_lenght(int n)
{
	int	div;

	div = n / 10;
	if ((n > 0 && div > 0) || (div < 0 && n < 0))
		return (calc_num_lenght(div) + 1);
	return (1);
}

char	next_item(int num)
{
	if (num < 0)
		return (num % 10 * -1 + '0');
	return (num % 10 + '0');
}

char	*ft_itoa(int n)
{
	int		n_length;
	int		n_ctn;
	int		is_negative;
	char	*result;

	is_negative = n < 0;
	n_length = calc_num_lenght(n);
	if (is_negative)
		n_length++;
	result = malloc(sizeof(char) * (n_length + 1));
	if (!result)
		return (NULL);
	if (is_negative)
		result[0] = '-';
	n_ctn = 1;
	while ((is_negative && n_length - n_ctn > 0) || (!is_negative && n_length
			- n_ctn >= 0))
	{
		result[n_length - n_ctn] = next_item(n);
		n = n / 10;
		n_ctn++;
	}
	result[n_length] = '\0';
	return (result);
}

// int main()
// {
// 	int num = 12356789;
// 	printf("str: '%s'\n", ft_itoa(num));
// }
// } str -> *-*sof*ia*(
// set -> *-(
// }
// }