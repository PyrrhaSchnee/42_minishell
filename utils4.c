/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:06:37 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 09:05:13 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(char **s)
{
	if (!s || !*s)
		return ;
	free(*s);
	*s = NULL;
}

void	close_fd_prev(int *fd)
{
	if (!fd || *fd < 0)
		return ;
	if (*fd != STDIN_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_fd(int *fd)
{
	if (!fd || *fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

int	exit_overflow(char *s)
{
	int			i;
	const char	*m = "9223372036854775807";

	if (*s == '+' || *s == '-')
		s++;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i > 19)
		return (1);
	if (i < 19)
		return (0);
	i = 0;
	while (i < 19)
	{
		if (s[i] > m[i])
			return (1);
		if (s[i] < m[i])
			return (0);
		i++;
	}
	return (0);
}
