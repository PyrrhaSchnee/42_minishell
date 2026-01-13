/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:35:22 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 11:55:34 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file_then_quit(t_exec *exec, t_shell *shell)
{
	if (exec->is_heredoc)
		get_heredoc(exec);
	else if (exec->infile)
		open_infile(exec, shell);
	if (exec->outfile)
		open_outfile(exec, shell);
	clean_exec(exec);
	ft_clean_all(shell);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	exit(0);
}
