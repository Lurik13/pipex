/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:59:07 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 18:12:49 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	_ft_fork(t_arg *args, int i, int argc, int *pipefd)
{
	pid_t	pid;

	ft_printf("Fork n%d\n", i - 1);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (argc == 4)
			only_one_command(pipefd, args);
		else if (i == 2)
			first_child(pipefd, args);
		else if (i == argc - 2)
			last_child(pipefd, args);
		else
			middle_child(pipefd, args);
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
	i = 2;
	while (i < argc - 1)
	{
		args->cmd = ft_split(argv[i], ' ');
		search_path(args);
		_ft_fork(args, i, argc, pipefd);
		ft_free(args);
		i++;
	}
	i = 0;
	close(pipefd[0]);
	close(pipefd[1]);
	while (i < argc - 3)
	{
		ft_printf("\x1b[38;2;0;255;0mClosing %d\e[0m\n", i + 1);
		wait(NULL);
		ft_printf("\x1b[38;2;255;0;0mClosed %d\e[0m\n", i + 1);
		i++;
	}
}

/*void	creating_pipes(int argc, char **argv, t_arg *args)
{
	int		pipefd[2];
	int		i;

	i = 2;
	while (i <= argc - 2)
	{
		if (pipe(pipefd) == -1)
		{
			perror("Pipe");
			exit(EXIT_FAILURE);
		}
		args->cmd = ft_split(argv[i], ' ');
		search_path(args);
		ft_printf("\x1b[38;2;120;0;255m%s\e[0m\n", args->cmd[0]);
		_ft_fork(args, i, argc, pipefd);
		ft_free(args);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	i = 0;
	while (i < argc - 3)
	{
		ft_printf("\x1b[38;2;0;255;0mClosing %d\e[0m\n", i + 1);
		wait(NULL);
		ft_printf("\x1b[38;2;255;0;0mClosed %d\e[0m\n", i + 1);
		i++;
	}
}*/
