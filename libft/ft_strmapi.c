/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:32 by yanli             #+#    #+#             */
/*   Updated: 2025/05/01 15:52:34 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	const size_t	slen = ft_strlen(s);
	char			*r;
	char			*s1;

	if (!s || !f)
		return (NULL);
	r = ft_calloc(sizeof(char), slen + 1);
	if (!r)
		return (NULL);
	i = 0;
	s1 = (char *)s;
	while (i < slen)
	{
		r[i] = f(i, s1[i]);
		i++;
	}
	r[i] = '\0';
	return (r);
}
