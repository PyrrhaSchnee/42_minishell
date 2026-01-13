/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:05:37 by yanli             #+#    #+#             */
/*   Updated: 2025/07/19 22:41:58 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int sig)
{
	g_signal = sig;
	rl_done = 1;
	if (sig == SIGINT)
	{
		write(1, "\nminishell$ ", 12);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static int	heredoc_delimiter_check(const char *s, t_parse_state quoted)
{
	if (!s)
		return (0);
	if (quoted != STATE_IN_SINGLE && quoted != STATE_IN_DOUBLE && (*s == '|'
			|| *s == '&' || *s == ';' || *s == '(' || *s == ')' || *s == '<'
			|| *s == '>' || *s == '\n'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, s, 1);
		ft_putendl_fd("'", 2);
		return (0);
	}
	return (1);
}

void	set_heredoc_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = signal_heredoc;
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		perror("minishell: heredoc");
		exit(1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL))
	{
		perror("minishell: heredoc");
		exit(1);
	}
}

static int	request_heredoc_input(t_token **token, t_shell *shell)
{
	pid_t	pid;

	if (!(*token)->next || !heredoc_delimiter_check((*token)->next->value,
			(*token)->next->quoted))
	{
		shell->rv = 2;
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: heredoc");
		shell->rv = 1;
		return (0);
	}
	if (!pid)
		child_acquisition_heredoc(token, shell);
	if (!parent_acquisition_heredoc(shell, pid))
		return (0);
	return (1);
}

int	handle_heredoc(t_token *token, t_shell *shell)
{
	t_token	*curr;

	curr = token;
	if (!curr)
		return (0);
	while (curr)
	{
		if (curr->type == TK_HEREDOC)
		{
			if (!request_heredoc_input(&curr, shell))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}
