/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_putstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:54:11 by yanli             #+#    #+#             */
/*   Updated: 2025/07/09 14:49:11 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errno(const char *prefix, const char *path)
{
	char	*err;

	err = strerror(errno);
	write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}

int	int_putstr_fd(char *s, int fd)
{
	size_t	i;
	int		errno2;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	if (write(fd, s, i) == -1)
	{
		errno2 = errno;
		print_errno("minishell", strerror(errno2));
		return (-1);
	}
	return (i);
}
