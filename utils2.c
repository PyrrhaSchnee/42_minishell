/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 07:30:41 by nlienard          #+#    #+#             */
/*   Updated: 2025/07/11 16:29:39 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_total(t_token *token)
{
	size_t	count;

	if (!token)
		return (0);
	count = 0;
	while (token && token->type != TK_PIPE)
	{
		if (is_fd_dir(token))
		{
			token = token->next;
			continue ;
		}
		if (token->type == TK_WORD || token->type == TK_BUILTIN
			|| token->type == TK_SPACE)
			count += ft_strlen(token->value);
		token = token->next;
	}
	return (count);
}

char	*get_path(char **envp)
{
	size_t	i;

	i = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	return (envp[i]);
}

char	*ft_empty(void)
{
	char	*r;

	r = ft_calloc(sizeof(char), 1);
	if (!r)
		return (NULL);
	r[0] = '\0';
	return (r);
}

void	ft_free_pids(pid_t **s)
{
	if (!s || !*s)
		return ;
	free(*s);
	(*s) = NULL;
}

int	is_fd_dir(t_token *t)
{
	size_t	i;

	i = 0;
	if (!t || t->type != TK_WORD || !t->next)
		return (0);
	if (t->next->type != TK_REDIR_IN && t->next->type != TK_HEREDOC
		&& t->next->type != TK_APPEND && t->next->type != TK_HEREDOC)
		return (0);
	while (t->value[i])
	{
		if (!ft_isdigit(t->value[i]))
			return (0);
		i++;
	}
	return (1);
}
