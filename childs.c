/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:55:54 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 16:11:09 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	only_one_command(int *pipefd, t_arg *args)
{
	int		i;

	i = 0;
	close(pipefd[WRITING]);
	if (dup2(args->in, STDIN_FILENO) == -1
		|| dup2(args->out, STDOUT_FILENO) == -1)
		perror("Dup error One");
	close(pipefd[READING]);
	close(args->in);
	close(args->out);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	perror("Invalid command");
	exit(EXIT_FAILURE);
}

void	first_child(int *pipefd, t_arg *args)
{
	int		i;

	i = 0;
	close(pipefd[READING]);
	if (dup2(args->in, STDIN_FILENO) == -1
		|| dup2(pipefd[WRITING], STDOUT_FILENO) == -1)
		perror("Dup error First");
	dprintf(2, "\x1b[38;2;50;200;255mJe suis preumssss\e[0m\n");
	close(pipefd[WRITING]);
	close(args->in);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	perror("Invalid command");
	exit(EXIT_FAILURE);
}

void	middle_child(int *pipefd, t_arg *args)
{
	int	i;

	i = 0;
	if (dup2(pipefd[READING], STDIN_FILENO) == -1
		|| dup2(pipefd[WRITING], STDOUT_FILENO) == -1)
		perror("Dup error Middle");
	dprintf(2, "\x1b[38;2;200;200;255mJe suis au miliiiiiiieu\e[0m\n");
	close(pipefd[READING]);
	close(pipefd[WRITING]);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	perror("Invalid command");
	exit(EXIT_FAILURE);
}

void	last_child(int *pipefd, t_arg *args)
{
	int		i;

	i = 0;
	close(pipefd[WRITING]);
	if (dup2(pipefd[READING], STDIN_FILENO) == -1
		|| dup2(args->out, STDOUT_FILENO) == -1)
		perror("Dup error Last");
	dprintf(2, "\x1b[38;2;50;200;255mJe suis laaaaast\e[0m\n");
	close(pipefd[READING]);
	close(args->out);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	perror("Invalid command");
	exit(EXIT_FAILURE);
}
