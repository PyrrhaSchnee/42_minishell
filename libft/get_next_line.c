/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:00:25 by yanli             #+#    #+#             */
/*   Updated: 2025/05/26 00:16:56 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getline(char *s)
{
	size_t	len;
	char	*line;

	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		len++;
	line = ft_calloc(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (len-- > 0)
		line[len] = s[len];
	return (line);
}

static char	*ft_update(char *rem)
{
	size_t	i;
	char	*next;

	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i] || (rem[i] == '\n' && rem[i + 1] == '\0'))
	{
		free(rem);
		return (NULL);
	}
	i++;
	next = ft_strdup(&rem[i]);
	if (!next)
	{
		free(rem);
		return (NULL);
	}
	free(rem);
	return (next);
}

static char	*ft_append(char *rem, char *buf)
{
	char	*temp;

	if (!rem)
		rem = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(rem, buf);
		free(rem);
		rem = temp;
	}
	return (rem);
}

static char	*ft_filler(int fd, char *rem)
{
	char	*buf;
	ssize_t	data_read;

	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (free(rem), NULL);
	data_read = 1;
	while (data_read > 0 && !ft_strchr(rem, '\n'))
	{
		data_read = read(fd, buf, BUFFER_SIZE);
		if (data_read <= 0)
			break ;
		buf[data_read] = '\0';
		rem = ft_append(rem, buf);
		if (!rem)
			break ;
	}
	free(buf);
	if (data_read < 0)
	{
		free(rem);
		return (NULL);
	}
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*rem[1048576];
	char		*line;

	if (fd < 0 || fd > 1048575 || BUFFER_SIZE < 1)
		return (NULL);
	rem[fd] = ft_filler(fd, rem[fd]);
	if (!rem[fd] || !rem[fd])
	{
		free(rem[fd]);
		rem[fd] = NULL;
		return (NULL);
	}
	line = ft_getline(rem[fd]);
	if (!line)
	{
		free(rem[fd]);
		rem[fd] = NULL;
		return (NULL);
	}
	rem[fd] = ft_update(rem[fd]);
	return (line);
}
