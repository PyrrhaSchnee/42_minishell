/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:05:08 by yanli             #+#    #+#             */
/*   Updated: 2025/07/07 17:55:10 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_empty(void)
{
	char	*r;

	r = ft_calloc(sizeof(char), 1);
	if (!r)
		return (NULL);
	r[0] = '\0';
	return (r);
}

static char	*ft_allocator(char *s1, size_t start, size_t len)
{
	char	*r;
	size_t	i;

	i = 0;
	while (s1[i + start] && i < len)
		i++;
	r = ft_calloc(sizeof(char), 1 + i);
	if (!r)
		return (NULL);
	return (r);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	const size_t	slen = ft_strlen(s);
	char			*r;
	char			*s1;

	if (!s)
		return (NULL);
	s1 = (char *)s;
	if (!len || start > slen)
		return (ft_empty());
	r = ft_allocator(s1, start, len);
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i + start] && i < len)
	{
		r[i] = s1[i + start];
		i++;
	}
	r[i] = '\0';
	return (r);
}
