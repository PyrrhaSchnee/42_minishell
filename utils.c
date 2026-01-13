/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:18 by yanli             #+#    #+#             */
/*   Updated: 2025/07/07 13:19:10 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pstr(char ***s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return ;
	while ((*s)[i])
	{
		if ((*s)[i])
			free((*s)[i]);
		(*s)[i] = NULL;
		i++;
	}
	free(*s);
	(*s) = NULL;
}

size_t	ft_nbr_sec(char **s)
{
	size_t	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_sort_pstr(char **s)
{
	char			**ret;
	size_t			i;
	const size_t	nbr_sec = ft_nbr_sec(s);
	char			*temp;

	ret = ft_strdup2(s);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nbr_sec - 1)
	{
		if (ft_strcmp(ret[i], ret[i + 1]) > 0)
		{
			temp = ret[i];
			ret[i] = ret[i + 1];
			ret[1 + i] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (ret);
}

char	*ft_strldup(char *s, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!len || !s)
		return (NULL);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_single_word(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && !ft_isspace(s[len]))
		len++;
	return (ft_strldup(s, len));
}
