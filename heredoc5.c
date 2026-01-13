/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:05:55 by yanli             #+#    #+#             */
/*   Updated: 2025/07/18 16:02:54 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_try_expansion(t_shell *shell, t_heredoc_envp *cfg)
{
	cfg->expanded = envp_retrieve_value(shell->envp, cfg->temp);
	if (!cfg->expanded)
	{
		write(cfg->fd2, "\n", 1);
		ft_free_str(&cfg->line);
		cfg->line = get_next_line(cfg->fd1);
		return ;
	}
	if (cfg->currline < cfg->totline)
		cfg->expanded = replace_eof_by_newline(cfg->expanded);
	cfg->currline++;
	write(cfg->fd2, cfg->expanded, ft_strlen(cfg->expanded));
	ft_free_str(&cfg->expanded);
	ft_free_str(&cfg->line);
	cfg->line = get_next_line(cfg->fd1);
}

int	need_expansion(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '$' && s[i + 1] && (s[i + 1] == '?' || is_start(s[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

void	build_delimiter_string2(t_bds *cfg, int *quoted)
{
	if (quoted && cfg->curr->quoted != STATE_GENERAL)
		*quoted = 1;
	if (cfg->curr->type == TK_ENVP)
		cfg->word = ft_strjoin("$", cfg->curr->value);
	else if (cfg->curr->type == TK_RV)
		cfg->word = ft_strdup("$?");
	else
		cfg->word = ft_strdup(cfg->curr->value);
}

void	child_acquisition_heredoc(t_token **token, t_shell *shell)
{
	set_heredoc_signal();
	if (!read_heredoc(shell, token))
	{
		token_nullification(shell);
		ft_clean_all(shell);
		if (g_signal == SIGINT)
			exit(130);
		exit(1);
	}
	token_nullification(shell);
	ft_clean_all(shell);
	exit(0);
}

int	parent_acquisition_heredoc(t_shell *shell, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status)))
	{
		if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
			shell->rv = 130;
		return (0);
	}
	return (1);
}
