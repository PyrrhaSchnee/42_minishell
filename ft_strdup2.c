/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:59:28 by yanli             #+#    #+#             */
/*   Updated: 2025/06/26 10:56:00 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_nbrsec(char **s)
{
	size_t	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	**fail_exit(size_t i, char **r)
{
	size_t	k;

	k = 0;
	if (!i || !r)
		return (NULL);
	while (k < i - 1)
	{
		if (r[k])
			free(r[k]);
		r[k] = NULL;
		k++;
	}
	return (NULL);
}

char	**ft_strdup2(char **s)
{
	const size_t	nbr_sec = ft_nbrsec(s);
	size_t			i;
	char			**r;

	if (!nbr_sec)
		return (NULL);
	r = ft_calloc(nbr_sec + 1, sizeof(char *));
	if (!r)
		return (NULL);
	i = 0;
	while (i < nbr_sec)
	{
		r[i] = ft_strdup(s[i]);
		if (!r[i])
			return (fail_exit(i, r));
		i++;
	}
	r[i] = NULL;
	return (r);
}
