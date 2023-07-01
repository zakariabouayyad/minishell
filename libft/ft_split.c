/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:06 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/23 22:13:34 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_freeall(char **list, int i )
{
	while (list[i])
	{
		free(list[i]);
		i--;
	}
	free(list);
	return (NULL);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	listsize;
	size_t	i;

	i = 0;
	listsize = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || \
		(s[i] == c && s[i + 1] != c && s[i + 1] != '\0'))
			listsize++;
		i++;
	}
	return (listsize);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	save;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_wordcount((char *)s, c) + 1));
	if (!str)
		return (NULL);
	while (++j < ft_wordcount((char *)s, c))
	{
		while (s[i] == c && s[i])
			i++;
		save = i;
		while (s[i] != c && s[i])
			i++;
		str[j] = ft_substr(s, save, i - save);
		if (!str)
			return (ft_freeall(str, j - 1));
	}
	str[j] = NULL;
	return (str);
}
