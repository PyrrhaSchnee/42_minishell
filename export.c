/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:21:25 by yanli             #+#    #+#             */
/*   Updated: 2025/07/17 14:43:23 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envp_input_checker(char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_envp_add(t_envp *envp, char *s)
{
	t_envp	*new_item;
	t_envp	*temp;

	if (ft_envp_existed(envp, s))
	{
		envp = ft_envp_modify(envp, s);
		return ;
	}
	temp = envp;
	while (temp->next)
		temp = temp->next;
	new_item = ft_new_envp(ft_copy_envp_name(s), ft_copy_envp_value(s));
	if (!new_item)
		return ;
	else
		temp->next = new_item;
	return ;
}

int	export_builtin_arg(char **argv, t_shell *shell)
{
	size_t			i;
	const t_envp	*head = shell->envp;
	int				rv;

	i = 1;
	rv = 0;
	while (argv[i])
	{
		if (!ft_envp_input_checker(argv[i]))
			ft_msg_invalid_envp(argv[i], &i, &rv);
		else
			ft_envp_add(shell->envp, argv[i++]);
	}
	shell->envp = (t_envp *)head;
	return (rv);
}

void	print_envp(t_shell *shell)
{
	t_envp	*curr;

	if (!shell->envp)
		return ;
	curr = shell->envp;
	while (curr)
	{
		if (curr->name && curr->name[0] && curr->value && (curr->value)[0])
			printf("declare -x %s=\"%s\"\n", curr->name, curr->value);
		else if (curr->name && curr->name[0]
			&& (!curr->value || ((curr->value) && !(curr->value)[0])))
			printf("declare -x %s\n", curr->name);
		else if (curr->name && curr->name[0])
			write(1, "\n", 1);
		curr = curr->next;
	}
}

t_envp	*ft_new_envp(char *name, char *value)
{
	t_envp	*new_envp;

	new_envp = ft_calloc(1, sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	new_envp->name = name;
	new_envp->value = value;
	new_envp->next = NULL;
	return (new_envp);
}
