/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:51:50 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 09:04:57 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

static void	select_clean(t_shell *shell, t_exec *e, char ***args, int mode)
{
	rl_clear_history();
	if (mode == 1)
	{
		ft_free_pstr(args);
		clean_exec(e);
		ft_clean_all(shell);
		close_all_fd();
	}
	if (mode == 2)
	{
		clean_exec(e);
		ft_clean_all(shell);
		close_all_fd();
	}
}

static int	ft_isnum(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_builtin2(char ***args, t_shell *shell, t_exec *e)
{
	int	ec;

	if (!ft_isnum((*args)[1]) || exit_overflow((*args)[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n",
			STDERR_FILENO);
		if (shell->nbr_child == 1)
			select_clean(shell, e, args, 1);
		else
			select_clean(shell, e, args, 2);
		exit(2);
	}
	else if (ft_isnum((*args)[1]) && (*args)[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->rv = 1;
		return (1);
	}
	ec = ft_atoi((*args)[1]);
	if (shell->nbr_child == 1)
		select_clean(shell, e, args, 1);
	else
		select_clean(shell, e, args, 2);
	exit((unsigned char)ec);
}

int	exit_builtin(char **args, t_shell *shell, int i, t_exec *exec)
{
	unsigned char	rs;

	if (i == 1)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args && args[1])
		return (exit_builtin2(&args, shell, exec));
	rs = shell->rv;
	if (shell->nbr_child == 1)
		select_clean(shell, exec, &args, 1);
	else
		select_clean(shell, exec, &args, 2);
	exit(rs);
}
