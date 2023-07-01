/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_pf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouayya <zbouayya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:14:58 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 01:38:45 by zbouayya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putunsigned_pf(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb < 10)
	{
		len += ft_putchar_pf(nb + '0');
	}
	else if (nb >= 10)
	{
		len += ft_putnbr_pf(nb / 10);
		len += ft_putnbr_pf(nb % 10);
	}
	return (len);
}
