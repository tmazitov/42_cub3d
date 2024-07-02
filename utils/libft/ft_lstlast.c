/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:02:19 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/12 16:43:53 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *list)
{
	if (!list)
		return (NULL);
	if (list->next)
		return (ft_lstlast(list->next));
	return (list);
}

// #include <stdio.h>

// int main()
// {
// 	int counter = 0;
// 	char str[] = "timur";
// 	t_list *list = ft_lstnew(&counter);
// 	while ( counter < 5)
// 	{
// 		ft_lstadd_back(&list, ft_lstnew(&str[counter]));
// 		counter++;
// 	}
// 	t_list *last = ft_lstlast(list);
// 	printf("%s\n", (char *)(last->content));
// }