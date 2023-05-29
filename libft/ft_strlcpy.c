/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:28 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	i;

	l = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}
