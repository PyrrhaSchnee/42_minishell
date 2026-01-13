/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:27 by yanli             #+#    #+#             */
/*   Updated: 2025/07/10 18:49:22 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_file_open_test(char **s, t_redir_type t)
{
	int	fd;

	fd = 0;
	if (!s || !*s)
		return (0);
	if (t == REDIR_IN)
		fd = open(*s, O_RDONLY);
	else if (t == REDIR_OUT)
		fd = open(*s, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	else if (t == REDIR_APPEND)
		fd = open(*s, O_APPEND | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(*s);
		return (0);
	}
	close_fd(&fd);
	return (1);
}

void	ft_free_redir_filename(char **s)
{
	if (!s || !*s)
		return ;
	free(*s);
	*s = NULL;
}

/*	redir_filename_join :
	concatenate redir filenames.
*/
char	*redir_filename_join(t_token **token, t_exec *e, char *name)
{
	t_token	*t;
	char	*temp;

	if (!token || !*token || !e || !name)
		return (name);
	t = *token;
	while (t && t->type == TK_WORD && t->value)
	{
		temp = ft_strjoin(name, t->value);
		if (!temp)
			return (name);
		ft_free_str(&name);
		name = temp;
		temp = NULL;
		t = t->next;
	}
	return (name);
}

char	*get_allow_bin(char *path, char *command)
{
	t_bin	cfg;

	ft_memset(&cfg, 0, sizeof(t_bin));
	cfg.split_path = ft_split(path + 5, ':');
	if (!cfg.split_path)
		return (NULL);
	if (!get_allow_bin2(&cfg, command))
	{
		ft_free_pstr(&cfg.split_path);
		free(cfg.path_bin);
		cfg.path_bin = NULL;
		free(cfg.path_command);
		cfg.path_command = NULL;
		return (NULL);
	}
	ft_free_pstr(&cfg.split_path);
	free(cfg.path_bin);
	return (cfg.path_command);
}
