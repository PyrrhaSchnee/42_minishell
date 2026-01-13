/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:42:02 by yanli             #+#    #+#             */
/*   Updated: 2025/07/13 19:20:24 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_sanitizer(char *line)
{
	t_parse_state	state;
	size_t			i;

	i = 0;
	state = STATE_GENERAL;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' && state == STATE_GENERAL)
			state = STATE_IN_SINGLE;
		else if (line[i] == '\'' && state == STATE_IN_SINGLE)
			state = STATE_GENERAL;
		else if (line[i] == '"' && state == STATE_GENERAL)
			state = STATE_IN_DOUBLE;
		else if (line[i] == '"' && state == STATE_IN_DOUBLE)
			state = STATE_GENERAL;
		i++;
	}
	if (state == STATE_IN_SINGLE)
		ft_putstr_fd(ERROR4, 2);
	if (state == STATE_IN_DOUBLE)
		ft_putstr_fd(ERROR5, 2);
	return (state == STATE_GENERAL);
}

int	ft_envp_quoted_checker(char *s)
{
	if (!s || !s[0])
		return (0);
	if (s[0] && !ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	return (1);
}

size_t	quoted_envp_length(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

char	*ft_copy_quoted_envp_name(char *s)
{
	size_t	len;
	char	*ret;
	size_t	i;

	i = 0;
	len = 0;
	while (s[len] && (s[len] == '_' || ft_isalnum(s[len])))
		len++;
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		exit(EXIT_FAILURE);
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	token_analyzer5(char *line, t_tk_param *p)
{
	char	*name;

	if (p->state != STATE_IN_SINGLE && line[p->i] == '$' && line[p->i + 1]
		&& ft_envp_quoted_checker(&line[p->i + 1]))
	{
		word_to_token(line, p);
		name = ft_copy_quoted_envp_name(&line[p->i + 1]);
		append_token(&p->token, new_token(name, TK_ENVP, p->state));
		(p->i) += ft_strlen(name) + 1;
	}
	else
	{
		word_to_token(line, p);
		if (line[p->i] == '$')
		{
			p->word = ft_charjoin(p->word, '$');
			(p->i)++;
		}
		else
			p->word = ft_tokenjoin(p->word, line, p);
	}
}
