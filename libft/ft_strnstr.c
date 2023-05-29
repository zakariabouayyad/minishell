/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:42 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;

	if (*needle == 0)
	{
		return ((char *) haystack);
	}
	i = 0;
	nlen = ft_strlen(needle);
	while (i < len && haystack[i])
	{
		if (haystack[i] == *needle && len - i >= nlen
			&& ft_strncmp(&haystack[i], needle, nlen) == 0)
		{
			return ((char *) &haystack[i]);
		}
		i++;
	}
	return (NULL);
}
