/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:18 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 22:46:56 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type, t_parse_state quoted)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->quoted = quoted;
	new_token->next = NULL;
	return (new_token);
}

void	free_token(t_token **token)
{
	t_token	*temp;
	t_token	*current;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
	*token = NULL;
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!head)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

int	tokenizer(char *line, t_shell *shell)
{
	if (!quote_sanitizer(line))
		return (0);
	while (line[shell->p.i] && ft_isspace(line[shell->p.i]))
		(shell->p.i)++;
	while (line[shell->p.i])
		token_analyzer1(line, &shell->p);
	word_to_token(line, &shell->p);
	shell->p.token = mark_builtin(shell->p.token);
	if (!redir_sanitizer(&shell->p))
	{
		shell->rv = 2;
		return (token_nullification(shell), 0);
	}
	if (!handle_heredoc(shell->p.token, shell))
		return (token_nullification(shell), 0);
	expand_return_value(shell->p.token, shell);
	shell->token = shell->p.token;
	return (1);
}

int	ft_str_is_not_space(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] && !ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}
