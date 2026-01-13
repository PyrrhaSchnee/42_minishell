/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:38:50 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 15:47:10 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pwd_builtin4(t_pwd *cfg, t_shell *shell)
{
	ft_putendl_fd(cfg->pwd, 1);
	free(shell->pwd2);
	shell->pwd2 = ft_strdup(cfg->pwd);
	if (!shell->pwd2)
		ft_error2();
	free(cfg->pwd);
	return (1);
}

static int	pwd_builtin3(t_pwd *cfg, t_shell *shell)
{
	free(cfg->pwd);
	ft_putendl_fd(cfg->cwd, 1);
	free(shell->pwd2);
	shell->pwd2 = ft_strdup(cfg->cwd);
	if (!shell->pwd2)
		ft_error2();
	return (free(cfg->cwd), 0);
}

static int	pwd_builtin2(t_pwd *cfg)
{
	if (!stat(cfg->pwd, &cfg->st_env) && !stat(".", &cfg->st_dot)
		&& cfg->st_env.st_dev == cfg->st_dot.st_dev
		&& cfg->st_env.st_ino == cfg->st_dot.st_ino)
		return (ft_putendl_fd(cfg->pwd, 1), free(cfg->pwd), 0);
	return (1);
}

int	pwd_builtin(t_shell *shell)
{
	t_pwd	cfg;

	ft_memset(&cfg, 0, sizeof(t_pwd));
	cfg.pwd = envp_retrieve_value(shell->envp, ft_strdup("PWD"));
	if (cfg.pwd && !pwd_builtin2(&cfg))
		return (0);
	cfg.cwd = getcwd(NULL, 0);
	if (cfg.cwd)
		return (pwd_builtin3(&cfg, shell));
	if (cfg.pwd)
		return (pwd_builtin4(&cfg, shell));
	if (shell->pwd2)
	{
		ft_putendl_fd(shell->pwd2, 1);
		return (1);
	}
	return (ft_putstr_fd(ERROR20, 2), ft_putendl_fd(strerror(errno), 2), 1);
}
