/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:18:47 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 15:39:43 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_after_exec(char **line, t_shell *shell)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	ft_free_pids(&shell->pids);
	free_token(&shell->token);
	ft_memset(&shell->p, 0, sizeof(t_tk_param));
}

void	ft_clean_all(t_shell *shell)
{
	rl_clear_history();
	ft_free_envp(&shell->envp);
	ft_free_pstr(&shell->envp2);
	ft_free_envp(&shell->env);
	ft_free_str(&shell->pwd2);
	clean_after_exec(NULL, shell);
}
