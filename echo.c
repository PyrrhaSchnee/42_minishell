/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:05:28 by yanli             #+#    #+#             */
/*   Updated: 2025/07/11 20:57:52 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_multi_n(char *s)
{
	size_t	i;

	i = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* echo_builtin_n handles echo with option -n */
static int	echo_builtin_n(size_t argc, char **s)
{
	size_t	i;

	i = 2;
	while (i < argc - 1)
	{
		if (int_putstr_fd(s[i], STDOUT_FILENO) == -1)
			return (1);
		if (int_putstr_fd(" ", STDOUT_FILENO) == -1)
			return (1);
		i++;
	}
	if (int_putstr_fd(s[i], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

/*	echo_builtin() : when calling this function, mode = 0 means "echo xxx",
	mode == 1 means "echo -n xxxxx"
*/
int	echo_builtin(size_t argc, char **s)
{
	size_t	i;

	i = 1;
	if (!s || argc == 1)
	{
		if (int_putstr_fd("\n", STDOUT_FILENO) == -1)
			return (1);
		return (0);
	}
	if (!ft_strncmp(s[1], "-n", 2) && echo_multi_n(s[1]))
		return (echo_builtin_n(argc, s));
	while (i < argc - 1)
	{
		if (int_putstr_fd(s[i], STDOUT_FILENO) == -1)
			return (1);
		if (int_putstr_fd(" ", STDOUT_FILENO) == -1)
			return (1);
		i++;
	}
	if (int_putendl_fd(s[i], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}
