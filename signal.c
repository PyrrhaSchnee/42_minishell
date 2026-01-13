/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:47:38 by yanli             #+#    #+#             */
/*   Updated: 2025/07/19 22:46:42 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_child_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGQUIT, &sa, NULL)
		|| sigaction(SIGINT, &sa, NULL))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

static void	signal_main_interactive(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	set_signal_handler(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = signal_main_interactive;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		perror("minishell: sigaction");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL))
	{
		perror("minishell: sigaction");
		exit(EXIT_FAILURE);
	}
}
