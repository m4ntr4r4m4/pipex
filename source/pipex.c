/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/14 16:48:12 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(int id, t_all *all, char **envp)
{
	if (id == 0)
	{
		all->pipes[id].fdin = open(all->infile, O_RDONLY);
		if (all->pipes[id].fdin < 0)
		{
			perror("error");
			exit(0);
		}
	}
	if (id == (int) all->size - 1)
	{
		all->pipes[id - 1].fdout \
			= open(all->outfile, O_RDWR | O_TRUNC | O_CREAT, 0666);
		if (all->pipes[id - 1].fdout < 0)
		{
			perror("error");
			exit(0);
		}
	}
	dupfd(all->pipes, id, all->size - 1);
	closefiledes(all->pipes, all->size - 1);
	if (execve(all->cmd[id].path, all->cmd[id].args, envp) < 0)
	{
		perror("command");
		exit(0);
	}
}

void	ft_error(void)
{
	ft_putstr_fd("example: ./pipex Infile cmd1 .. cmdn Outfile\n", 1);
	exit(0);
}

void	leaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	int		*pid;
	int		i;
	t_all	all;

	i = -1;
	all.pathvar = path_var(envp);
	if (ft_parsing(++argv, &all, argc - 3))
		ft_error();
	pid = malloc(sizeof(int) * all.size);
	while (++i < (int)all.size - 1)
	{
		if (pipe(all.pipes[i].fd) < 0)
			return (0);
	}
	i = -1;
	while (++i < (int) all.size)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child1(i, &all, envp);
	}
	i = -1;
	while (++i < (int) all.size - 1)
	{
		close(all.pipes[i].fd[0]);
		close(all.pipes[i].fd[1]);
	}
	i = -1;
	while (++i < (int) all.size)
		waitpid(pid[i], NULL, 0);
	freevars(&all);
	free(pid);
	return (0);
}
