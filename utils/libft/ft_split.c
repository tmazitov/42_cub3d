/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:37:22 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/02 20:56:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	calc_words_count(char const *str, char ch)
{
	int	counter;
	int	word_counter;

	word_counter = 0;
	counter = 0;
	while (str[counter])
	{
		if (str[counter] && str[counter] == ch)
			counter++;
		if (str[counter] && str[counter] != ch)
			word_counter++;
		while (str[counter] && str[counter] != ch)
			counter++;
	}
	return (word_counter);
}

int	next_str_len(char const *str, char ch)
{
	int	counter;

	counter = 0;
	while (str[counter] && str[counter] != ch)
		counter++;
	return (counter);
}

void	skip_space(char const *str, int *index, char ch)
{
	while (str[*index] && str[*index] == ch)
		(*index)++;
}

void	*free_split(char **result)
{
	int	counter;

	if (!result)
		return (NULL);
	counter = 0;
	while (result[counter])
		free(result[counter++]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *str, char ch)
{
	int		wrd_ctn;
	int		ctn;
	int		str_ctn;
	char	**result;

	if (!str)
		return (NULL);
	result = malloc((calc_words_count(str, ch) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	wrd_ctn = 0;
	str_ctn = 0;
	while (str[str_ctn])
	{
		skip_space(str, &str_ctn, ch);
		ctn = next_str_len(str + str_ctn, ch);
		if (ctn == 0)
			continue ;
		result[wrd_ctn] = ft_substr(str, str_ctn, ctn);
		if (!result[wrd_ctn++])
			return (free_split(result));
		str_ctn += ctn;
	}
	result[wrd_ctn] = 0;
	return (result);
}

// int main()
// {
// 	char *str = "a:ba  a";
// 	char *del = ": ";
// 	char **res = ft_split(str, del);
// 	int	counter = 0;
// 	while (res[counter])
// 	{
// 		printf("%s\n", res[counter]);
// 		counter++;
// 	}
// }