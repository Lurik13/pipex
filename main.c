/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lribette <lribette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:27:37 by lribette          #+#    #+#             */
/*   Updated: 2024/01/19 19:42:02 by lribette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_files(char *argv)
{
	int		fd;

	fd = open(argv, O_RDONLY, 0666);
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

void	first_child(int *pipefd, t_arg *args)
{
	int		i;

	i = 0;
	close(pipefd[READING]);
	if (dup2(args->in, STDIN_FILENO) == -1 || dup2(pipefd[WRITING], STDOUT_FILENO) == -1)
		dprintf(2, "dup error First\n");
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
	if (dup2(pipefd[READING], STDIN_FILENO) == -1 || dup2(args->out, STDOUT_FILENO) == -1)
		dprintf(2, "dup error Last\n");
	close(pipefd[READING]);
	close(args->out);
	while (args->path[i])
		execve(args->path[i++], args->cmd, args->envp);
	perror("Invalid command");
	exit(EXIT_FAILURE);
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
	int		pipefd[2];
	pid_t	pid[2];
	int		i;
	
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < argc - 3)
	{
		ft_printf("Fork n%d\n", i);
		args->cmd = ft_split(argv[i + 2], ' ');
		search_path(args);
		pid[i] = fork();
		if (pid[i] == -1)
			exit(EXIT_FAILURE);
		if (pid[i] == 0)
		{
			if (i + 1 < argc - 3)
				first_child(pipefd, args);
			else
				last_child(pipefd, args);	
		}		
		ft_free(args);
		i++;
	}
	i = 0;
	close(pipefd[0]);
	close(pipefd[1]);
	while (i++ < argc - 3)
		wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	args;

	if (argc > 3)
	{
		args.in = check_files(argv[1]);
		args.out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (args.out == -1)
		{
			ft_printf("Invalid outfile\n");
			exit(1);
		}
		args.envp = envp;
		creating_pipes(argc, argv, &args);
	}
	else
		ft_printf("Wrong number of args\n");
}


//env -i ./pipex text.txt "cat -e" "wc -l" ici.txt
// il faut regarder si Path existe ou non dans envp

//prendre en compte s'il n'y a pas de pipe a faire

//faire le premier bonus