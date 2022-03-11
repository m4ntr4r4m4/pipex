/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/11 14:38:17 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv, char **envp)
{
	t_pip	vars;
	int		i = 0;
	int		pid1;
	int		pid2;
	int		fdin;
	int		fdout;

	if (argc == 5)
	{
		if (pipe(vars.fd) < 0)
			return (0);

		vars.pathvar = path_var(envp);
		pid1 = fork();
		if (pid1 == 0)
		{

			printf("evolinmai\n");
			fdin = open("./infile", O_RDONLY);
			dup2(fdin, 0);
			dup2(vars.fd[1], 1);
			close(vars.fd[1]);
			close(vars.fd[0]);
			close(fdin);
			vars.program = ft_split(argv[2], ' ');
			while (vars.pathvar[i])
			{
		//		printf("this is pathvar pid1 %s\n", vars.pathvar[i]);
				vars.path = check_bin(vars.program[0], vars.pathvar[i++], 3);
				if (vars.path)
					break;
			}
			if(!vars.path)
				printf("error: bin not found\n");
			execve(vars.path, vars.program , envp);
		}
		pid2 = fork();
		if (pid2 == 0)
		{
			printf("PID2evolinmai\n");
			fdout = open("./outfile", O_WRONLY);

			dup2(fdout, 1);
			dup2(vars.fd[0], 0);
			close(vars.fd[0]);
			close(vars.fd[1]);
			close(fdout);
			vars.program2 = ft_split(argv[3], ' ');
			i = 0;
			while (vars.pathvar[i])
			{
//				printf("this is pathvar pid2 %s\n", vars.pathvar[i]);
				vars.path2 = check_bin(vars.program2[0], vars.pathvar[i++], 3);
				if (vars.path2)
					break;
			}
			if(!vars.path2)
				printf("error: bin not found\n");
			execve(vars.path2, vars.program2 , envp);
		}
		close(vars.fd[0]);
		close(vars.fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}
