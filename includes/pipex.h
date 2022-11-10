/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:08:11 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/10 18:05:18 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>

typedef struct s_pip {
	int		fd[2];
	int		fdin;
	int		fdout;
}	t_pip;

typedef struct s_cmd {
	char	*name;
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_all {
	char	**pathvar;
	char	*infile;
	char	*outfile;
	t_cmd	*cmd;
	size_t	size;
	t_pip	*pipes;
}	t_all;

char	*check_bin(char *binary, char *bin, int ac);
char	**path_var(char **envp);
void	freevars(t_pip *vars);
#endif
