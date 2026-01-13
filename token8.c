/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:41:37 by yanli             #+#    #+#             */
/*   Updated: 2025/07/09 13:57:50 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_to_token(char *line, t_tk_param *p)
{
	if (!p->word)
		return ;
	(void)line;
	append_token(&p->token, new_token(p->word, TK_WORD, p->state));
	p->word = NULL;
}

void	jump_space(char *line, t_tk_param *p)
{
	size_t	k;

	k = 0;
	if (p->word)
		append_token(&p->token, new_token(p->word, TK_WORD, p->state));
	p->word = NULL;
	while (ft_isspace(line[p->i + k]))
		k++;
	(p->i) += k;
	if (line[p->i])
		insert_token_separator(p);
}

char	*ft_charjoin(char *s, char c)
{
	char	*ret;
	size_t	len;

	if (!s)
	{
		ret = ft_calloc(2, sizeof(char));
		if (!ret)
			return (NULL);
		ret[0] = c;
		ret[1] = '\0';
		return (ret);
	}
	len = ft_strlen(s);
	ret = ft_calloc(len + 2, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	ret[len] = c;
	ret[len + 1] = '\0';
	free(s);
	return (ret);
}
