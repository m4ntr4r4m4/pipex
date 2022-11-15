/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:36:36 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/15 16:32:58 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_var(char **envp)
{
	int		i;
	char	**pathvar;
	char	*str;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	envp[i] = ft_strtrim(envp[i], "PATH=");
	pathvar = ft_split(envp[i], ':');
	i = 0;
	while (pathvar[i])
	{
		str = ft_strjoin(pathvar[i], "/");
		free(pathvar[i]);
		pathvar[i] = str;
		i++;
	}
	return (pathvar);
}

char	*check_bin(char *binary, char *bin, int ac)
{
	int		x;
	char	*str;

	str = ft_strjoin(bin, binary);
	if (ac == 1)
		x = access(str, R_OK);
	if (ac == 2)
		x = access(str, W_OK);
	if (ac == 3)
		x = access(str, X_OK);
	free(str);
	if (x == 0)
		return (ft_strjoin(bin, binary));
	return (NULL);
}

void	freetable(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}

void	freevars(t_all *all)
{
	int	i;

	i = -1;
	freetable(all->pathvar);
	free(all->pipes);
	while (++i < (int) all->size)
		freetable(all->cmd[i].args);
	free(all->cmd);
	if (all->limiter)
		unlink(all->infile);
}
