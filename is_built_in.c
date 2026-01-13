/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:30:13 by nlienard          #+#    #+#             */
/*   Updated: 2025/07/13 15:44:34 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_args(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (2);
	if (!ft_strcmp(cmd, "exit"))
		return (3);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

static int	run_builtin2(char **cmd, t_shell *shell, t_exec *exec)
{
	int	ret;

	if (!ft_strcmp(cmd[0], "unset"))
	{
		ret = unset_builtin(cmd, shell);
		if (shell->envp2)
			ft_free_pstr(&shell->envp2);
		shell->envp2 = envp_retro_convert(shell);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		ret = env_builtin(cmd, shell->envp);
	else if (!ft_strcmp(cmd[0], "exit"))
		ret = exit_builtin(cmd, shell, 1, exec);
	else
		ret = 1;
	return (ret);
}

int	run_builtin(char **cmd, t_shell *shell, t_exec *exec)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd[0], "cd"))
		ret = cd_builtin(&cmd[1], shell);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ret = pwd_builtin(shell);
	else if (!ft_strcmp(cmd[0], "echo"))
		ret = echo_builtin(count_args(cmd), cmd);
	else if (!ft_strcmp(cmd[0], "export"))
	{
		ret = export_builtin(cmd, shell);
		if (shell->envp2)
			ft_free_pstr(&shell->envp2);
		shell->envp2 = envp_retro_convert(shell);
	}
	else
		ret = run_builtin2(cmd, shell, exec);
	return (ret);
}
