/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:01:43 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 01:17:52 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x1 - x2, 2) + (pow(y1 - y2, 2))));
}

int	max_delimeter(int value)
{
	int delim;

	delim = 10;
	while (value / delim > 0)
		delim *= 10;
	return (delim);
}