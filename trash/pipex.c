/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/07 17:53:31 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv)
{
	char	*envp[] = {"./", NULL};
	char	**program;
	char	**flags;
	char	*flags1[]= {"-la"};
	int		i = 0;

	if (argc)
	{

		program = ft_split(argv[2], ' ');
		while(program[i])
			i++;
		flags = malloc(sizeof(char **) * (i));
		i = 0;
		while(program[i + 1] != 0)
		{
			flags[i] = program[i + 1];
			i++;
		}
//		flags[i] = argv[1];
		flags[i] = NULL;
//		printf("this is li: %d\n", i);
		i = 0;
		while (flags[i] != NULL)
			printf("this is flags: %s\n", flags[i++]);
		//execve(program[0], flags , envp);
		execve("/bin/ls", flags1 , envp);
	}
	return (0);
}
