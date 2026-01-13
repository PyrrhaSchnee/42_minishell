/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:47:04 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 11:24:53 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_total_element(t_token *token)
{
	size_t	count;

	if (!token)
		return (0);
	count = 1;
	while (token)
	{
		if (token->type == TK_PIPE)
			count++;
		token = token->next;
	}
	return (count);
}
