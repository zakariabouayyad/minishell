/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:15:28 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 01:37:40 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_puthex_pf(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_puthex_pf(n / 16);
		len += ft_puthex_pf(n % 16);
	}
	if (n >= 10 && n <= 15)
		len += ft_putchar_pf(n + 87);
	else if (n <= 9)
		len += ft_putchar_pf(n + '0');
	return (len);
}
