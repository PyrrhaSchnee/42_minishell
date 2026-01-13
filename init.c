/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:41:53 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 21:40:53 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*ft_empty_envp(void)
{
	t_envp	*ret;

	ret = ft_calloc(1, sizeof(t_envp));
	if (!ret)
		exit(1);
	ret->next = NULL;
	ret->name = ft_empty();
	ret->value = ft_empty();
	return (ret);
}

static char	**ft_empty_envp2(void)
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		exit(1);
	ret[1] = NULL;
	ret[0] = ft_empty();
	return (ret);
}

static void	envp_init(t_shell *shell, char **envp)
{
	if (!envp || !*envp || !**envp)
	{
		shell->env = ft_empty_envp();
		shell->envp = ft_empty_envp();
		shell->envp2 = ft_empty_envp2();
	}
	else
	{
		shell->env = ft_copy_env(envp);
		shell->envp = ft_copy_envp(envp);
		shell->envp2 = envp_retro_convert(shell);
	}
	if (!shell->envp || !shell->envp2)
		ft_error4();
}

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	set_signal_handler();
	envp_init(shell, envp);
	unlink(HEREDOC_TEMPFILE);
	unlink(HEREDOC_TEMPFILE2);
	shell->pwd2 = envp_retrieve_value(shell->envp, ft_strdup("PWD"));
	if (!shell->pwd2)
		shell->pwd2 = getcwd(NULL, 0);
	if (!shell->pwd2)
		shell->pwd2 = ft_empty();
}
