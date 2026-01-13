/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:06:42 by yanli             #+#    #+#             */
/*   Updated: 2025/07/13 19:22:39 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_envp_input_checker2(char *s)
{
	if (!s || !*s)
		return (0);
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	return (1);
}

static char	*ft_copy_envp_name2(char *s)
{
	size_t	i;
	char	*ret;
	size_t	k;

	i = 0;
	while (s[i] && (s[i] == '_' || ft_isalnum(s[i])))
		i++;
	k = 0;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		exit(EXIT_FAILURE);
	while (k < i)
	{
		ret[k] = s[k];
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

void	token_return_value(char *line, t_tk_param *p, int mode)
{
	if (p->state != STATE_IN_SINGLE && line[p->i] == '$' && line[p->i + 1]
		&& line[p->i + 1] == '?')
	{
		word_to_token(line, p);
		append_token(&p->token, new_token(ft_strdup("$?"), TK_RV, p->state));
		(p->i) += 2;
	}
	else
	{
		if (!mode)
			token_analyzer6(line, p);
		else
			token_analyzer5(line, p);
	}
}

void	token_analyzer6(char *line, t_tk_param *p)
{
	char	*name;

	if (line[p->i] == '$' && line[p->i + 1] && !ft_isspace(line[p->i + 1]))
	{
		word_to_token(line, p);
		if (ft_envp_input_checker2(&line[p->i + 1]))
		{
			name = ft_copy_envp_name2(&line[p->i + 1]);
			append_token(&p->token, new_token(name, TK_ENVP, p->state));
			(p->i) += (ft_strlen(name) + 1);
		}
		else
			jump_invalid_envp(&line[p->i + 1], p);
	}
	else
		p->word = ft_tokenjoin(p->word, line, p);
}
