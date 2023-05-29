/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:10 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return ((char *)(&str[i]));
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(&str[i]));
	}
	return (0);
}
