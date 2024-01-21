/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 10:55:54 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 11:06:05 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *pipefd, t_arg *args)
{
	int		i;

	i = 0;
	close(pipefd[READING]);
	if (dup2(args->in, STDIN_FILENO) == -1
		|| dup2(pipefd[WRITING], STDOUT_FILENO) == -1)
		perror("Dup error First\n");
	close(pipefd[WRITING]);
	close(args->in);
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
		perror("Dup error Last\n");
	close(pipefd[READING]);
	close(args->out);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	perror("Invalid command");
	exit(EXIT_FAILURE);
}
