/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:01:08 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 12:41:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	counter;

	if (!str || !f)
		return ;
	counter = 0;
	while (str[counter])
	{
		f(counter, &str[counter]);
		counter++;
	}
}
