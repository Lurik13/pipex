/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:46:04 by lribette          #+#    #+#             */
/*   Updated: 2024/01/17 14:29:54 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	writefd(int fd, char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

int	main(void)
{
	pid_t	pid[3];
	char	c;
	int		pipefd[2];
	int		status;
	int		i;

	i = 0;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (i < 3)
	{
		printf("Fork ici.\n");
		pid[i] = fork();
		if (pid[i] == -1)
			return (1);
		if (pid[i] == 0)
		{
			close(pipefd[1]);
			while (read(pipefd[0], &c, 1) > 0)
				write(STDOUT_FILENO, &c, 1);
			close(pipefd[0]);
			exit(0);
		}
		else if (pid[i] > 0)
		{
			close(pipefd[0]);
			writefd(STDOUT_FILENO, "Salute\n");
			writefd(pipefd[1], "\x1b[38,2,255,255,0mYes j'y suis arrive !\e[0m\n");
			close(pipefd[1]);
			waitpid(pid[i], &status, 0);
			writefd(STDOUT_FILENO, "Recu\n");
			exit(0);
		}
		i++;
	}
	printf("Pere: J'ai tue tous mes enfants mouahahahahahhahaahahahahahahahahahaha\n");
}
