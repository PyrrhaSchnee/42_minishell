/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:18:41 by yanli             #+#    #+#             */
/*   Updated: 2025/07/09 13:55:34 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy_envp_name(char *s)
{
	char	*ret;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] && s[i] != '=')
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (k < i)
	{
		ret[k] = s[k];
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

char	*ft_copy_envp_value(char *s)
{
	char			*ret;
	size_t			i;
	size_t			k;
	const size_t	slen = ft_strlen(s);

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
		i++;
	else
		return (NULL);
	ret = ft_calloc(slen - i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	k = 0;
	while (s[i])
		ret[k++] = s[i++];
	ret[k] = '\0';
	return (ret);
}

void	ft_free_envp(t_envp **envp)
{
	t_envp	*next;

	if (!envp || !*envp)
		return ;
	while (*envp)
	{
		if ((*envp)->name)
			free((*envp)->name);
		(*envp)->name = NULL;
		if ((*envp)->value)
			free((*envp)->value);
		(*envp)->value = NULL;
		next = (*envp)->next;
		free(*envp);
		*envp = next;
	}
}

t_envp	*ft_copy_envp(char **envp)
{
	size_t	i;
	t_envp	*head;
	t_envp	*curr;
	t_envp	*next;
	char	**s;

	s = ft_sort_pstr(envp);
	if (!s)
		return (NULL);
	i = 1;
	head = ft_new_envp(ft_copy_envp_name(s[0]), ft_copy_envp_value(s[0]));
	if (!head)
		return (NULL);
	curr = head;
	while (s[i])
	{
		next = ft_new_envp(ft_copy_envp_name(s[i]), ft_copy_envp_value(s[i]));
		if (!next)
			return (ft_free_envp(&head), NULL);
		curr->next = next;
		curr = next;
		i++;
	}
	ft_free_pstr(&s);
	return (head);
}

int	export_builtin(char **argv, t_shell *shell)
{
	int	r;

	r = 0;
	if (!shell->envp)
		return (1);
	if (!argv[1])
		return (print_envp(shell), 0);
	else
	{
		r += export_builtin_arg(argv, shell);
		shell->envp = ft_sort_envp(shell);
	}
	if (r > 0)
		return (1);
	return (0);
}
