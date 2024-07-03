/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:25:02 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/03 14:07:05 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_error(char *support_message)
{
	(void)!write(2, "error: ", 7);
	(void)!write(2, support_message, ft_strlen(support_message));
	(void)!write(2, "\n", 1);
}