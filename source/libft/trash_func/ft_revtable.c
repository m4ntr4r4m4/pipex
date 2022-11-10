/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revtable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:30:55 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/15 13:49:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_revtable(char **table)
{
	int	i;
	char	*str;

	i = 0;
	str = NULL;
	while ((table)[i + 1])
	{
		str = (table)[i];
		(table)[i] = (table)[i + 1];
		(table)[i + 1] = str;
		i++;
	}
	ft_print_table(table, 1);

}

int	main()
{
	char *table[] = {"hello", "my", "friend", NULL};

	ft_revtable(&(*table));
//	ft_print_table(table, 1);



}

