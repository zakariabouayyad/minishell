/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:15 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/13 18:06:34 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	ret = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
