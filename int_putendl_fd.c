/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_putendl_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:58:17 by yanli             #+#    #+#             */
/*   Updated: 2025/06/25 23:18:45 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	int_putendl_fd(char *s, int fd)
{
	int	rv;

	if (!s)
		return (int_putstr_fd("(null)\n", fd));
	rv = int_putstr_fd(s, fd);
	if (rv == -1)
	{
		perror("minishell");
		return (rv);
	}
	if (write(fd, "\n", 1) == -1)
	{
		perror("minishell:");
		return (-1);
	}
	return (rv + 1);
}
