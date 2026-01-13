/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:20:10 by yanli             #+#    #+#             */
/*   Updated: 2025/07/10 12:29:36 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_state_info(t_parse_state s)
{
	if (s == STATE_GENERAL)
		printf("Quoting state: STATE_GENERAL\n");
	else if (s == STATE_IN_DOUBLE)
		printf("Quoting state: STATE_IN_DOUBLE\n");
	else if (s == STATE_IN_SINGLE)
		printf("Quoting state: STATE_IN_SINGLE\n");
}

static void	print_token_type(t_token *token)
{
	if (token->type == TK_WORD)
		printf("Token type: %-14s", "TK_WORD");
	else if (token->type == TK_PIPE)
		printf("Token type: %-14s", "TK_PIPE");
	else if (token->type == TK_REDIR_IN)
		printf("Token type: %-14s", "TK_REDIR_IN");
	else if (token->type == TK_REDIR_OUT)
		printf("Token type: %-14s", "TK_REDIR_OUT");
	else if (token->type == TK_APPEND)
		printf("Token type: %-14s", "TK_APPEND");
	else if (token->type == TK_HEREDOC)
		printf("Token type: %-14s", "TK_HEREDOC");
	else if (token->type == TK_EOF)
		printf("Token type: %-14s", "TK_EOF");
	else if (token->type == TK_BUILTIN)
		printf("Token type: %-14s", "TK_BUILTIN");
	else if (token->type == TK_ENVP)
		printf("Token type: %-14s", "TK_ENVP");
	else if (token->type == TK_SPACE)
		printf("Token type: %-14s", "TK_SPACE");
	else if (token->type == TK_RV)
		printf("Token type: %-14s", "TK_RV");
}

void	print_token_info(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	while (temp)
	{
		printf("Token word: %-10s ", temp->value);
		print_token_type(temp);
		print_state_info(temp->quoted);
		temp = temp->next;
	}
}

void	print_pstr(char **s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return ;
	while (s[i])
		printf("%s\n", s[i++]);
}

void	reach(void)
{
	write(2, "I have reached here\n", 20);
}
