/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:18:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/22 20:38:29 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*item;

	if (!list || !f || !del)
		return (NULL);
	res = NULL;
	while (list)
	{
		item = ft_lstnew(f(list->content));
		if (!item)
		{
			ft_lstclear(&item, del);
			return (NULL);
		}
		ft_lstadd_back(&res, item);
		list = list->next;
	}
	return (res);
}
// old  new 
//  1    1
//  2    
//  3
//  4