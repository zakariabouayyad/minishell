/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:15:07 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 01:38:31 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putstr_pf(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (str == NULL)
	{
		ft_putstr_pf("(null)");
		return (6);
	}
	while (str[i])
	{
		len += ft_putchar_pf(str[i]);
		i++;
	}
	return (len);
}
