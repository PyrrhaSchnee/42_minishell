/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:27:18 by yanli             #+#    #+#             */
/*   Updated: 2025/07/09 12:30:29 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envp_retrieve_value(t_envp *envp, char *s)
{
	char	*ret;

	ret = NULL;
	if (!envp || !s)
		return (NULL);
	while (envp)
	{
		if (!ft_strcmp(envp->name, s))
		{
			if (envp->value)
			{
				ret = ft_strdup(envp->value);
				break ;
			}
			else
				break ;
		}
		envp = envp->next;
	}
	free(s);
	return (ret);
}

char	*envp_expansion(t_shell *shell, t_token *token)
{
	char	*name;

	if (!token || !shell)
		return (NULL);
	name = get_single_word(token->value);
	if (!ft_envp_existed(shell->envp, name))
	{
		free(name);
		return (NULL);
	}
	return (envp_retrieve_value(shell->envp, name));
}

static void	envp_expansion2(char **expanded, t_shell *shell, t_token *token)
{
	if (!expanded)
		return ;
	*expanded = envp_expansion(shell, token);
	free(token->value);
	if (*expanded)
		token->value = *expanded;
	else
		token->value = ft_strdup("");
	if (!token->value)
		exit(EXIT_FAILURE);
}

void	expand_envp_token(t_token *token, t_shell *shell)
{
	char	*expanded;
	int		disable;

	disable = 0;
	if (!token || !shell)
		return ;
	while (token)
	{
		if (token->type == TK_BUILTIN && !ft_strcmp(token->value, "export"))
			disable = 1;
		else if (token->type == TK_PIPE)
			disable = 0;
		if (token->type == TK_ENVP)
		{
			if (!disable)
				envp_expansion2(&expanded, shell, token);
			token->type = TK_WORD;
		}
		token = token->next;
	}
}
