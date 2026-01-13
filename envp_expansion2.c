/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_expansion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:51:41 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 15:17:16 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*append_free(char *dst, char *src)
{
	char	*ret;

	ret = ft_strjoin(dst, src);
	free(dst);
	return (ret);
}

char	*expand_str(char *s, t_shell *shell)
{
	t_eee	cfg;

	ft_memset(&cfg, 0, sizeof(t_eee));
	if (!s)
		return (NULL);
	cfg.ret = ft_empty();
	cfg.i = 0;
	expand_str2(&cfg, s, shell);
	return (cfg.ret);
}

void	expand_embedded_envp(t_token *token, t_shell *shell)
{
	char	*new;

	if (!token || !shell)
		return ;
	while (token)
	{
		if (token->type == TK_WORD && token->quoted != STATE_IN_SINGLE)
		{
			new = expand_str(token->value, shell);
			free(token->value);
			token->value = new;
			if (!token->value)
				token->value = ft_strdup("");
		}
		token = token->next;
	}
}
