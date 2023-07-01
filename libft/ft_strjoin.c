/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:09:21 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/09 18:05:48 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	ret = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		ret[i + j] = s2[j];
	ret[i + j] = '\0';
	return (ret);
}
