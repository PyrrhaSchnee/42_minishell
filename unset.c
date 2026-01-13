/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:39:04 by yanli             #+#    #+#             */
/*   Updated: 2025/07/04 11:49:39 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*ft_envp_delete(t_envp *envp, char *s)
{
	t_envp	*head;
	t_envp	*prev;

	head = envp;
	prev = NULL;
	while (envp)
	{
		if (!ft_strcmp(envp->name, s))
		{
			if (!prev)
				head = envp->next;
			else
				prev->next = envp->next;
			free(envp->name);
			free(envp->value);
			free(envp);
			return (head);
		}
		prev = envp;
		envp = envp->next;
	}
	return (head);
}

int	unset_builtin(char **args, t_shell *shell)
{
	size_t	i;
	char	*name;

	i = 0;
	if (!args || !args[0] || !args[0][0] || !shell)
		return (0);
	while (args[i])
	{
		name = ft_copy_envp_name(args[i]);
		if (ft_envp_existed(shell->envp, name))
			shell->envp = ft_envp_delete(shell->envp, name);
		i++;
		free(name);
	}
	return (0);
}
