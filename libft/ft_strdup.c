/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:07 by yanli             #+#    #+#             */
/*   Updated: 2025/06/26 21:33:03 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*s;

	s = ft_calloc(sizeof(char), 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_strdup(const char *s)
{
	char	*r;
	size_t	slen;
	size_t	i;
	char	*s2;

	i = 0;
	if (!s)
		return (empty_string());
	slen = ft_strlen(s);
	r = ft_calloc(sizeof(char), slen + 1);
	if (!r)
		return (empty_string());
	s2 = (char *)s;
	while (i < slen)
	{
		r[i] = s2[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
