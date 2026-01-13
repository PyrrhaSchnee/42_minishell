/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:29:11 by yanli             #+#    #+#             */
/*   Updated: 2025/07/02 09:39:59 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_str(char *s1, char c)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		while (s1[i] && s1[i] == c)
			i++;
		if (s1[i] && s1[i] != c)
			r++;
		while (s1[i] && s1[i] != c)
			i++;
	}
	return (r);
}

static char	*ft_add(char *str, char c)
{
	size_t	i;
	char	*s;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	s = ft_calloc(sizeof(char), 1 + i);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static void	ft_clean(int j, char **r)
{
	int	i;

	i = 0;
	while (i < j)
		free(r[i++]);
	free(r);
}

static int	ft_filler(const int str_nb, char const *s, char **r, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < str_nb)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			r[j] = ft_add((char *)&s[i], c);
		if (!r[j])
		{
			ft_clean(j, r);
			return (-1);
		}
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	r[j] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char		**r;
	const int	str_nb = ft_nb_str((char *)s, c);

	if (!s)
		return (NULL);
	r = ft_calloc(sizeof(char *), (size_t)(str_nb + 1));
	if (!r)
		return (NULL);
	if (ft_filler(str_nb, s, r, c) == -1)
		return (r = NULL);
	return (r);
}
