/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/14 11:55:03 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(void);
void	dupfd(t_pip *pipes, int id, int size)
{
	if (id == 0)
	{
		dup2(pipes[id].fdin, 0);
		close(pipes[id].fdin);
		close(pipes[id].fd[0]);
		fprintf(stderr,"ddup fd in pipe %d\n", id);
	}
	if (id > 0)
	{
		dup2(pipes[id - 1].fd[0], 0);
		close(pipes[id - 1].fd[0]);
		fprintf(stderr,"ddup fd in from pre pipe %d\n", id - 1);
		fprintf(stderr,"close fd 0\n");
	}
	if(id < size)
	{
		dup2(pipes[id].fd[1], 1);
		close(pipes[id].fd[1]);
		fprintf(stderr,"ddup fd out to pipe %d\n", id);
		fprintf(stderr,"close fd 1\n");
	}
	if(id == size)
	{
		dup2(pipes[id - 1].fdout, 1);
		close(pipes[id - 1].fdout);
		fprintf(stderr,"close fd 1\n");
		fprintf(stderr,"ddp out fdout %d\n", id - 1);
	}
}

void	closefiledes(t_pip *var, int size)
{
	int	i;

	i = 0;
	while (i < size )
	{
		close(var[i].fd[0]);
		close(var[i].fd[1]);
		i++;
	}
}

void	child1(int id,  t_all *all, char **envp)
{
	fprintf(stderr," ********************************************\nPID :%d\nthis is id %d\nsize : %d\n",getpid(), id, (int) all->size);
	if (id == 0)
	{
		all->pipes[id].fdin = open(all->infile, O_RDONLY);
			if (all->pipes[id].fdin < 0)
			{
				perror("error");
				exit(0);
			}
		fprintf(stderr,"open in file\n");
	}
	if (id == (int) all->size - 1)
	{
		all->pipes[id - 1].fdout = open(all->outfile,  O_RDWR | O_TRUNC | O_CREAT, 0666);
		if (all->pipes[id - 1].fdout < 0)
		{
			perror("error");
			exit(0);
		}
		fprintf(stderr,"open out file\n");
	}
	dupfd(all->pipes, id, all->size - 1);
	closefiledes(all->pipes, all->size - 1);
	ft_print_table(all->cmd[id].args, 2);
	fprintf(stderr,"*******--------*********\n");
	if (execve(all->cmd[id].path, all->cmd[id].args, envp) < 0)
	{
		perror("command");
		exit(0);
	}
}


void	get_cmd(char **av, t_all *all, int x)
{
	int	i;
	int	j;
	char **tmp;

	all->size = 0;
	i = -1;
	while (++i < x)
	{
  		tmp = ft_split_parse(av[i] ,' ');
		j = 0;
		while (all->pathvar[j])
		{
			all->cmd[i].path = check_bin(tmp[0], all->pathvar[j++], FT_EXEC);
			if (all->cmd[i].path)
			{
				tmp[0] = all->cmd[i].path;
				all->cmd[i].name = tmp[0];
				all->cmd[i].args = (tmp);
				all->size++;
				break ;
			}
			else
				all->cmd[i].name = NULL;
		}
		if (!all->cmd[i].name)
		{
			perror("command");
			ft_error();
		}
	}
	all->outfile = av[i];
}

int	ft_parsing(char **av, t_all *vars, int x)
{
	int	i;

	i = -1;
	vars->cmd = malloc(sizeof(t_cmd) * x);
	printf("this number cmd %d\n", x);
	vars->pipes = malloc(sizeof(t_pip) * x - 1);
	if(!check_bin(av[0], "./", 1))
		return (-1);
	vars->infile = av[0];
	get_cmd((av + 1), vars, x);
	i = -1;
	while (++i < (int)vars->size)
		fprintf(stderr, "cmd[%d] : %s\n",i, vars->cmd[i].name);
//	if (i < x - 1)
//		if(!check_bin(av[i + 1], "./", 3) && !check_bin(vars->cmd[i - 1].name, "./", 2))
//			return (-1);
	return (0);
}
void	ft_error(void)
{
	ft_putstr_fd("example: ./pipex Infile cmd1 .. cmdn Outfile\n", 1);
		exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	int		*pid;
	int		i;
	t_all	all;

	i = -1;

//	while(argv[++i])
//		fprintf(stderr, "av[%d]: %s\n", i, argv[i]);
	fprintf(stderr," PID :%d\n",getpid());
	all.pathvar = path_var(envp);
	if (ft_parsing(++argv, &all, argc - 3))
		ft_error();
	pid = malloc(sizeof(int) * all.size);
	fprintf(stderr, "number of cmds %zu\n", all.size);
//	ft_print_table(all.cmd[0].args, 1);
	while (++i < (int)all.size - 1)
	{
		if (pipe(all.pipes[i].fd) < 0)
			return (0);
		printf("success pipe[%d]\n",i);
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
//		freevars(&vars);
//	}
	return (0);
}
