/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:05:08 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 15:18:22 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_eof_by_newline(char *s)
{
	const size_t	slen = ft_strlen(s);
	char			*r;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	r = ft_calloc(slen + 2, sizeof(char));
	if (!r)
		return (NULL);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i++] = '\n';
	r[i] = '\0';
	free(s);
	return (r);
}

static char	*remove_newline(char *s)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (j < i)
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static int	heredoc_prepare_fd(t_heredoc *doc, t_heredoc_envp *cfg)
{
	cfg->fd1 = open(HEREDOC_TEMPFILE, O_RDWR | O_CREAT | O_TRUNC, 0666);
	cfg->fd2 = open(HEREDOC_TEMPFILE2, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (cfg->fd1 < 0 || cfg->fd2 < 0 || write(cfg->fd1, doc->joined,
			ft_strlen(doc->joined)) == -1)
		return (perror("minishell"), 0);
	close_fd(&cfg->fd1);
	cfg->fd1 = open(HEREDOC_TEMPFILE, O_RDONLY);
	cfg->totline = 1;
	cfg->line = get_next_line(cfg->fd1);
	while (cfg->line)
	{
		cfg->totline++;
		ft_free_str(&cfg->line);
		cfg->line = get_next_line(cfg->fd1);
	}
	close_fd(&cfg->fd1);
	return (1);
}

static void	heredoc_envp_loop(t_shell *shell, t_heredoc_envp *cfg)
{
	while (cfg->line)
	{
		if (need_expansion(cfg->line))
		{
			cfg->temp = remove_newline(cfg->line);
			cfg->expanded = expand_str(cfg->temp, shell);
			ft_free_str(&cfg->temp);
			if (cfg->currline < cfg->totline)
				cfg->expanded = replace_eof_by_newline(cfg->expanded);
			cfg->currline++;
			write(cfg->fd2, cfg->expanded, ft_strlen(cfg->expanded));
			ft_free_str(&cfg->expanded);
		}
		else
			write(cfg->fd2, cfg->line, ft_strlen(cfg->line));
		ft_free_str(&cfg->line);
		cfg->line = get_next_line(cfg->fd1);
	}
}

int	heredoc_envp_expansion(t_shell *shell, t_heredoc *doc)
{
	t_heredoc_envp	*cfg;

	cfg = ft_calloc(sizeof(t_heredoc_envp), 1);
	if (!heredoc_prepare_fd(doc, cfg))
		return (0);
	cfg->fd1 = open(HEREDOC_TEMPFILE, O_RDONLY);
	cfg->line = get_next_line(cfg->fd1);
	if (!cfg->line)
		return (0);
	heredoc_envp_loop(shell, cfg);
	ft_free_str(&doc->joined);
	close_fd(&cfg->fd1);
	close_fd(&cfg->fd2);
	free(cfg);
	return (1);
}
