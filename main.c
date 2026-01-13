/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:02:32 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 17:56:01 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	run_shell(t_shell *shell)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		rl_done = 0;
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (g_signal == SIGINT)
			shell->rv = 130;
		if (line[0])
			add_history(line);
		if (tokenizer(line, shell))
			check_and_exec(shell);
		clean_after_exec(&line, shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	run_shell(&shell);
	ft_clean_all(&shell);
	return (shell.rv);
}
