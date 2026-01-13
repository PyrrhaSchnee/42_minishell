/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:52:54 by yanli             #+#    #+#             */
/*   Updated: 2025/07/20 12:40:44 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	determine_close_mode(const size_t id, const size_t nbr_child)
{
	if (id && id < nbr_child - 1)
		return (2);
	if (id == nbr_child - 1)
		return (0);
	if (id == 0)
		return (1);
	return (3);
}

void	select_close_fd(const size_t id, const size_t nbr_child)
{
	const int	mode = determine_close_mode(id, nbr_child);

	if (mode == 2)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	if (mode == 1)
		close(STDOUT_FILENO);
	if (mode == 0)
		close(STDIN_FILENO);
}

void	builtin_fd_redir(t_cmd_bi *cfg, t_exec *e, t_shell *shell)
{
	cfg->save_in = -1;
	cfg->save_out = -1;
	if (e->infile)
	{
		if (!cfg->cmd || ft_strcmp(cfg->cmd[0], "exit"))
			cfg->save_in = dup(STDIN_FILENO);
		if (e->is_heredoc)
			get_heredoc(e);
		else
			open_infile(e, shell);
	}
	if (e->outfile)
	{
		if (!cfg->cmd || ft_strcmp(cfg->cmd[0], "exit"))
			cfg->save_out = dup(STDOUT_FILENO);
		open_outfile(e, shell);
	}
}

void	builtin_fd_reset(t_cmd_bi *cfg)
{
	if (cfg->save_in != -1)
	{
		dup2(cfg->save_in, STDIN_FILENO);
		close_fd(&cfg->save_in);
	}
	if (cfg->save_out != -1)
	{
		dup2(cfg->save_out, STDOUT_FILENO);
		close_fd(&cfg->save_out);
	}
}

void	check_if_is_directory(t_exec *e, t_shell *shell)
{
	int	fd;

	fd = open(e->command[0], O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		errno = EISDIR;
		perror(e->command[0]);
		close_fd(&fd);
		close_fd(&e->fd[1]);
		close_fd_prev(&(e->prev));
		clean_exec(e);
		ft_clean_all(shell);
		exit(126);
	}
}
