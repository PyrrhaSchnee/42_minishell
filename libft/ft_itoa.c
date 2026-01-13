/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:00:56 by yanli             #+#    #+#             */
/*   Updated: 2025/06/18 09:41:37 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pos(char *r, long int n, ssize_t totlen)
{
	r[totlen--] = '\0';
	while (totlen > -1)
	{
		r[totlen--] = n % 10 + '0';
		n /= 10;
	}
}

static void	neg(char *r, long int n, ssize_t totlen)
{
	r[0] = '-';
	r[totlen--] = '\0';
	while (totlen > 0)
	{
		r[totlen--] = n % 10 + '0';
		n /= 10;
	}
}

static ssize_t	ft_nb_len(long int nb)
{
	ssize_t	i;

	i = 0;
	if (nb < 0)
		nb = -nb;
	else if (nb == 0)
		return (1);
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*r;
	long int	nb;

	if (n < 0)
	{
		nb = -(n + 10);
		nb += 10;
		r = ft_calloc(sizeof(char), (size_t)ft_nb_len(-nb) + 2);
		if (!r)
			return (NULL);
		neg(r, nb, ft_nb_len(-nb) + 1);
		return (r);
	}
	else
	{
		nb = n;
		r = ft_calloc(sizeof(char), (size_t)ft_nb_len(nb) + 1);
		if (!r)
			return (NULL);
		pos(r, nb, ft_nb_len(nb));
		return (r);
	}
}
