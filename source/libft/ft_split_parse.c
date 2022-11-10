/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:41:37 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/10 21:15:53 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static int	word_c(char *str, char c)
{
	int	i;
	int	wc;
	int	quote;

	i = 0;
	quote = 0;
	wc = 0;
	if (str[i] != c && str[i] != '\0')
		wc++;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		if (str[i + 1] && str[i] == c && (str[i + 1] != c) && quote != 1)
			wc++;
		i++;
	}
	return (wc);
}


static char	**cpy(char **mots, char const *s, int wc, char c)
{
	int	i;
	int	j;
	int	len;
	int	start;
	static int quote;

	i = 0;
	j = 0;
	while (j < wc)
	{
		len = 0;
		while (s[i] == c)
			i++;
		start = i;
		if (s[i] == '"')
			quote++;
		while ((s[i] != c || (quote % 2) != 0) && s[i] != '\0')
		{
			len++;
			i++;
			if (s[i] == '"')
				quote++;
		}
		mots[j] = ft_substr(s, start, len);
		j++;
	}
	mots[j] = 0;
	return (mots);
}

char	**ft_split_parse(char const *s, char c)
{
	char	**mots;
	int		wc;

	if (!s)
		return (NULL);
	wc = word_c((char *)s, c);
	mots = malloc(sizeof(char *) * (wc + 1));
	if (!mots)
		return (0);
	mots = cpy(mots, s, wc, c);
	return (mots);
}
