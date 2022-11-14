/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:46:12 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/14 17:32:41 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	split_parse(t_all *all, char **av, int i)
{
	char	**tmp;
	int		j;

	tmp = ft_split_parse(av[i], ' ');
	j = 0;
	while (all->pathvar[j])
	{
		all->cmd[i].path = check_bin(tmp[0], all->pathvar[j++], FT_EXEC);
		if (all->cmd[i].path)
		{
			free(tmp[0]);
			tmp[0] = all->cmd[i].path;
			all->cmd[i].name = tmp[0];
			all->cmd[i].args = (tmp);
			all->size++;
			break ;
		}
		else
			all->cmd[i].name = NULL;
	}
}

void	get_cmd(char **av, t_all *all, int x)
{
	int		i;

	all->size = 0;
	i = -1;
	while (++i < x)
	{
		split_parse(all, av, i);
		if (!all->cmd[i].name)
		{
			freevars(all);
			perror("command");
			ft_error(1);
		}
	}
	all->outfile = av[i];
}

int	ft_parsing(char **av, t_all *vars, int x)
{
	int		i;
	char	*str;

	i = -1;
	vars->cmd = malloc(sizeof(t_cmd) * x);
	if (x - 1 == 0)
		ft_error(1);
	vars->pipes = malloc(sizeof(t_pip) * x - 1);
	str = check_bin(av[0], "./", 1);
	if (!str)
		return (-1);
	vars->infile = av[0];
	get_cmd((av + 1), vars, x);
	free(str);
	return (0);
}
