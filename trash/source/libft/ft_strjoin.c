/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 01:30:36 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/11 19:00:50 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	int		x;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	dest = NULL;
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	dest = malloc((j + i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	x = 0;
	while(s1[x])
	{
		dest[x] = s1[x];
		x++;
	}
	x = 0;
	while(s2[x])
	{
		dest[x + i] = s2[x];
		x++;
	}
	dest[i + j] = '\0';
	free(s1);
	return (dest);
}
