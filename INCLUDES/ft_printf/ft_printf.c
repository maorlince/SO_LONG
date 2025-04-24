/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:10 by manon             #+#    #+#             */
/*   Updated: 2025/02/25 13:19:26 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexadrr(unsigned long long n)
{
	int		i;
	char	*hexa;

	hexa = "0123456789abcdef";
	i = 0;
	if (n >= 16)
		i += ft_puthexadrr(n / 16);
	i += ft_putchar(hexa[n % 16]);
	return (i);
}

int	ft_putadress(void *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	i += ft_putstr("0x");
	i += ft_puthexadrr((unsigned long long)ptr);
	return (i);
}

int	ft_format(va_list args, char c)
{
	int	count;

	count = 0;
	if ((c == 'd') || (c == 'i'))
		count += ft_putnbr(va_arg(args, int));
	if (c == 's')
		count += ft_putstr(va_arg(args, const char *));
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	if (c == 'p')
		count += ft_putadress(va_arg(args, void *));
	if ((c == 'x') || (c == 'X') || (c == 'u'))
		count += ft_puthexa(va_arg(args, unsigned int), c);
	if (c == '%')
		count += write(1, &c, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	if (!format)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			count += ft_format(args, format[i]);
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
