/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:56 by yanli             #+#    #+#             */
/*   Updated: 2025/07/02 09:40:59 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*f;

	if (!s)
		return (NULL);
	f = (char *)s;
	i = ft_strlen(s);
	while (i > -1)
	{
		if ((char)c == f[i])
			return (&f[i]);
		i--;
	}
	return (NULL);
}
