/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:04:00 by yanli             #+#    #+#             */
/*   Updated: 2025/07/13 11:43:28 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_child_exit_status(t_shell *shell)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < shell->nbr_child)
	{
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			return ;
		}
		if (WIFSIGNALED(status))
		{
			shell->rv = WTERMSIG(status) + 128;
			print_child_sigmsg(&status);
		}
		else if (WIFEXITED(status))
			shell->rv = WEXITSTATUS(status);
		i++;
	}
}

void	child_pipe_handle_builtin(t_exec *exec, t_shell *shell)
{
	if (!ft_strcmp(exec->command[0], "exit"))
		exit_builtin(exec->command, shell, 0, exec);
	if (is_builtin_cmd(exec->command[0]) && !ft_strchr(exec->command[0], '/'))
	{
		exec->bin = NULL;
		return ;
	}
	if (is_absolute_path(exec, shell) == 1)
		exec->bin = exec->command[0];
	else
		exec->bin = get_allow_bin(exec->pathname, exec->command[0]);
	if (exec->bin)
		return ;
	if (!is_builtin_cmd(exec->command[0]))
		handle_no_exec_bin(exec, shell);
}

int	exec_command2(t_exec *exec, t_shell *shell)
{
	t_cmd_bi	cfg;

	prepare_command_and_pathname(exec, shell);
	if (shell->nbr_child == 1 && exec->tab_command && exec->tab_command[0])
	{
		ft_memset(&cfg, 0, sizeof(t_cmd_bi));
		cfg.cmd = split_placeholder(exec->tab_command[0]);
		if (cfg.cmd && is_builtin_cmd(cfg.cmd[0]) && !ft_strchr(cfg.cmd[0],
				'/'))
		{
			if (!exec_command3(&cfg, exec, shell))
				return (0);
			clean_exec(exec);
			ft_free_pstr(&(cfg.cmd));
			return (0);
		}
		ft_free_pstr(&(cfg.cmd));
	}
	shell->pids = ft_calloc(shell->nbr_child, sizeof(pid_t));
	return (1);
}

int	pipe_before_fork(t_exec *exec, t_shell *shell)
{
	if (exec->id == shell->nbr_child - 1)
		return (0);
	if (pipe(exec->fd) == -1)
	{
		close_fd(&exec->fd[0]);
		close_fd(&exec->fd[1]);
		close_fd(&exec->prev);
		return (1);
	}
	return (0);
}

int	exec_command(t_exec *exec, t_shell *shell)
{
	if (!exec_command2(exec, shell))
		return (0);
	if (!shell->pids)
		exit(EXIT_FAILURE);
	while (exec->id < shell->nbr_child)
	{
		if (pipe_before_fork(exec, shell))
			return (1);
		if (handle_fork(shell, exec))
			return (1);
		(exec->id)++;
	}
	get_child_exit_status(shell);
	unlink(HEREDOC_TEMPFILE);
	unlink(HEREDOC_TEMPFILE2);
	return (0);
}
