/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:05:01 by yanli             #+#    #+#             */
/*   Updated: 2025/07/02 09:41:05 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

static ssize_t	ft_start(char *s1, char *s2)
{
	ssize_t			i;
	const ssize_t	s1len = (ssize_t)ft_strlen(s1);

	i = 0;
	while (s1[i] && ft_check(s1[i], s2))
		i++;
	if (s1len == i)
		return (-1);
	return (i);
}

static ssize_t	ft_end(char *s1, char *s2)
{
	ssize_t	i;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (s1[i] && ft_check(s1[i], s2))
		i--;
	return (i);
}

static char	*ft_empty_str(void)
{
	char	*r;

	r = ft_calloc(sizeof(char), 1);
	if (!r)
		return (NULL);
	r[0] = '\0';
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const ssize_t	start = ft_start((char *)s1, (char *)set);
	const ssize_t	end = ft_end((char *)s1, (char *)set);
	char			*r;
	ssize_t			i;

	if (!s1)
		return (NULL);
	if (start == -1)
		return (ft_empty_str());
	r = ft_calloc(sizeof(char), (size_t)(2 + end - start));
	if (!r)
		return (NULL);
	i = 0;
	while (start + i < end + 1)
	{
		r[i] = (char)s1[i + start];
		i++;
	}
	r[i] = '\0';
	return (r);
}
