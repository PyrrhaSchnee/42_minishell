/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:33:55 by yanli             #+#    #+#             */
/*   Updated: 2025/06/22 00:02:28 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;

	if (nmemb && (size > SIZE_MAX / nmemb))
	{
		perror("malloc");
		return (NULL);
	}
	r = malloc(nmemb * size);
	if (!r)
	{
		perror("malloc");
		return (NULL);
	}
	r = ft_memset(r, 0, nmemb * size);
	return (r);
}
