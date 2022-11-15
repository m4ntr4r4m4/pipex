/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:46:12 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/15 16:49:20 by ahammoud         ###   ########.fr       */
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

char	*get_line(int fd)
{
	char	*buff;
	char	*str;
	char	*tmp;
	int		i;

	buff = malloc(sizeof(char) * 2);
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	buff[1] = '\0';
	i = read(fd, buff, 1);
	if (i == -1)
	{
		free(buff);
		return (NULL);
	}
	while (buff[0] != '\n' && i != 0)
	{
		tmp = ft_strjoin(str, buff);
		free(str);
		str = tmp;
		i = read(fd, buff, 1);
	}
	free(buff);
	return (str);
}

void	ft_here_doc(t_all *all)
{
	int		fd;
	char	*input;

	fd = open("file.tmp", O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		exit(0);
	input = get_line(0);
	while (ft_strncmp(input, all->limiter, ft_strlen(all->limiter)))
	{
		ft_putendl_fd(input, fd);
		free(input);
		input = get_line(0);
	}
	close(fd);
	if (input)
		free(input);
	all->infile = "./file.tmp";
}

int	ft_parsing(char **av, t_all *vars, int x)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	vars->cmd = malloc(sizeof(t_cmd) * x);
	if (x - 1 == 0)
		ft_error(1);
	vars->pipes = malloc(sizeof(t_pip) * x - 1);
	if (strncmp(av[0], "here_doc", ft_strlen("here_doc")) != 0)
	{
		str = check_bin(av[0], "./", 1);
		if (!str)
			return (-1);
		vars->infile = av[0];
		get_cmd((av + 1), vars, x);
	}
	else
	{
		vars->limiter = av[1];
		ft_here_doc(vars);
		get_cmd((av + 2), vars, x - 1);
	}
	free(str);
	return (0);
}
