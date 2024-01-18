/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:46:28 by lribette          #+#    #+#             */
/*   Updated: 2024/01/18 18:20:32 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include "./ft_printf/ft_printf.h"

typedef struct s_arg
{
	int		in;
	char	**path;
	char	**cmd;
	char	**envp;
	int		out;
}	t_arg;

char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);

#endif