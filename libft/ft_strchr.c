/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:58:43 by yanli             #+#    #+#             */
/*   Updated: 2025/06/19 13:37:39 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*f;

	if (!s)
		return (NULL);
	i = 0;
	f = (char *)s;
	while (s[i])
	{
		if ((char)c == f[i])
			return (&f[i]);
		i++;
	}
	if ((char)c == f[i])
		return (&f[i]);
	return (NULL);
}
