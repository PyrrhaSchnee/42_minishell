/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_expansion3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:12:12 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 14:22:26 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_str4(t_eee *cfg, char *s, t_shell *shell)
{
	cfg->j = cfg->i + 1;
	while (s[cfg->j] && is_valid(s[cfg->j]))
		cfg->j++;
	cfg->name = ft_strldup(&s[cfg->i + 1], cfg->j - (cfg->i + 1));
	cfg->temp = envp_retrieve_value(shell->envp, cfg->name);
	if (!cfg->temp)
		cfg->temp = ft_empty();
	cfg->ret = append_free(cfg->ret, cfg->temp);
	free(cfg->temp);
	cfg->i = cfg->j;
}

static void	expand_str3(t_eee *cfg, t_shell *shell)
{
	cfg->temp = ft_itoa((int)shell->rv);
	cfg->ret = append_free(cfg->ret, cfg->temp);
	free(cfg->temp);
	cfg->i += 2;
}

void	expand_str2(t_eee *cfg, char *s, t_shell *shell)
{
	while (s[cfg->i])
	{
		if (s[cfg->i] == '$' && s[cfg->i + 1])
		{
			if (s[cfg->i + 1] == '?')
			{
				expand_str3(cfg, shell);
				continue ;
			}
			else if (is_start(s[cfg->i + 1]))
			{
				expand_str4(cfg, s, shell);
				continue ;
			}
		}
		cfg->ret = ft_charjoin(cfg->ret, s[cfg->i]);
		cfg->i++;
	}
}
