/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:10:38 by yanli             #+#    #+#             */
/*   Updated: 2025/07/20 12:45:17 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command3(t_cmd_bi *cfg, t_exec *exec, t_shell *shell)
{
	if (!parse_cmd_redirections(exec, shell, 0))
	{
		shell->rv = 1;
		ft_free_pstr(&(cfg->cmd));
		ft_free_pstr(&(exec->tab_command));
		clean_exec(exec);
		return (0);
	}
	builtin_fd_redir(cfg, exec, shell);
	shell->rv = run_builtin(cfg->cmd, shell, exec);
	builtin_fd_reset(cfg);
	return (1);
}

void	prepare_command_and_pathname(t_exec *exec, t_shell *shell)
{
	exec->tab_command = put_in_tab(shell->token);
	shell->nbr_child = count_total_element(shell->token);
	exec->pathname = get_path(shell->envp2);
	if (!exec->pathname)
		exec->pathname = exec->empty;
}

void	clean_exec(t_exec *e)
{
	ft_free_str(&e->infile);
	ft_free_str(&e->outfile);
	ft_free_pstr(&e->tab_command);
	ft_free_pstr(&e->command);
}

int	is_absolute_path(t_exec *exec, t_shell *shell)
{
	if (!exec || !exec->command[0] || !exec->command[0][0])
		return (0);
	if (!ft_strchr(exec->command[0], '/'))
		return (0);
	if (!ft_strcmp(exec->command[0], "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		exit(2);
	}
	check_if_is_directory(exec, shell);
	return (1);
}

int	set_child_fd(t_exec *e, t_shell *shell, const size_t id)
{
	if (id > 0)
	{
		if (dup2(e->prev, STDIN_FILENO) == -1)
			return (perror(ft_itoa(e->id)), 1);
		close(e->prev);
	}
	if (id < shell->nbr_child - 1)
	{
		if (dup2(e->fd[1], STDOUT_FILENO) == -1)
			return (perror(ft_itoa(e->id)), 1);
		close_fd(&e->fd[1]);
		close_fd(&e->fd[0]);
	}
	if (id > 0 && id == shell->nbr_child - 1)
		close_fd(&e->fd[1]);
	return (0);
}
