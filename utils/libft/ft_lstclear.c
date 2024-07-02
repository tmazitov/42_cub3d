/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:53:17 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 19:08:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	if (!list || !del)
		return ;
	if ((*list)->next)
		ft_lstclear(&((*list)->next), del);
	ft_lstdelone(*list, del);
	*list = 0;
}
