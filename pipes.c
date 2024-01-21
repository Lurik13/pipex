/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:07 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 11:05:41 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	_ft_fork(t_arg *args, int i, int argc, int *pipefd)
{
	pid_t	pid;

	ft_printf("Fork n%d\n", i);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (i + 1 < argc - 3)
			first_child(pipefd, args);
		else
			last_child(pipefd, args);
	}
}

void	creating_pipes(int argc, char **argv, t_arg *args)
{
	int		pipefd[2];
	int		i;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < argc - 3)
	{
		args->cmd = ft_split(argv[i + 2], ' ');
		search_path(args);
		_ft_fork(args, i, argc, pipefd);
		ft_free(args);
		i++;
	}
	i = 0;
	close(pipefd[0]);
	close(pipefd[1]);
	while (i++ < argc - 3)
		wait(NULL);
}
