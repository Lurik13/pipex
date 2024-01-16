/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:19:02 by lribette          #+#    #+#             */
/*   Updated: 2024/01/16 14:19:37 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	words_count(char *str)
{
	int	i;
	int	number_of_words;

	i = 0;
	number_of_words = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		while (str[i] && !is_space(str[i]))
			i++;
		if (!str[i] && is_space(str[i - 1]))
			continue ;
		else
			number_of_words++;
	}
	return (number_of_words);
}

char	*ft_word_dup(char *str, int start, int end)
{
	int		i;
	char	*dup;
	
	i = 0;
	dup = malloc((end - start + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (end > start)
		dup[i++] = str[start++];
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		start;
	char	**split;

	i = 0;
	j = -1;
	start = 0;
	split = malloc((words_count(str) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (++j < words_count(str))
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i])
			start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		split[j] = ft_word_dup(str, start, i);
	}
	split[j] = NULL;
	return (split);
}