/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:54:33 by kzegani           #+#    #+#             */
/*   Updated: 2023/05/10 22:54:38 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(const char *s)
{
	int	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9' && i <= 20)
		i++;
	return (i);
}

static int	ret(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

static int	space(char *s)
{
	int	i;

	i = 0;
	while (ft_strchr(" \n\v\f\r\t", s[i]) != NULL)
		i++;
	return (i);
}

static int	zero(const char *s, int i)
{
	while (s[i] == '0' && s[i] != '\0')
			i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	i = space((char *)s);
	if (s[0] == '\0')
		return (0);
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	i = zero(s, i);
	if (count(s + i) > 19)
		return (ret(sign));
	else if (count(s + i) == 19)
	{
		if (sign == -1 && ft_strncmp("9223372036854775807", s + i, 19) < 0)
			return (0);
		else if (sign == 1 && ft_strncmp("9223372036854775807", s + i, 19) < 0)
			return (-1);
	}
	while (s[i] >= 48 && s[i] <= 57)
		num = num * 10 + (s[i++] - 48);
	return (num * sign);
}
