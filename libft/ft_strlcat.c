/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:25 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dest == NULL && dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= ft_strlen(dest))
		return (dstsize + ft_strlen(src));
	i = 0;
	j = ft_strlen(dest);
	while (src[i] && dstsize > j + 1)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (ft_strlen(&src[i]) + ft_strlen(dest));
}
