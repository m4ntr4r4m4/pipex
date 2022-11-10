/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/10 21:15:50 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dupfd(t_pip *pipes, int id, int size)
{
	if (id == 0)
	{
		dup2(pipes[id].fdin, 0);
		close(pipes[id].fdin);
	}
	if (id > 0)
	{
		dup2(pipes[id - 1].fd[0], 0);
		close(pipes[id - 1].fd[0]);
	}
	if(id < size)
	{
		dup2(pipes[id].fd[1], 1);
		close(pipes[id].fd[1]);
	}
	if(id == size)
	{
		dup2(pipes[id].fdout, 1);
		close(pipes[id].fdout);
	}
}

//void	child1(t_pip *vars, int id,  t_cmd *cmd)
//{
//	int	i;
//
//	i = 0;
//	if (id == 0)
//		vars[id].fdin = open(cmd->file, O_RDONLY);
//	if (vars[id].fdin < 0)
//	{
//		perror("error");
//		exit(0);
//	}
//	dupfd(vars);
//	vars.program = ft_split(argv[2], ' ');
//	while (vars.pathvar[i])
//	{
//		vars.path = check_bin(vars.program[0], vars.pathvar[i++], 3);
//		if (vars.path)
//			break ;
//	}
//	if (!vars.path)
//	{
//		perror("command");
//		exit(0);
//	}
//	execve(vars.path, vars.program, envp);
//}

void	dupfd2(t_pip vars)
{
	dup2(vars.fdout, 1);
	dup2(vars.fd[0], 0);
	close(vars.fd[0]);
	close(vars.fd[1]);
	close(vars.fdout);
}

void	get_cmd(char **av, t_all *all, int x)
{
	int	i;
	char **tmp;

	all->size = 0;
//	fprintf(stderr,"this is size %d\n", x);
//	ft_print_table(av, 1);
	i = -1;
	while (++i < x)
	{
  		tmp = ft_split_parse(av[i] ,' ');

		all->cmd[i].name = tmp[0];
		all->cmd[i].args = (tmp);
//		printf("cmd: %s\n", all->cmd[i].name);
 	// 	ft_print_table(all->cmd[i].args, 1);
		all->size++;
	}
}


int	ft_parsing(char **av, t_all *vars)
{
	int	i;
	int	x;
	int	j;
	static int	y;

	i = -1;
	x = 0;
	while (av[x])
		x++;
	vars->cmd = malloc(sizeof(t_cmd) * x--);
	vars->pipes = malloc(sizeof(t_pip) * x - 1);
//	fprintf(stderr,"this is av  %s\n", (*av));
	if(!check_bin(av[0], "./", 1))
		return (-1);
	get_cmd((av + 1), vars, x - 1);
	while (++i < x - 1)
	{
		j = 0;
//		fprintf(stderr, "cmd name %s\n", vars->cmd[i].name);
		while (vars->pathvar[j])
		{
			vars->cmd[i].path = check_bin(vars->cmd[i].name, vars->pathvar[j++], 3);
			if (vars->cmd[i].path)
			{
				y++;
				break ;
			}
		}
	}
	if (i != y)
		return (-1);
	fprintf(stderr, "this strncmp : %d\n", (ft_strncmp(vars->cmd[i - 1].name, av[i + 1], ft_strlen(vars->cmd[i - 1].name))));
	
	fprintf(stderr, "cmd[i] : %s\n", vars->cmd[i - 1].name);
	fprintf(stderr,"hello %d %d %d %s\n",x, y, i, av[i + 1]);
	if(!check_bin(av[i + 1], "./", 3) && !check_bin(av[i + 1], "./", 2))
		return (-1);

	return (-0);
}

int	main(int argc, char **argv, char **envp)
{
//	int		*pid;
	int		i;
	t_all	all;

	i = -1;
	argc = 0;

//	while(argv[++i])
//		fprintf(stderr, "av[%d]: %s\n", i, argv[i]);
	all.pathvar = path_var(envp);
	if (ft_parsing(++argv, &all))
	{
		ft_putstr_fd("example: ./pipex Infile cmd1 .. cmdn Outfile\n", 1);
		exit(0);
	}
//	fprintf(stderr, "number of cmds %zu\n", all.size);
//		if (pipe(vars[i].fd) < 0)
//			return (0);
//		vars.pathvar = path_var(envp);
//		pid1 = fork();
//		if (pid1 == 0)
//			child1(vars, argv, envp);
//		pid2 = fork();
//		if (pid2 == 0)
//			child2(vars, argv, envp);
//		close(vars.fd[0]);
//		close(vars.fd[1]);
//		waitpid(pid1, NULL, 0);
//		waitpid(pid2, NULL, 0);
//		freevars(&vars);
//	}
//	else
	return (0);
}
