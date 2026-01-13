/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:22:32 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 22:54:33 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_delimiter_string(t_token *token, int *quoted)
{
	t_bds	cfg;

	ft_memset(&cfg, 0, sizeof(t_bds));
	cfg.curr = token->next;
	if (cfg.curr && cfg.curr->type == TK_SPACE)
		cfg.curr = cfg.curr->next;
	cfg.ret = ft_empty();
	while (cfg.curr && (cfg.curr->type == TK_WORD || cfg.curr->type == TK_ENVP
			|| cfg.curr->type == TK_RV))
	{
		build_delimiter_string2(&cfg, quoted);
		if (!cfg.word)
			return (free(cfg.ret), NULL);
		cfg.temp = ft_strjoin(cfg.ret, cfg.word);
		free(cfg.word);
		free(cfg.ret);
		if (!cfg.temp)
			return (NULL);
		cfg.ret = cfg.temp;
		cfg.curr = cfg.curr->next;
	}
	return (cfg.ret);
}

int	print_delimiter(t_token **token)
{
	char	*delim;

	delim = build_delimiter_string(*token, NULL);
	if (!delim)
		return (0);
	ft_putstr_fd(ERROR18, 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd("')", 2);
	free(delim);
	return (1);
}

static int	get_heredoc_delimiter2(t_token **token, t_ghd *cfg, t_heredoc *doc)
{
	ft_free_str(&doc->line);
	cfg->curr = (*token)->next;
	if (cfg->curr && cfg->curr->type == TK_SPACE)
		cfg->curr = cfg->curr->next;
	while (cfg->curr && (cfg->curr->type == TK_WORD
			|| cfg->curr->type == TK_ENVP || cfg->curr->type == TK_RV))
	{
		cfg->curr->type = TK_EOF;
		cfg->curr = cfg->curr->next;
	}
	if (cfg->quoted)
		doc->mode = 1;
	free(cfg->delim);
	return (1);
}

int	get_heredoc_delimiter(t_token **token, t_heredoc *doc)
{
	t_ghd	cfg;

	if (!token || !doc)
		return (0);
	ft_memset(&cfg, 0, sizeof(t_ghd));
	cfg.delim = build_delimiter_string(*token, &cfg.quoted);
	if (!cfg.delim)
		return (0);
	if (!ft_strncmp(doc->line, cfg.delim, ft_strlen(cfg.delim) + 1))
	{
		if (get_heredoc_delimiter2(token, &cfg, doc))
			return (1);
	}
	free(cfg.delim);
	return (0);
}
