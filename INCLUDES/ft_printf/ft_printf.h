/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:53:39 by mlemerci          #+#    #+#             */
/*   Updated: 2025/02/25 13:19:40 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

//PRINTF:
int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_puthexa(unsigned int n, char format);
int	ft_putnbr(int n);
int	ft_putstr(const char *s);

#endif
