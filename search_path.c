/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:53:30 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 11:04:04 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*_ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*str;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	j = -1;
	str = malloc(len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

static int	_search_path_line(t_arg *args)
{
	int	i;

	i = 0;
	while (args->envp[i])
	{
		if (args->envp[i][0] == 'P' && args->envp[i][1] == 'A'
			&& args->envp[i][2] == 'T' && args->envp[i][3] == 'H'
			&& args->envp[i][4] == '=')
			return (i);
		i++;
	}
	ft_printf("No path\n");
	exit(EXIT_FAILURE);
}

void	search_path(t_arg *args)
{
	int	i;
	int	j;

	i = _search_path_line(args);
	args->path = ft_split(args->envp[i] + 5, ':');
	j = 0;
	if (!args->path[j])
	{
		ft_printf("No path\n");
		exit(EXIT_FAILURE);
	}
	while (args->path[j])
	{
		args->path[j] = _ft_strjoin(args->path[j], "/");
		args->path[j] = _ft_strjoin(args->path[j], args->cmd[0]);
		j++;
	}
}
