/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:42:16 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 13:59:57 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_allow_bin2(t_bin *cfg, char *command)
{
	while (cfg->split_path[cfg->i])
	{
		if (cfg->path_bin)
			free(cfg->path_bin);
		cfg->path_bin = ft_strjoin(cfg->split_path[cfg->i], "/");
		if (!cfg->path_bin)
		{
			ft_free_pstr(&cfg->split_path);
			return (0);
		}
		if (cfg->path_command)
			free(cfg->path_command);
		cfg->path_command = ft_strjoin(cfg->path_bin, command);
		if (!cfg->path_command)
		{
			ft_free_pstr(&cfg->split_path);
			free(cfg->path_bin);
			return (0);
		}
		if (access(cfg->path_command, X_OK) == 0)
			return (1);
		(cfg->i)++;
	}
	return (0);
}

static t_token	*get_cmd_start(t_token *t, size_t id)
{
	size_t	n;

	n = 0;
	if (!t)
		return (NULL);
	while (t && n < id)
	{
		if (t->type == TK_PIPE)
			n++;
		t = t->next;
	}
	return (t);
}

static int	parse_cmd_redir2(t_exec **exec, t_token **t)
{
	if (!exec || !*exec || !t || !*t)
		return (0);
	if ((*t)->type == TK_REDIR_IN && !find_infile_redir_filename(&(*t), *exec))
		return (0);
	else if ((*t)->type == TK_REDIR_OUT)
	{
		(*exec)->is_append = 0;
		if (!find_outfile_redir_filename(&(*t), *exec, REDIR_OUT))
			return (0);
	}
	else if ((*t)->type == TK_APPEND)
	{
		(*exec)->is_append = 1;
		if (!find_outfile_redir_filename(&(*t), *exec, REDIR_APPEND))
			return (0);
	}
	else if ((*t)->type == TK_HEREDOC)
		(*exec)->is_heredoc = 1;
	*t = (*t)->next;
	return (1);
}

int	parse_cmd_redirections(t_exec *exec, t_shell *shell, size_t id)
{
	t_token	*t;
	int		rt;

	if (!exec || !shell || !shell->token)
		return (0);
	ft_free_redir_filename(&exec->infile);
	ft_free_redir_filename(&exec->outfile);
	exec->is_append = 0;
	exec->is_heredoc = 0;
	t = get_cmd_start(shell->token, id);
	if (!t)
		return (0);
	while (t && t->type != TK_PIPE)
	{
		rt = parse_cmd_redir2(&exec, &t);
		if (!rt)
			return (0);
	}
	return (1);
}

int	check_and_exec(t_shell *shell)
{
	t_exec	exec;

	if (!shell || !shell->token)
		return (1);
	ft_memset(&exec, 0, sizeof(t_exec));
	exec.prev = -1;
	exec.token = shell->token;
	expand_envp_token(shell->token, shell);
	expand_embedded_envp(shell->token, shell);
	exec_command(&exec, shell);
	clean_exec(&exec);
	return (0);
}
