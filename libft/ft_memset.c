/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:22:13 by yanli             #+#    #+#             */
/*   Updated: 2025/06/22 00:02:53 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*j;

	if (!s)
		return (NULL);
	j = (unsigned char *)s;
	i = 0;
	while (i < n)
		j[i++] = (unsigned char)c;
	return (s);
}
