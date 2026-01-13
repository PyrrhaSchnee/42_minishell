/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:33:25 by yanli             #+#    #+#             */
/*   Updated: 2025/07/12 10:55:39 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_child_sigmsg2(int *status)
{
	if (WTERMSIG(*status) == SIGXCPU)
		ft_putstr_fd("CPU time limit exceeded (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGXFSZ)
		ft_putstr_fd("File size limit exceeded (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGILL)
		ft_putstr_fd("Illegal instruction (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGTTIN)
		ft_putstr_fd("Stopped\n", STDERR_FILENO);
}

void	print_child_sigmsg(int *status)
{
	if (WTERMSIG(*status) == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (WTERMSIG(*status) == SIGSEGV)
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGABRT)
		ft_putstr_fd("Aborted (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGKILL)
		ft_putstr_fd("Killed\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGFPE)
		ft_putstr_fd("Floating point execption (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status == SIGBUS))
		ft_putstr_fd("Bus error (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGTRAP)
		ft_putstr_fd("Trace/breakpoint trap (core dumped)\n", STDERR_FILENO);
	else if (WTERMSIG(*status) == SIGSYS)
		ft_putstr_fd("Bad system call (core dumped)\n", STDERR_FILENO);
	else
		print_child_sigmsg2(status);
}
