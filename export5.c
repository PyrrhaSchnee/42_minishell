/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:16:53 by yanli             #+#    #+#             */
/*   Updated: 2025/07/16 18:24:03 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*eev_loop(const char *val, t_eev *cfg, t_shell *shell)
{
	while (val[cfg->i])
	{
		if (val[cfg->i] == '$' && (ft_isalpha(val[cfg->i + 1]) || val[cfg->i
					+ 1] == '_'))
		{
			cfg->j = cfg->i + 1;
			while (val[cfg->j] && (ft_isalnum(val[cfg->j])
					|| val[cfg->j] == '_'))
				(cfg->j)++;
			cfg->name = ft_strldup((char *)&val[cfg->i + 1], cfg->j - cfg->i
					- 1);
			cfg->v = envp_retrieve_value(shell->envp, cfg->name);
			if (!cfg->v)
				cfg->v = ft_strdup("");
			cfg->temp = ft_strjoin(cfg->ret, cfg->v);
			free(cfg->ret);
			free(cfg->v);
			cfg->ret = cfg->temp;
			cfg->i = cfg->j;
			continue ;
		}
		else
			cfg->ret = ft_charjoin(cfg->ret, val[cfg->i++]);
	}
	return (cfg->ret);
}

char	*expand_export_value(const char *val, t_shell *shell)
{
	t_eev	cfg;

	ft_memset(&cfg, 0, sizeof(t_eev));
	cfg.ret = ft_calloc(1, sizeof(char));
	if (!cfg.ret)
		return (NULL);
	return (eev_loop(val, &cfg, shell));
}

char	*expand_export_argument(char *arg, t_shell *shell)
{
	char	*eq;
	char	*name;
	char	*value;
	char	*ret;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (ft_strdup(arg));
	name = ft_strldup(arg, (size_t)(eq - arg + 1));
	value = expand_export_value(eq + 1, shell);
	if (!value)
		return (free(name), NULL);
	ret = ft_strjoin(name, value);
	free(name);
	free(value);
	return (ret);
}
