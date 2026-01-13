/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:54:03 by yanli             #+#    #+#             */
/*   Updated: 2025/06/18 09:43:10 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	start;
	size_t	i;
	size_t	j;

	if (!big || !little)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	i = 0;
	start = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
			start = i;
		while (big[i + j] && little[j] && i + j < len
			&& big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)&big[start]);
		i++;
	}
	return (NULL);
}
