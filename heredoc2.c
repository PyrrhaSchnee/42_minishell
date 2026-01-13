/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:33:50 by yanli             #+#    #+#             */
/*   Updated: 2025/07/18 15:08:23 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	action_heredoc_signal(t_token **token, t_heredoc *doc)
{
	if (g_signal == SIGINT)
	{
		if (doc->line)
			free(doc->line);
		doc->line = NULL;
		return (0);
	}
	if (!doc->line)
	{
		if (g_signal != SIGINT)
			return (print_delimiter(token));
		return (0);
	}
	return (2);
}

static int	join_heredoc(t_heredoc *doc)
{
	doc->temp = ft_strjoin(doc->line, "\n");
	ft_free_str(&doc->line);
	if (!doc->temp)
		return (ft_free_str(&doc->joined), 0);
	doc->line = ft_strjoin(doc->joined, doc->temp);
	ft_free_str(&doc->temp);
	ft_free_str(&doc->joined);
	return (1);
}

static int	read_heredoc2(t_token **token, t_heredoc *doc)
{
	int	signal_status;

	doc->joined = NULL;
	while (1)
	{
		doc->line = readline("> ");
		signal_status = action_heredoc_signal(token, doc);
		if (signal_status == 1)
			return (1);
		if (signal_status == 0)
			return (0);
		if (get_heredoc_delimiter(token, doc))
			return (1);
		if (!join_heredoc(doc))
			return (0);
		if (!doc->line)
			return (0);
		doc->joined = doc->line;
	}
}

int	read_heredoc(t_shell *shell, t_token **token)
{
	int			status;
	t_heredoc	doc;
	int			fd;

	ft_memset(&doc, 0, sizeof(t_heredoc));
	status = read_heredoc2(token, &doc);
	if (!status)
	{
		if (doc.joined)
			free(doc.joined);
		return (0);
	}
	if (doc.joined && !doc.mode)
		return (heredoc_envp_expansion(shell, &doc));
	fd = open(HEREDOC_TEMPFILE2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (free(doc.joined), 0);
	write(fd, doc.joined, ft_strlen(doc.joined));
	ft_free_str(&doc.joined);
	close_fd(&fd);
	return (1);
}
