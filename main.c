/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:27:37 by lribette          #+#    #+#             */
/*   Updated: 2024/01/15 11:49:26 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	check_files(char *argv)
{
	int	fd;
	
	fd = access(argv, R_OK & W_OK & X_OK);
	if (fd == -1)
		perror("Error");
	else
		printf("Pass");
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;
	(void)argv;

	if (argc == 5)
	{
		fd1 = check_files(argv[1]);
		fd2 = check_files(argv[4]);
		printf("C'est bon");
		if (execve(argv[2], argv, envp) == -1)
			perror("Can't execve");
	}
	else
		printf("Wrong number of args");
}
