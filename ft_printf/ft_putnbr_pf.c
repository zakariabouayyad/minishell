/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:15:21 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 01:38:18 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putnbr_pf(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putchar_pf('-');
		len += ft_putchar_pf('2');
		n = 147483648;
	}
	if (n < 0)
	{
		len += ft_putchar_pf('-');
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_putnbr_pf(n / 10);
		len += ft_putnbr_pf(n % 10);
	}
	else
	{
		n = n + '0';
		len += ft_putchar_pf(n);
	}
	return (len);
}
