/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:08:11 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/11 14:06:20 by ahammoud         ###   ########.fr       */
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
#include <stdio.h>

typedef struct s_pip {
	char	**program;
	char	**program2;
	char	**pathvar;
	char	*path;
	char	*path2;
	int		fd[2];
}	t_pip;

#endif
