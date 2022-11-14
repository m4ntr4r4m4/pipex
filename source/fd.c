/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:44:28 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/14 16:58:27 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dupfd(t_pip *pipes, int id, int size)
{
	if (id == 0)
	{
		dup2(pipes[id].fdin, 0);
		close(pipes[id].fdin);
		close(pipes[id].fd[0]);
	}
	if (id > 0)
	{
		dup2(pipes[id - 1].fd[0], 0);
		close(pipes[id - 1].fd[0]);
	}
	if (id < size)
	{
		dup2(pipes[id].fd[1], 1);
		close(pipes[id].fd[1]);
	}
	if (id == size)
	{
		dup2(pipes[id - 1].fdout, 1);
		close(pipes[id - 1].fdout);
	}
}

void	closefiledes(t_pip *var, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(var[i].fd[0]);
		close(var[i].fd[1]);
		i++;
	}
}
