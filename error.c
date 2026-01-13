/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:22:19 by yanli             #+#    #+#             */
/*   Updated: 2025/07/11 16:28:13 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error1(void)
{
	ft_putstr_fd(ERROR1, 2);
	exit(EXIT_FAILURE);
}

void	ft_error2(void)
{
	ft_putstr_fd(ERROR2, 2);
	exit(EXIT_FAILURE);
}

void	ft_error3(char **copy, size_t i)
{
	ssize_t	k;

	k = (ssize_t)i;
	if (!copy)
		return ;
	while (k > -1)
	{
		if (copy[k])
			free(copy[k]);
		copy[k] = NULL;
		k--;
	}
	free(copy);
	copy = NULL;
	exit(EXIT_FAILURE);
}

void	ft_error4(void)
{
	ft_putstr_fd(ERROR3, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
