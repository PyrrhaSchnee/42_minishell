/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:19:18 by yanli             #+#    #+#             */
/*   Updated: 2025/07/06 01:39:00 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_envp_rc_nbr(t_envp *envp)
{
	size_t	i;
	t_envp	*temp;

	i = 0;
	if (!envp)
		return (0);
	temp = envp;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	*envp_rc_join(char *s1, char *s2)
{
	const size_t	s1len = ft_strlen(s1);
	const size_t	s2len = ft_strlen(s2);
	char			*ret;
	size_t			i;
	size_t			k;

	ret = ft_calloc(s1len + s2len + 2, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[k])
		ret[i++] = s1[k++];
	ret[i++] = '=';
	k = 0;
	while (s2[k])
		ret[i++] = s2[k++];
	ret[i] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

char	*envp_rc_merge(t_envp *envp, size_t i)
{
	size_t	k;
	t_envp	*temp;

	k = 0;
	temp = envp;
	while (k < i)
	{
		k++;
		temp = temp->next;
	}
	return (envp_rc_join(ft_strdup(temp->name), ft_strdup(temp->value)));
}

void	envp_rc_filler(char **ret, t_envp *envp, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ret[i] = envp_rc_merge(envp, i);
		if (!ret[i])
			return (ft_free_pstr(&ret));
		i++;
	}
	ret[i] = NULL;
}

char	**envp_retro_convert(t_shell *shell)
{
	char			**ret;
	const size_t	n = get_envp_rc_nbr(shell->envp);

	if (!n)
		return (NULL);
	ret = ft_calloc(n + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	envp_rc_filler(ret, shell->envp, n);
	return (ret);
}
