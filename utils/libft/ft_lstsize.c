/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:44:47 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 16:01:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst->next)
		return (ft_lstsize(lst->next) + 1);
	return (1);
}

// int main()
// {
// 	int counter = 0;
// 	t_list *list = ft_lstnew(&counter);
// 	while ( counter < 5)
// 	{
// 		ft_lstadd_front(&list, ft_lstnew(&counter));
// 		counter++;
// 	}
// 	printf("%d\n", ft_lstsize(list));
// }