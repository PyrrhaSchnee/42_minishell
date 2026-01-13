/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:37:53 by yanli             #+#    #+#             */
/*   Updated: 2025/07/10 12:39:44 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	jump_invalid_envp(char *s, t_tk_param *p)
{
	size_t	i;

	i = 0;
	if (s[i] && !ft_isalpha(s[i]) && s[i] != '_')
	{
		(p->i) += 2;
		return ;
	}
	i++;
	while (s[i] && !ft_isalnum(s[i]) && s[i] != '_')
		i++;
	(p->i) += (i + 1);
	return ;
}

void	insert_token_separator(t_tk_param *p)
{
	if (!p->word)
		append_token(&p->token, new_token(ft_strdup(" "), TK_SPACE, p->state));
}

void	expand_return_value(t_token *token, t_shell *shell)
{
	if (!token)
		return ;
	while (token)
	{
		if (token->type == TK_RV)
		{
			if (token->value)
				free(token->value);
			token->value = ft_itoa((int)shell->rv);
			if (!token->value)
				exit(EXIT_FAILURE);
			token->type = TK_WORD;
		}
		token = token->next;
	}
}
