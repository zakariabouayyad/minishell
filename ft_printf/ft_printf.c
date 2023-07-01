/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzegani <kzegani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:37:37 by zbouayya          #+#    #+#             */
/*   Updated: 2023/06/24 07:39:52 by kzegani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char c, va_list arg)
{
	int	len;

	len = 0;
	if (c == 's')
		len += ft_putstr_pf(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr_pf(va_arg(arg, int));
	else if (c == 'p')
		len += ft_putadd_pf(va_arg(arg, unsigned long long));
	else if (c == 'c')
		len += ft_putchar_pf(va_arg(arg, int));
	else if (c == 'X')
		len += ft_puthex_upper_pf(va_arg(arg, unsigned int));
	else if (c == 'x')
		len += ft_puthex_pf(va_arg(arg, unsigned int));
	else if (c == 'u')
		len += ft_putunsigned_pf(va_arg(arg, unsigned int));
	else if (c == '%')
		len += ft_putchar_pf('%');
	else
		len += ft_putchar_pf(c);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if ((write(2, &str[0], 0)) == -1)
		return (-1);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				return (len);
			len += check(str[i + 1], ap);
			i++;
		}
		else
			len += ft_putchar_pf(str[i]);
		i++;
	}
	va_end(ap);
	return (len);
}
