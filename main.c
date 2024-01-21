/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:27:37 by lribette          #+#    #+#             */
/*   Updated: 2024/01/21 11:16:25 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	_check_files(int argc, char **argv, t_arg *args)
{
	args->in = open(argv[1], O_RDONLY, 0666);
	args->out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (args->in == -1 || args->out == -1)
	{
		ft_printf("Invalid file\n");
		exit(1);
	}
}

void	ft_free(t_arg *args)
{
	int	i;

	i = 0;
	while (args->path[i])
		free(args->path[i++]);
	free(args->path);
	i = 0;
	while (args->cmd[i])
		free(args->cmd[i++]);
	free(args->cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	args;

	if (argc > 3)
	{
		_check_files(argc, argv, &args);
		args.envp = envp;
		creating_pipes(argc, argv, &args);
	}
	else
		ft_printf("Wrong number of args\n");
}

//prendre en compte s'il n'y a pas de pipe a faire

//faire le premier bonus