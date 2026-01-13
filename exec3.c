/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:17:57 by yanli             #+#    #+#             */
/*   Updated: 2025/07/10 19:29:25 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_outfile_filename2(t_token **token, t_exec *e, t_redir_type rt)
{
	t_token	*t;

	t = *token;
	ft_free_redir_filename(&e->outfile);
	e->outfile = ft_strdup(t->next->next->value);
	if (t->next->next->next && t->next->next->next->type == TK_WORD)
		e->outfile = redir_filename_join(&(t->next->next->next), e, e->outfile);
	if (!redir_file_open_test(&e->outfile, rt))
		return (0);
	t = t->next->next;
	return (1);
}

int	find_outfile_redir_filename(t_token **token, t_exec *e, t_redir_type rt)
{
	t_token	*t;

	if (!token || !*token)
		return (0);
	t = *token;
	if (t->next && t->next->type == TK_SPACE && t->next->next
		&& t->next->next->type == TK_WORD)
		return (find_outfile_filename2(token, e, rt));
	else if (t->next && t->next->type == TK_WORD)
	{
		ft_free_redir_filename(&e->outfile);
		e->outfile = ft_strdup(t->next->value);
		if (t->next->next && t->next->next->type == TK_WORD)
			e->outfile = redir_filename_join(&(t->next->next), e, e->outfile);
		if (!redir_file_open_test(&e->outfile, rt))
			return (0);
		t = t->next;
		return (1);
	}
	return (0);
}

static int	find_infile_filename2(t_token **token, t_exec *e)
{
	t_token	*t;

	t = *token;
	ft_free_redir_filename(&e->infile);
	e->infile = ft_strdup(t->next->next->value);
	if (t->next->next->next && t->next->next->next->type == TK_WORD)
		e->infile = redir_filename_join(&(t->next->next->next), e, e->infile);
	if (!redir_file_open_test(&e->infile, REDIR_IN))
		return (0);
	t = t->next->next;
	return (1);
}

int	find_infile_redir_filename(t_token **token, t_exec *e)
{
	t_token	*t;

	if (!token || !*token)
		return (0);
	t = *token;
	if (t->next && t->next->type == TK_SPACE && t->next->next
		&& t->next->next->type == TK_WORD)
		return (find_infile_filename2(token, e));
	else if (t->next && t->next->type == TK_WORD)
	{
		ft_free_redir_filename(&e->infile);
		e->infile = ft_strdup(t->next->value);
		if (t->next->next && t->next->next->type == TK_WORD)
			e->infile = redir_filename_join(&(t->next->next), e, e->infile);
		if (!redir_file_open_test(&e->infile, REDIR_IN))
			return (0);
		t = t->next;
		return (1);
	}
	return (0);
}
