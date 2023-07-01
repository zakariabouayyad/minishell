/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:15:50 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 01:40:38 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_putadd_2(unsigned long long n)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_putadd_2(n / 16);
		len += ft_putadd_2(n % 16);
	}
	if (n >= 10 && n <= 15)
		len += ft_putchar_pf(n + 87);
	else if (n <= 9)
		len += ft_putchar_pf(n + '0');
	return (len);
}

int	ft_putadd_pf(unsigned long long n)
{
	ft_putstr_pf("0x");
	return ((ft_putadd_2(n)) + 2);
}
