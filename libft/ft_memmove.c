/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:08:46 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*src1;
	char	*dest1;

	src1 = (char *)src;
	dest1 = (char *)dest;
	if (!src && !dest)
	{
		return (0);
	}
	if (src1 > dest1)
	{
		ft_memcpy(dest1, src1, len);
	}
	else
	{
		while (len > 0)
		{
			dest1[len - 1] = src1[len - 1];
			len--;
		}
	}
	return (dest1);
}
