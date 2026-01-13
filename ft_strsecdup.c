/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsecdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:26:33 by yanli             #+#    #+#             */
/*   Updated: 2025/06/30 17:41:54 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strsecdup(char *s, size_t begin, size_t end)
{
	char	*ret;
	size_t	i;

	ret = ft_calloc(end - begin + 1, sizeof(char));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < end - begin)
	{
		ret[i] = s[i + begin];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
