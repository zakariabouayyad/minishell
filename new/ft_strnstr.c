/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:32:26 by kzegani           #+#    #+#             */
/*   Updated: 2023/05/11 00:32:32 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*one;
	char	*two;

	i = 0;
	one = (char *)haystack;
	two = (char *)needle;
	if (needle[0] == '\0')
		return (one);
	while (one[i] != '\0' && i < len)
	{
		j = 0;
		while (one[i + j] == two[j] && i + j < len)
		{
			if (two[j + 1] == '\0')
				return (one + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
