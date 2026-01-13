/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_sanitizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:28:20 by yanli             #+#    #+#             */
/*   Updated: 2025/07/09 15:10:28 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_sanitizer(t_token *t)
{
	if (!t->next || (t->next && t->next->type == TK_REDIR_IN))
		return (ft_putstr_fd(ERROR6, 2), 0);
	if (t->next->type == TK_HEREDOC || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_HEREDOC))
		return (ft_putstr_fd(ERROR10, 2), 0);
	if (t->next->type == TK_APPEND || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_APPEND))
		return (ft_putstr_fd(ERROR11, 2), 0);
	if (t->next->type == TK_REDIR_IN || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_REDIR_IN))
		return (ft_putstr_fd(ERROR12, 2), 0);
	if (t->next->type == TK_REDIR_OUT || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_REDIR_OUT))
		return (ft_putstr_fd(ERROR9, 2), 0);
	if ((t->next->type == TK_PIPE || (t->next->type == TK_SPACE && t->next->next
				&& t->next->next->type == TK_PIPE)))
		return (ft_putstr_fd(ERROR13, 2), 0);
	return (1);
}

static int	append_sanitizer(t_token *t)
{
	if (!t->next)
		return (ft_putstr_fd(ERROR6, 2), 0);
	if (t->next->type == TK_REDIR_OUT || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_REDIR_OUT))
		return (ft_putstr_fd(ERROR9, 2), 0);
	if (t->next->type == TK_REDIR_IN || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_REDIR_IN))
		return (ft_putstr_fd(ERROR10, 2), 0);
	if (t->next->type == TK_APPEND || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_APPEND))
		return (ft_putstr_fd(ERROR11, 2), 0);
	if (t->next->type == TK_HEREDOC || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_HEREDOC))
		return (ft_putstr_fd(ERROR12, 2), 0);
	if (t->next->type == TK_PIPE || (t->next->type == TK_SPACE && t->next->next
			&& t->next->next->type == TK_PIPE))
		return (ft_putstr_fd(ERROR13, 2), 0);
	return (1);
}

static int	redir_in_sanitizer(t_token *t)
{
	if (!t->next || (t->next && t->next->type == TK_REDIR_OUT))
		return (ft_putstr_fd(ERROR6, 2), 0);
	if (t->next->type == TK_SPACE && t->next->next
		&& t->next->next->type == TK_REDIR_IN)
		return (ft_putstr_fd(ERROR10, 2), 0);
	if (t->next->type == TK_SPACE && t->next->next
		&& t->next->next->type == TK_REDIR_OUT)
		return (ft_putstr_fd(ERROR9, 2), 0);
	if (t->next->type == TK_SPACE && t->next->next
		&& t->next->next->type == TK_HEREDOC)
		return (ft_putstr_fd(ERROR12, 2), 0);
	if (t->next->type == TK_APPEND || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_APPEND))
		return (ft_putstr_fd(ERROR9, 2), 0);
	if ((t->next->type == TK_SPACE && t->next->next
			&& t->next->next->type == TK_PIPE) || t->next->type == TK_PIPE)
		return (ft_putstr_fd(ERROR13, 2), 0);
	return (1);
}

static int	redir_out_sanitizer(t_token *t)
{
	if (!t->next)
		return (ft_putstr_fd(ERROR6, 2), 0);
	if (t->next->type == TK_REDIR_IN || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_REDIR_IN))
		return (ft_putstr_fd(ERROR10, 2), 0);
	if (t->next->type == TK_REDIR_OUT || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_REDIR_OUT))
		return (ft_putstr_fd(ERROR9, 2), 0);
	if (t->next->type == TK_PIPE || (t->next->type == TK_SPACE && t->next->next
			&& t->next->next->type == TK_PIPE))
		return (ft_putstr_fd(ERROR13, 2), 0);
	if (t->next->type == TK_SPACE && t->next->next
		&& t->next->next->type == TK_APPEND)
		return (ft_putstr_fd(ERROR11, 2), 0);
	if (t->next->type == TK_HEREDOC || (t->next->type == TK_SPACE
			&& t->next->next && t->next->next->type == TK_HEREDOC))
		return (ft_putstr_fd(ERROR12, 2), 0);
	return (1);
}

int	redir_sanitizer(t_tk_param *p)
{
	t_token	*t;

	t = p->token;
	while (t)
	{
		if (t->type == TK_HEREDOC && !heredoc_sanitizer(t))
			break ;
		else if (t->type == TK_APPEND && !append_sanitizer(t))
			break ;
		else if (t->type == TK_REDIR_IN && !redir_in_sanitizer(t))
			break ;
		else if (t->type == TK_REDIR_OUT && !redir_out_sanitizer(t))
			break ;
		else if (t->type == TK_PIPE && !pipe_sanitizer(t))
			break ;
		t = t->next;
	}
	if (t)
		return (0);
	return (1);
}
