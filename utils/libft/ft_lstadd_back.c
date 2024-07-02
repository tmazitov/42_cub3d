/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:19:23 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 19:16:30 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*last;

	if (!list)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = ft_lstlast(*list);
	if (!last)
		return ;
	last->next = new;
}

// #include <stdio.h>

// int main()
// {
// 	int counter = 0;
// 	t_list *list = ft_lstnew(&counter);
// 	while ( counter < 5)
// 	{
// 		ft_lstadd_back(&list, ft_lstnew(&counter));
// 		counter++;
// 	}
// 	printf("%d\n", ft_lstsize(list));
// }