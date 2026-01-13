/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:18 by yanli             #+#    #+#             */
/*   Updated: 2025/07/02 09:40:41 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1len = ft_strlen(s1);
	const size_t	s2len = ft_strlen(s2);
	char			*r;
	size_t			i;
	size_t			j;

	r = ft_calloc(sizeof(char), 1 + s1len + s2len);
	if (!r)
		return (NULL);
	i = 0;
	j = 0;
	while (j < s1len)
		r[i++] = s1[j++];
	j = 0;
	while (j < s2len)
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}
