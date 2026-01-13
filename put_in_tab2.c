/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_tab2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:01:23 by yanli             #+#    #+#             */
/*   Updated: 2025/07/15 16:28:34 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	shortcut_condition(t_token_type elem)
{
	if (elem == TK_REDIR_IN || elem == TK_REDIR_OUT || elem == TK_APPEND
		|| elem == TK_HEREDOC || elem == TK_PIPE || elem == TK_EOF)
		return (1);
	return (0);
}

static int	fill_tab_move_token(t_token ***token)
{
	t_token	*curr;

	if ((**token)->type == TK_EOF)
	{
		(**token) = (**token)->next;
		return (1);
	}
	if ((**token)->type == TK_WORD && is_fd_dir(**token))
	{
		(**token) = (**token)->next;
		return (1);
	}
	if ((**token)->type == TK_HEREDOC || (**token)->type == TK_APPEND
		|| (**token)->type == TK_REDIR_IN || (**token)->type == TK_REDIR_OUT)
	{
		curr = (**token)->next;
		if (curr && curr->type == TK_SPACE)
			curr = curr->next;
		while (curr && curr->type == TK_WORD)
			curr = curr->next;
		(**token) = curr;
		return (1);
	}
	return (0);
}

char	*fill_tab(t_token **token)
{
	char	*str;
	size_t	size;

	if (!token || !*token)
		return (NULL);
	size = ft_strlen_total(*token) + 1;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	while ((*token) && (*token)->type != TK_PIPE)
	{
		if (!fill_tab_move_token(&token))
		{
			append_with_placeholder(str, (*token)->value, size,
				(*token)->quoted);
			(*token) = (*token)->next;
			if ((*token) && (*token)->type == TK_SPACE)
			{
				ft_strlcat(str, (*token)->value, size);
				(*token) = (*token)->next;
			}
		}
	}
	return (str);
}
