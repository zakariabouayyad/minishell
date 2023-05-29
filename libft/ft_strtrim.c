/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:49 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;
	int		z;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	end = 0;
	i = 0;
	while (s1[i] && ft_check(s1[i++], set))
		start++;
	i = ft_strlen(s1) - 1;
	while (s1[i] && start < (int)ft_strlen(s1) && ft_check(s1[i--], set))
		end++;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) - (end + start) + 1));
	if (!str)
		return (NULL);
	i = 0;
	z = (ft_strlen(s1) - (end + start) + 1);
	while (i < z)
		str[i++] = s1[start++];
	str[i - 1] = '\0';
	return (str);
}
