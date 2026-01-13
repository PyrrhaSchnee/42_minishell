/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:20:04 by yanli             #+#    #+#             */
/*   Updated: 2025/07/07 14:38:35 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_rc_display(char **s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return ;
	while (s[i])
	{
		write(1, s[i], ft_strlen(s[i]));
		write(1, "\n", 1);
		i++;
	}
}

t_envp	*ft_sort_envp(t_shell *shell)
{
	t_envp	*ret;
	char	**temp;

	temp = envp_retro_convert(shell);
	ret = ft_copy_envp(temp);
	ft_free_pstr(&temp);
	ft_free_envp(&shell->envp);
	return (ret);
}

void	ft_msg_invalid_envp(char *s, size_t *i, int *rv)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	(*i)++;
	*rv = 1;
}

int	ft_envp_existed(t_envp *envp, char *s)
{
	t_envp		*curr;
	const char	*name = ft_copy_envp_name(s);
	int			r;

	curr = envp;
	r = 0;
	while (curr)
	{
		if (!ft_strcmp(curr->name, (char *)name))
		{
			r = 1;
			break ;
		}
		curr = curr->next;
	}
	free((char *)name);
	name = NULL;
	return (r);
}

t_envp	*ft_envp_modify(t_envp *envp, char *s)
{
	t_envp		*curr;
	const char	*name = ft_copy_envp_name(s);
	const char	*value = ft_copy_envp_value(s);

	curr = envp;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			free(curr->value);
			curr->value = (char *)value;
			break ;
		}
		curr = curr->next;
	}
	free((char *)name);
	return (envp);
}
