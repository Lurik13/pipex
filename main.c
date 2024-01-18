/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:27:37 by lribette          #+#    #+#             */
/*   Updated: 2024/01/18 19:10:15 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(char *argv)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Invalid file\n");
		exit(1);
	}
	return (fd);
}

void	search_path(t_arg *args)
{
	int	i;
	int	j;

	i = 0;
	while (args->envp[i])
	{
		if (args->envp[i][0] == 'P' && args->envp[i][1] == 'A' && args->envp[i][2] == 'T'
			&& args->envp[i][3] == 'H' && args->envp[i][4] == '=')
		{
			j = 0;
			while (j != 5)
				j++;
			args->path = ft_split(args->envp[i] + j, ':');
			j = 0;
			while (args->path[j])
			{
				args->path[j] = ft_strjoin(args->path[j], "/");
				args->path[j] = ft_strjoin(args->path[j], args->cmd[0]);
				j++;
			}
		}
		i++;
	}
}

void	child(int *pipefd, t_arg *args)
{
	int		i;

	i = 0;
	close(pipefd[1]);
	dup2(args->in, STDIN_FILENO);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	//dup2(args->out, STDOUT_FILENO);
	close(pipefd[0]);
	exit(0);
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

void	creating_pipes(int argc, char **argv, t_arg *args)
{
	(void)argc;
	int		pipefd[2];
	pid_t	pid;
	int		status;
	
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
	args->cmd = ft_split(argv[2], ' ');
	search_path(args);
	ft_printf("Fork\n");
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(pipefd, args);
	else if (pid > 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		ft_free(args);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	args;

	if (argc > 3)
	{
		args.in = check_files(argv[1]);
		args.out = check_files(argv[argc - 1]);
		/*args.in = argv[1];
		args.out = argv[argc - 1];*/
		args.envp = envp;
		creating_pipes(argc, argv, &args);
		
		/*int	i = 0;
		while (args.cmd[i])
		{
			//ft_printf("%s\n\n\n", envp[i]);
			args.path = search_path(envp);
			int	j = 0;
			while (args.path[j])
				ft_printf("%s\n", args.path[j++]);
			i++;
		}
		printf("C'est bon\n");*/
		/*if (execve(argv[2], argv, envp) == -1)
			perror("Can't execve");*/
		/*close(fd1);
		close(fd2);*/
	}
	else
		ft_printf("Wrong number of args\n");
}
