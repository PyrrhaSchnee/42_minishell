/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:28:56 by yanli             #+#    #+#             */
/*   Updated: 2025/04/04 02:05:22 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const size_t	dstlen = ft_strlen(dst);
	const size_t	srclen = ft_strlen(src);
	size_t			i;

	if (size <= dstlen)
		return (srclen + size);
	i = 0;
	while (src[i] && i < size - 1 - dstlen)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (dstlen + srclen);
}
