/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaceholder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:17:25 by yanli             #+#    #+#             */
/*   Updated: 2025/07/07 22:25:13 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_char(char *s, char old, char new)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == old)
			s[i] = new;
		i++;
	}
}

char	**split_placeholder(char *s)
{
	char	**ret;
	size_t	i;

	ret = ft_split(s, ' ');
	if (!ret)
		return (NULL);
	i = 0;
	while (ret[i])
	{
		replace_char(ret[i], SPACE_PLACEHOLDER, ' ');
		i++;
	}
	return (ret);
}
