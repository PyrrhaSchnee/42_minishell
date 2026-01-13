/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:49:31 by yanli             #+#    #+#             */
/*   Updated: 2025/07/08 14:20:10 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_analyzer1(char *line, t_tk_param *p)
{
	if (line[p->i] == '\'' && p->state == STATE_GENERAL)
	{
		if (line[p->i + 1] && line[p->i + 1] == '\'')
			(p->i) += 2;
		else
		{
			word_to_token(line, p);
			p->state = STATE_IN_SINGLE;
			(p->i)++;
		}
	}
	else if (line[p->i] == '"' && p->state == STATE_GENERAL)
	{
		if (line[p->i + 1] && line[p->i + 1] == '"')
			(p->i) += 2;
		else
		{
			word_to_token(line, p);
			p->state = STATE_IN_DOUBLE;
			(p->i)++;
		}
	}
	else
		token_analyzer1a(line, p);
}

void	token_analyzer1a(char *line, t_tk_param *p)
{
	if (line[p->i] == '\'' && p->state == STATE_IN_SINGLE)
	{
		word_to_token(line, p);
		p->state = STATE_GENERAL;
		(p->i)++;
	}
	else if (line[p->i] == '"' && p->state == STATE_IN_DOUBLE)
	{
		word_to_token(line, p);
		p->state = STATE_GENERAL;
		(p->i)++;
	}
	else if (p->state == STATE_GENERAL)
		token_analyzer2(line, p);
	else
		token_return_value(line, p, 1);
}

void	token_analyzer2(char *line, t_tk_param *p)
{
	if (p->state == STATE_GENERAL && ft_isspace(line[p->i]))
		jump_space(line, p);
	else if (line[p->i] == '|')
	{
		word_to_token(line, p);
		append_token(&p->token, new_token(ft_strdup("|"), TK_PIPE, p->state));
		(p->i)++;
	}
	else if (line[p->i] == '>' && line[p->i + 1] && line[p->i + 1] == '>')
	{
		word_to_token(line, p);
		append_token(&p->token, new_token(ft_strdup(">>"), TK_APPEND,
				p->state));
		(p->i) += 2;
	}
	else
		token_analyzer3(line, p);
}

static void	token_heredoc(char *line, t_tk_param *p)
{
	word_to_token(line, p);
	append_token(&p->token, new_token(ft_strdup("<<"), TK_HEREDOC, p->state));
	if (line[p->i + 2] && line[p->i + 3] && ((line[p->i + 2] == '"'
				&& line[p->i + 3] == '"') || (line[p->i + 2] == '\''
				&& line[p->i + 3] == '\'')))
	{
		append_token(&p->token, new_token(ft_empty(), TK_WORD, p->state));
		(p->i) += 4;
	}
	else
		(p->i) += 2;
}

void	token_analyzer3(char *line, t_tk_param *p)
{
	if (line[p->i] == '>')
	{
		word_to_token(line, p);
		append_token(&p->token, new_token(ft_strdup(">"), TK_REDIR_OUT,
				p->state));
		(p->i)++;
	}
	else if (line[p->i] == '<' && line[p->i + 1] && line[p->i + 1] == '<')
		token_heredoc(line, p);
	else if (line[p->i] == '<')
	{
		word_to_token(line, p);
		append_token(&p->token, new_token(ft_strdup("<"), TK_REDIR_IN,
				p->state));
		(p->i)++;
	}
	else
		token_return_value(line, p, 0);
}
