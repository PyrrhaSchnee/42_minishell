/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:28:14 by nlienard          #+#    #+#             */
/*   Updated: 2025/07/16 11:58:41 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_redir_tok(t_token **token)
{
	while (*token && ((*token)->type == TK_REDIR_IN
			|| (*token)->type == TK_REDIR_OUT || (*token)->type == TK_APPEND
			|| (*token)->type == TK_HEREDOC))
	{
		if ((*token)->next && (*token)->next->type == TK_SPACE)
			*token = (*token)->next->next;
		else
			*token = (*token)->next;
		if (*token && (*token)->type == TK_WORD)
			*token = (*token)->next;
	}
}

static int	find_first_word(t_token **token)
{
	if ((*token) && (*token)->type == TK_PIPE)
		(*token) = (*token)->next;
	skip_redir_tok(token);
	if (*token && (*token)->type == TK_PIPE)
		return (0);
	while (*token && (*token)->type != TK_WORD && (*token)->type != TK_BUILTIN)
	{
		if ((*token)->type == TK_PIPE)
			return (0);
		skip_redir_tok(token);
		if (*token && (*token)->type != TK_WORD && (*token)->type != TK_BUILTIN)
			*token = (*token)->next;
	}
	return (0);
}

void	append_with_placeholder(char *dst, char *src, size_t size,
		t_parse_state quoted)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] && i + 1 < size)
	{
		if (quoted != STATE_GENERAL && src[j] == ' ')
			dst[i++] = SPACE_PLACEHOLDER;
		else
			dst[i++] = src[j];
		j++;
	}
	dst[i] = '\0';
}

static char	**put_in_tab3(t_token *token, char **tab_cmd, const size_t nb_elem)
{
	size_t	i;

	i = 0;
	while (token && i < nb_elem)
	{
		find_first_word(&token);
		if (!token)
		{
			tab_cmd[i++] = ft_empty();
			break ;
		}
		if (token->type == TK_PIPE)
			tab_cmd[i] = ft_empty();
		else
		{
			tab_cmd[i] = fill_tab(&token);
			if (!tab_cmd[i])
				return (free(tab_cmd), NULL);
			while (token && token->type != TK_PIPE)
				token = token->next;
		}
		i++;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}

char	**put_in_tab(t_token *token)
{
	char			**tab_cmd;
	const size_t	nb_elem = count_total_element(token);

	if (!token)
		return (NULL);
	tab_cmd = ft_calloc(nb_elem + 1, sizeof(char *));
	if (!tab_cmd)
		return (NULL);
	return (put_in_tab3(token, tab_cmd, nb_elem));
}
