/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:53:53 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 13:21:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_nbr(int num, int fd)
{
	int	div;
	int	mod;

	div = num / 10;
	mod = num % 10;
	if ((num > 0 && div > 0) || (num < 0 && div < 0))
		print_nbr(div, fd);
	if (mod < 0)
		mod *= -1;
	ft_putchar_fd('0' + mod, fd);
}

void	ft_putnbr_fd(int num, int fd)
{
	if (num < 0)
		ft_putchar_fd('-', fd);
	print_nbr(num, fd);
}
