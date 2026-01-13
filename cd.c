/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:32:20 by yanli             #+#    #+#             */
/*   Updated: 2025/07/19 22:15:39 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	logical_path(t_cd *cfg, char *s, t_shell *shell)
{
	ft_putstr_fd(ERROR19, 2);
	ft_putendl_fd(strerror(errno), 2);
	cfg->temp = ft_strjoin(cfg->oldpwd, "/");
	if (!cfg->temp)
		ft_error2();
	cfg->logical = ft_strjoin(cfg->temp, s);
	free(cfg->temp);
	if (!cfg->logical)
		ft_error2();
	cfg->argv[1] = ft_strjoin("PWD=", cfg->logical);
	if (!cfg->argv[1])
		ft_error2();
	free(shell->pwd2);
	shell->pwd2 = ft_strdup(cfg->logical);
	if (!shell->pwd2)
		ft_error2();
	free(cfg->logical);
	export_builtin(cfg->argv, shell);
	free(cfg->argv[1]);
	free(cfg->oldpwd);
}

static void	update_pwd(t_cd *cfg, char *s, t_shell *shell)
{
	cfg->oldpwd = envp_retrieve_value(shell->envp, ft_strdup("PWD"));
	if (!cfg->oldpwd && shell->pwd2)
		cfg->oldpwd = ft_strdup(shell->pwd2);
	if (!cfg->oldpwd)
		cfg->oldpwd = ft_empty();
	cfg->argv[0] = NULL;
	cfg->argv[2] = NULL;
	cfg->argv[1] = ft_strjoin("OLDPWD=", cfg->oldpwd);
	if (!cfg->argv[1])
		ft_error2();
	export_builtin(cfg->argv, shell);
	free(cfg->argv[1]);
	if (getcwd(cfg->cwd, PATH_MAX) == NULL)
		return (logical_path(cfg, s, shell));
	free(cfg->oldpwd);
	cfg->argv[1] = ft_strjoin("PWD=", cfg->cwd);
	if (!cfg->argv[1])
		ft_error2();
	export_builtin(cfg->argv, shell);
	free(cfg->argv[1]);
}

static int	cd_return_to_oldpwd(t_cd *cfg, t_shell *shell)
{
	cfg->oldpwd = envp_retrieve_value(shell->envp, ft_strdup("OLDPWD"));
	if (!cfg->oldpwd)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
	if (chdir(cfg->oldpwd))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cfg->oldpwd);
		free(cfg->oldpwd);
		return (1);
	}
	cfg->oldpwd2 = ft_strdup(cfg->oldpwd);
	ft_putendl_fd(cfg->oldpwd, 1);
	free(cfg->oldpwd);
	update_pwd(cfg, cfg->oldpwd2, shell);
	free(cfg->oldpwd2);
	return (0);
}

static int	cd_return_to_home(t_cd *cfg, t_shell *shell)
{
	cfg->home = envp_retrieve_value(shell->envp, ft_strdup("HOME"));
	if (!cfg->home)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (chdir(cfg->home))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cfg->home);
		free(cfg->home);
		return (1);
	}
	update_pwd(cfg, cfg->home, shell);
	free(cfg->home);
	return (0);
}

int	cd_builtin(char **args, t_shell *shell)
{
	t_cd	cfg;

	ft_memset(&cfg, 0, sizeof(t_cd));
	if (!args || !*args)
		return (cd_return_to_home(&cfg, shell));
	if (args && args[1])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (args && args[0] && args[0][0] == '-' && !args[0][1])
		return (cd_return_to_oldpwd(&cfg, shell));
	cfg.rv = chdir(*args);
	if (cfg.rv)
		return (perror(*args), 1);
	update_pwd(&cfg, *args, shell);
	return (0);
}
