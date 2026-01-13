/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:30:39 by yanli             #+#    #+#             */
/*   Updated: 2025/05/26 00:24:49 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putunbr(unsigned int n)
{
	int	r;

	r = 0;
	if (n > 9)
		r += ft_putunbr(n / 10);
	r += write(1, &(char){n % 10 + '0'}, 1);
	return (r);
}

static int	ft_putnbr(int n)
{
	int	r;

	r = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (n < 0)
	{
		r += write(1, "-", 1);
		r += ft_putnbr(-n);
		return (r);
	}
	else if (n > 9)
		r += ft_putnbr(n / 10);
	r += write(1, &(char){n % 10 + '0'}, 1);
	return (r);
}

int	ft_process_nbr(const char c, va_list ag)
{
	int				n;
	unsigned int	u;

	if (c == 'd' || c == 'i')
	{
		n = va_arg(ag, int);
		return (ft_putnbr(n));
	}
	u = va_arg(ag, unsigned int);
	return (ft_putunbr(u));
}
