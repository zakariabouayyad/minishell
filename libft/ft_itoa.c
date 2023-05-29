/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:07:05 by zbouayya          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:06 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_topositive(int n)
{
	if (n < 0)
	{
		return (n * (-1));
	}
	return (n);
}

static int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
	{
		len++;
	}
	while (nbr != 0)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = ft_len(n);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
	}
	else if (n == 0)
	{
		res[0] = '0';
	}
	while (n != 0)
	{
		len--;
		res[len] = ft_topositive(n % 10) + '0';
		n = n / 10;
	}
	return (res);
}
