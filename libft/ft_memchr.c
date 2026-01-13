/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:35:56 by yanli             #+#    #+#             */
/*   Updated: 2025/07/02 09:38:50 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*us;
	size_t			i;

	if (!s)
		return (NULL);
	uc = (unsigned char)c;
	us = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (uc == us[i])
			return ((void *)&us[i]);
		i++;
	}
	return (NULL);
}
