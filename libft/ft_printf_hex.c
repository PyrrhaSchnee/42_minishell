/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:18:25 by yanli             #+#    #+#             */
/*   Updated: 2025/05/26 00:24:57 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putmem(unsigned long int n)
{
	const char	h[] = "0123456789abcdef";
	int			r;

	r = 0;
	if (n > 15)
		r += ft_putmem(n / 16);
	r += write(1, &h[n % 16], 1);
	return (r);
}

static int	ft_puthex(const char *h, unsigned int n)
{
	int	r;

	r = 0;
	if (n > 15)
		r += ft_puthex(h, n / 16);
	r += write(1, &h[n % 16], 1);
	return (r);
}

int	ft_process_hex(const char c, va_list ag)
{
	void				*addr;
	unsigned long int	mem;
	unsigned int		ui;
	const char			hlow[] = "0123456789abcdef";
	const char			hup[] = "0123456789ABCDEF";

	if (c == 'x')
	{
		ui = va_arg(ag, unsigned int);
		return (ft_puthex(hlow, ui));
	}
	if (c == 'X')
	{
		ui = va_arg(ag, unsigned int);
		return (ft_puthex(hup, ui));
	}
	addr = va_arg(ag, void *);
	mem = (unsigned long int)addr;
	if (!mem)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (2 + ft_putmem(mem));
}
