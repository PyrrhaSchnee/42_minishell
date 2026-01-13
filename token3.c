/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:56:59 by yanli             #+#    #+#             */
/*   Updated: 2025/07/20 12:49:58 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin2(char *s)
{
	if (!s)
		return (0);
	else if (!ft_strcmp(s, "cd") && ft_strlen(s) == 2)
		return (2);
	else if (!ft_strcmp(s, "export") && ft_strlen(s) == 6)
		return (1);
	else if (!ft_strcmp(s, "pwd") && ft_strlen(s) == 3)
		return (3);
	else if (!ft_strcmp(s, "unset") && ft_strlen(s) == 5)
		return (4);
	else if (!ft_strcmp(s, "echo") && ft_strlen(s) == 4)
		return (5);
	else if (!ft_strcmp(s, "exit") && ft_strlen(s) == 4)
		return (6);
	else if (!ft_strcmp(s, "env") && ft_strlen(s) == 3)
		return (7);
	else
		return (0);
}

int	ft_isbuiltin(char *s)
{
	if (!s)
		return (0);
	else if (!ft_strncmp(s, "cd", 2) && (!s[2] || !ft_strncmp(s, "cd ", 3)))
		return (2);
	else if (!ft_strncmp(s, "export", 6) && (!s[6] || !ft_strncmp(s, "export ",
				7)))
		return (1);
	else if (!ft_strncmp(s, "pwd", 3) && (!s[3] || !ft_strncmp(s, "pwd ", 4)))
		return (3);
	else if (!ft_strncmp(s, "unset", 5) && (!s[5] || !ft_strncmp(s, "unset ",
				6)))
		return (4);
	else if (!ft_strncmp(s, "echo", 4) && (!s[4] || !ft_strncmp(s, "echo ", 5)))
		return (5);
	else if (!ft_strncmp(s, "exit", 4) && (!s[4] || !ft_strncmp(s, "exit ", 5)))
		return (6);
	else if (!ft_strncmp(s, "env", 3) && (!s[3] || !ft_strncmp(s, "env ", 4)))
		return (7);
	else
		return (0);
}

t_token	*mark_builtin(t_token *token)
{
	const t_token	*head = token;
	t_token			*prev_nospace;

	prev_nospace = NULL;
	while (token)
	{
		if (token->value && ft_isbuiltin2(token->value)
			&& token->type != TK_ENVP)
		{
			if (!prev_nospace || (prev_nospace->type != TK_REDIR_IN
					&& prev_nospace->type != TK_REDIR_OUT
					&& prev_nospace->type != TK_APPEND
					&& prev_nospace->type != TK_HEREDOC))
				token->type = TK_BUILTIN;
		}
		if (token->type != TK_SPACE)
			prev_nospace = token;
		token = token->next;
	}
	return ((t_token *)head);
}
