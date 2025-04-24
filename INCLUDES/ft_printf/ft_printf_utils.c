/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:26:34 by manon             #+#    #+#             */
/*   Updated: 2025/02/25 13:19:32 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int n)
{
	int		i;
	char	*nbr;
	long	l;

	l = n;
	i = 0;
	nbr = "0123456789";
	if (l < 0)
	{
		ft_putchar('-');
		l = -l;
		i++;
	}
	if (l > 9)
		i += ft_putnbr(l / 10);
	i += ft_putchar(nbr[l % 10]);
	return (i);
}

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_puthexa(unsigned int n, char format)
{
	int		i;
	char	*hexa;

	i = 0;
	if (format == 'u')
	{
		if (n > 9)
			i += ft_putnbr(n / 10);
		i += ft_putchar(n % 10 + '0');
	}
	if ((format == 'x' || format == 'X'))
	{
		if (format == 'x')
			hexa = "0123456789abcdef";
		else if (format == 'X')
			hexa = "0123456789ABCDEF";
		if (n >= 16)
			i += ft_puthexa(n / 16, format);
		i += ft_putchar(hexa[n % 16]);
	}
	return (i);
}
