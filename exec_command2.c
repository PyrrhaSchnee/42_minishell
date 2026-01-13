/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:06:51 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 11:31:51 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_heredoc(t_exec *exec)
{
	exec->fd_in = open(HEREDOC_TEMPFILE2, O_RDONLY);
	if (exec->fd_in == -1)
	{
		perror(exec->infile);
		return ;
	}
	dup2(exec->fd_in, STDIN_FILENO);
	close_fd(&exec->fd_in);
}

void	open_infile(t_exec *exec, t_shell *shell)
{
	int	errno2;

	exec->fd_in = open(exec->infile, O_RDONLY);
	if (exec->fd_in == -1)
	{
		errno2 = errno;
		print_errno("minishell", strerror(errno2));
		close_fd(&exec->prev);
		clean_exec(exec);
		ft_clean_all(shell);
		exit(EXIT_FAILURE);
	}
	dup2(exec->fd_in, STDIN_FILENO);
	close_fd(&exec->fd_in);
}

void	open_outfile(t_exec *exec, t_shell *shell)
{
	int	errno2;

	if (exec->is_append == 1)
		exec->fd_out = open(exec->outfile, O_APPEND | O_WRONLY | O_CREAT, 0666);
	else
		exec->fd_out = open(exec->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (exec->fd_out == -1)
	{
		errno2 = errno;
		print_errno("minishell", strerror(errno2));
		close_fd(&exec->prev);
		clean_exec(exec);
		ft_clean_all(shell);
		exit(EXIT_FAILURE);
	}
	dup2(exec->fd_out, STDOUT_FILENO);
	close_fd(&exec->fd_out);
}

void	exec_child_command(t_exec *exec, t_shell *shell)
{
	int	ret;

	if (is_builtin_cmd(exec->command[0]) && !ft_strchr(exec->command[0], '/'))
	{
		ret = run_builtin(exec->command, shell, exec);
		clean_exec(exec);
		ft_clean_all(shell);
		close_all_fd();
		exit(ret);
	}
	if (execve(exec->bin, exec->command, shell->envp2) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(exec->command[0]);
		ft_free_pstr(&exec->command);
		clean_exec(exec);
		close_all_fd();
		ft_clean_all(shell);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
}
