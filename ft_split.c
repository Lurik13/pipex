/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:19:02 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 10:57:49 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_count_words(char *s, char c)
{
	unsigned int	number;
	unsigned int	i;
	unsigned int	isword;

	number = 0;
	i = -1;
	isword = 0;
	while (s[++i])
	{
		if (s[i] != c && isword == 0)
		{
			number++;
			isword = 1;
		}
		else if (s[i] == c && isword == 1)
			isword = 0;
	}
	return (number);
}

static char	*ft_worddup(char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		index;

	split = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = ft_worddup(s, index, i);
			index = -1;
		}
	}
	split[j] = 0;
	return (split);
}
