/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:48:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 21:07:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_font_print.h"

t_symbol	*make_symbol(char ch, t_image *image)
{
	t_symbol	*symbol;

	symbol = malloc(sizeof(t_symbol));
	if (!symbol)
		return (NULL);
	symbol->symbol = ch;
	symbol->image = image;
	symbol->next = NULL;
	return (symbol);
}

void	*free_symbol(t_symbol *symbol)
{
	if (!symbol)
		return (NULL);
	if (symbol->next)
		free_symbol(symbol->next);
	free(symbol);
	return (NULL);
}
