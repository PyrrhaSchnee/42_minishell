/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:51:07 by yanli             #+#    #+#             */
/*   Updated: 2025/07/09 09:42:31 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_next_token_len(char *s, t_parse_state state)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (state == STATE_GENERAL)
	{
		while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '"'
			&& s[i] != '|' && s[i] != '>' && s[i] != '\'')
			i++;
	}
	else if (state == STATE_IN_DOUBLE)
	{
		while (s[i] && s[i] != '"' && s[i] != '$')
			i++;
	}
	else if (state == STATE_IN_SINGLE)
	{
		while (s[i] && s[i] != '\'')
			i++;
	}
	return (i);
}

static char	*ft_case1(char *line, size_t ntl, t_tk_param *p)
{
	char	*r;
	size_t	k;

	r = ft_calloc(sizeof(char), ntl + 1);
	if (!r)
		return (NULL);
	k = 0;
	while (k < ntl)
	{
		r[k] = line[p->i + k];
		k++;
	}
	r[k] = '\0';
	p->i += ntl;
	return (r);
}

static void	ft_tokenjoin2(char *line, t_tkjoin *cfg, t_tk_param *p)
{
	cfg->k = 0;
	while (cfg->k < cfg->ntl)
	{
		cfg->ret[cfg->slen + cfg->k] = line[p->i + cfg->k];
		(cfg->k)++;
	}
	cfg->ret[cfg->slen + cfg->k] = '\0';
	p->i += cfg->ntl;
}

char	*ft_tokenjoin(char *s, char *line, t_tk_param *p)
{
	t_tkjoin	cfg;

	ft_memset(&cfg, 0, sizeof(t_tkjoin));
	cfg.ntl = ft_next_token_len(&line[p->i], p->state);
	cfg.slen = ft_strlen(s);
	if (!cfg.ntl)
	{
		(p->i)++;
		return (s);
	}
	if (!s)
		return (ft_case1(line, cfg.ntl, p));
	cfg.ret = ft_calloc(sizeof(char), cfg.slen + cfg.ntl + 1);
	if (!cfg.ret)
		return (NULL);
	ft_strlcpy(cfg.ret, s, cfg.slen + 1);
	ft_tokenjoin2(line, &cfg, p);
	free(s);
	s = NULL;
	return (cfg.ret);
}
