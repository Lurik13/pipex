/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:46:28 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 11:02:49 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READING 0
# define WRITING 1

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
	int		stdout_backup;
}	t_arg;

int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
void	search_path(t_arg *args);
void	creating_pipes(int argc, char **argv, t_arg *args);
void	first_child(int *pipefd, t_arg *args);
void	last_child(int *pipefd, t_arg *args);
void	ft_free(t_arg *args);

#endif