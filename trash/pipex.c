/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/09 14:58:37 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **path_var(char **envp)
{
	int	i;
	char	**pathvar;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	printf("envp path: %s\n", envp[i]);
	envp[i] = ft_strtrim(envp[i], "PATH=");
	pathvar = ft_split(envp[i], ':');
	i = 0;
	while (pathvar[i])
	{
		pathvar[i] = ft_strjoin(pathvar[i], "/");
		i++;
	}
	return (pathvar);
}

char	*check_bin(char *binary, char *bin)
{
	int		x;

	x = access(ft_strjoin(bin, binary), X_OK);
	if (x == 0)
		return (ft_strjoin(bin, binary));
	return (NULL);
}

int main (int argc, char **argv, char **envp)
{
	t_pip	vars;
	int		fd[2];
	int		i = 0;

	if (argc == 5)
	{
		vars.pathvar = path_var(envp);
		vars.program = ft_split(argv[2], ' ');
		while (vars.pathvar[i])
		{
			vars.path = check_bin(vars.program[0], vars.pathvar[i++]);
			if (vars.path)
				break;
		}
		if(!vars.path)
			printf("error: bin not found\n");
		i = 0;
		execve(vars.path, vars.program , envp);
	}
	return (0);
}
