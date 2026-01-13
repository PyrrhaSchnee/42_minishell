/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:53:15 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 14:37:37 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_retro_convert(t_envp *env)
{
	char			**ret;
	const size_t	n = get_envp_rc_nbr(env);

	if (!n)
		return (NULL);
	ret = ft_calloc(n + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	envp_rc_filler(ret, env, n);
	return (ret);
}

t_envp	*ft_copy_env(char **envp)
{
	size_t	i;
	t_envp	*head;
	t_envp	*curr;
	t_envp	*next;

	if (!envp)
		return (NULL);
	i = 1;
	head = ft_new_envp(ft_copy_envp_name(envp[0]), ft_copy_envp_value(envp[0]));
	if (!head)
		return (NULL);
	curr = head;
	while (envp[i])
	{
		next = ft_new_envp(ft_copy_envp_name(envp[i]),
				ft_copy_envp_value(envp[i]));
		if (!next)
			return (ft_free_envp(&head), NULL);
		curr->next = next;
		curr = next;
		i++;
	}
	return (head);
}

/* env_builtin has been tested, it's good now. Don't modify it. */
int	env_builtin(char **args, t_envp *envp)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	while (envp)
	{
		if (envp->name && envp->value && envp->name[0])
			printf("%s=%s\n", envp->name, envp->value);
		envp = envp->next;
	}
	return (0);
}
