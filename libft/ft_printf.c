/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 01:58:24 by yanli             #+#    #+#             */
/*   Updated: 2025/05/26 00:24:44 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_process_str(const char c, va_list ag)
{
	size_t	i;
	char	x;
	char	*str;

	i = 0;
	if (c == 'c')
	{
		x = (char)va_arg(ag, int);
		return (write(1, &x, 1));
	}
	str = va_arg(ag, char *);
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i++;
	return (write(1, str, i));
}

static int	ft_process(char *s, va_list ag)
{
	int		r;
	size_t	i;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 'c' || s[i] == 's')
				r += ft_process_str(s[i], ag);
			if (s[i] == 'p' || s[i] == 'x' || s[i] == 'X')
				r += ft_process_hex(s[i], ag);
			if (s[i] == 'd' || s[i] == 'i' || s[i] == 'u')
				r += ft_process_nbr(s[i], ag);
			if (s[i] == '%')
				r += write(1, &s[i], 1);
		}
		else
			r += write(1, &s[i], 1);
		i++;
	}
	return (r);
}

int	ft_printf(const char *ag0, ...)
{
	int		r;
	va_list	ag;

	if (!ag0)
		return (0);
	va_start(ag, ag0);
	r = ft_process((char *)ag0, ag);
	va_end(ag);
	return (r);
}
