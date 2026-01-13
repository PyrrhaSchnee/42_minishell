/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:52:13 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 11:36:51 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_fail_close_fd(t_exec *e)
{
	if (!e)
		return ;
	close_fd(&e->fd[0]);
	close_fd(&e->fd[1]);
	close_fd_prev(&e->prev);
}

void	child_pipe(t_exec *exec, t_shell *shell, const size_t id)
{
	if (!parse_cmd_redirections(exec, shell, id))
	{
		clean_exec(exec);
		select_close_fd(id, shell->nbr_child);
		ft_clean_all(shell);
		exit(EXIT_FAILURE);
	}
	if (exec->tab_command && exec->tab_command[id])
		exec->command = split_placeholder(exec->tab_command[id]);
	else
		exec->command = NULL;
	if (exec->tab_command && exec->tab_command[id] && !exec->command)
		ft_error2();
	if (!exec->command || !exec->command[0])
		create_file_then_quit(exec, shell);
	child_pipe_handle_builtin(exec, shell);
	child_pipe2(exec, shell);
}

void	child_pipe2(t_exec *exec, t_shell *shell)
{
	if (exec->is_heredoc && is_builtin_cmd(exec->command[0]) != 1)
		get_heredoc(exec);
	else if (exec->infile && is_builtin_cmd(exec->command[0]) != 1)
		open_infile(exec, shell);
	if (exec->outfile)
		open_outfile(exec, shell);
	exec_child_command(exec, shell);
}

static void	handle_fork2(t_shell *shell, t_exec *e, pid_t pid)
{
	shell->pids[(pid_t)e->id] = pid;
	close_fd_prev(&e->prev);
	if (e->id < shell->nbr_child - 1)
	{
		close_fd(&e->fd[1]);
		e->prev = e->fd[0];
	}
}

int	handle_fork(t_shell *shell, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		pipe_fail_close_fd(exec);
		return (1);
	}
	else if (pid == 0)
	{
		set_child_signal();
		if (set_child_fd(exec, shell, exec->id))
			return (1);
		child_pipe(exec, shell, exec->id);
		return (0);
	}
	else
	{
		handle_fork2(shell, exec, pid);
		return (0);
	}
}
