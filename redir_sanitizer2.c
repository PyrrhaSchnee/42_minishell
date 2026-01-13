/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_sanitizer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:48:50 by yanli             #+#    #+#             */
/*   Updated: 2025/07/05 16:31:14 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_sanitizer(t_token *t)
{
	if (!t->next)
		return (ft_putstr_fd(ERROR13, 2), 0);
	if (t->next->type == TK_HEREDOC || t->next->type == TK_APPEND
		|| t->next->type == TK_REDIR_IN || t->next->type == TK_REDIR_OUT)
		return (ft_putstr_fd(ERROR13, 2), 0);
	if (t->next->type == TK_PIPE)
		return (ft_putstr_fd(ERROR14, 2), 0);
	if (t->next->type == TK_SPACE && !t->next->next)
		return (ft_putstr_fd(ERROR13, 2), 0);
	if (t->next->next && t->next->next->type == TK_SPACE
		&& (t->next->next->type == TK_PIPE || t->next->next->type == TK_APPEND
			|| t->next->next->type == TK_HEREDOC
			|| t->next->next->type == TK_REDIR_IN
			|| t->next->next->type == TK_REDIR_OUT))
		return (ft_putstr_fd(ERROR13, 2), 0);
	return (1);
}

void	token_nullification(t_shell *shell)
{
	if (shell->token)
		free_token(&shell->token);
	shell->token = NULL;
	if (shell->p.token)
		free_token(&shell->p.token);
	shell->p.token = NULL;
}
