/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:16:37 by yanli             #+#    #+#             */
/*   Updated: 2025/07/11 21:09:40 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static void	check_int_overflow(long n)
{
	if (n < -2147483648 || n > 2147483647)
	{
		ft_putstr_fd("Error\nft_atoi() detected an int overflow\n", 2);
		exit(EXIT_FAILURE);
	}
}*/

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		r;
	char	*s;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	r = 0;
	s = (char *)nptr;
	while (s[i] == ' ' || (s[i] > 8 && s[i] < 14))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		r = r * 10 + (s[i++] - '0');
	return (r * sign);
}
