/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanli <yanli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:40:11 by yanli             #+#    #+#             */
/*   Updated: 2025/07/19 22:40:41 by yanli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif /* _DEFAULT_SOURCE */

# ifndef HEREDOC_TEMPFILE
#  define HEREDOC_TEMPFILE "/tmp/heredoctemp.txt"
#  define HEREDOC_TEMPFILE2 "/tmp/heredoctemp2.txt"
# endif /* HEREDOC_TEMPFILE */

# ifndef SPACE_PLACEHOLDER
#  define SPACE_PLACEHOLDER '\x01'
# endif /* SPACE_PLACEHOLDER */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include "msg.h"
# include "libft/libft.h"

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_DELIMITER,
	TK_BUILTIN,
	TK_ENVP,
	TK_SPACE,
	TK_RV,
	TK_EOF
}				t_token_type;

typedef enum e_parse_state
{
	STATE_GENERAL,
	STATE_IN_SINGLE,
	STATE_IN_DOUBLE,
}				t_parse_state;

typedef struct s_token
{
	char			*value;
	t_parse_state	quoted;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_exec
{
	int		fd[2];
	t_token	*token;
	int		builtin;
	size_t	id;
	int		fd_in;
	int		fd_out;
	int		prev;
	size_t	i;
	size_t	is_append;
	size_t	is_heredoc;
	char	*infile;
	char	*outfile;
	char	*eof;
	char	*bin;
	char	empty[1];
	char	**env;
	char	*pathname;
	char	**command;
	char	**tab_command;
}				t_exec;

typedef struct s_envp
{
	char			*name;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_tk_param
{
	t_parse_state	state;
	t_token			*token;
	t_token_type	type;
	size_t			i;
	char			*delimiter;
	char			*word;
}				t_tk_param;

/* rv = return value (0 - 255) */
typedef struct s_shell
{
	t_envp			*envp;
	char			**envp2;
	t_envp			*env;
	unsigned char	rv;
	pid_t			*pids;
	size_t			nbr_child;
	t_token			*token;
	t_tk_param		p;
	char			*pwd2;
}				t_shell;

typedef struct s_bin
{
	size_t	i;
	char	**split_path;
	char	*path_bin;
	char	*path_command;
	int		save_in;
	int		save_out;
}				t_bin;

typedef struct s_heredoc
{
	char	*line;
	char	*temp;
	char	*joined;
	int		mode;
}				t_heredoc;

typedef struct s_tkjoin
{
	size_t	ntl;
	size_t	slen;
	char	*line;
	char	*ret;
	size_t	k;
}				t_tkjoin;

typedef enum s_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND
}			t_redir_type;

typedef struct s_cmd_bi
{
	char	**cmd;
	int		save_in;
	int		save_out;
}				t_cmd_bi;

typedef struct s_notty
{
	char	*line;
	char	*temp;
	ssize_t	r;
	size_t	i;
	char	buf[1];
}				t_notty;

typedef struct s_heredoc_envp
{
	int		fd1;
	int		fd2;
	size_t	totline;
	size_t	currline;
	char	*line;
	char	*expanded;
	char	*temp;
}				t_heredoc_envp;

typedef struct s_cd
{
	int		rv;
	char	*home;
	char	*argv[3];
	char	*oldpwd;
	char	*oldpwd2;
	char	*temp;
	char	*logical;
	char	cwd[PATH_MAX];
}				t_cd;

typedef struct s_pwd
{
	char		*pwd;
	char		*cwd;
	struct stat	st_env;
	struct stat	st_dot;
}				t_pwd;

/* cfg for get_heredoc_delimiter() */
typedef struct s_ghd
{
	char	*delim;
	int		quoted;
	t_token	*curr;
}				t_ghd;

/* cfg for expand_embedded_envp() */
typedef struct s_eee
{
	size_t	i;
	size_t	j;
	char	*ret;
	char	*name;
	char	*temp;
}				t_eee;

/* cfg for build_delimiter_string() */
typedef struct s_bds
{
	t_token	*curr;
	char	*ret;
	char	*temp;
	char	*word;
}				t_bds;

/* clean_all.c */
void	ft_clean_all(t_shell *shell);
void	clean_after_exec(char **line, t_shell *shell);

/* init.c */
void	init_shell(t_shell *shell, char **enpv);
void	print_errno(const char *prefix, const char *path);

/* ft_strsecdup.c */
char	*ft_strsecdup(char *s, size_t begin, size_t end);

/* token.c */
void	free_token(t_token **token);
t_token	*new_token(char *value, t_token_type type, t_parse_state quoted);
void	append_token(t_token **head, t_token *new_token);
int		tokenizer(char *line, t_shell *shell);
void	expand_return_value(t_token *token, t_shell *shell);

/* token2.c */
void	token_analyzer1(char *line, t_tk_param *p);
void	token_analyzer1a(char *line, t_tk_param *p);
void	token_analyzer2(char *line, t_tk_param *p);
void	token_analyzer3(char *line, t_tk_param *p);

/* token3.c */
int		ft_isbuiltin(char *s);
int		ft_isbuiltin2(char *s);
t_token	*mark_builtin(t_token *token);

/* token4.c */
int		quote_sanitizer(char *line);
int		ft_envp_quoted_checker(char *s);
size_t	quoted_envp_length(char *s);
char	*ft_copy_quoted_envp_name(char *s);
void	token_analyzer5(char *line, t_tk_param *p);

/* token5.c */
char	*ft_tokenjoin(char *s, char *line, t_tk_param *p);

/* token6.c */
void	jump_invalid_envp(char *s, t_tk_param *p);
void	insert_token_separator(t_tk_param *p);

/* token7.c */
void	token_return_value(char *line, t_tk_param *p, int mode);
void	token_analyzer6(char *line, t_tk_param *p);

/* token8.c */
void	jump_space(char *line, t_tk_param *p);
void	word_to_token(char *line, t_tk_param *p);
char	*ft_charjoin(char *s, char c);

/* split_spaceholder.c */
char	**split_placeholder(char *s);

/* redir_sanitizer.c */
int		redir_sanitizer(t_tk_param *p);

/* redir_sanitizer2.c */
int		pipe_sanitizer(t_token *t);
void	token_nullification(t_shell *shell);

/* is_built_in.c */
size_t	count_args(char **s);
int		is_builtin_cmd(char *cmd);
int		run_builtin(char **cmd, t_shell *shell, t_exec *exec);

/* signal.c */
void	set_signal_handler(void);
void	set_child_signal(void);

/* error.c */
void	ft_error1(void);
void	ft_error2(void);
void	ft_error3(char **copy, size_t i);
void	ft_error4(void);

/* pwd.c, cd.c, env.c, echo.c, exit.c */
int		pwd_builtin(t_shell *shell);
int		cd_builtin(char **args, t_shell *shell);
int		echo_builtin(size_t argc, char **s);
int		exit_builtin(char **args, t_shell *shell, int i, t_exec *exec);
int		env_builtin(char **args, t_envp *envp);
char	**env_retro_convert(t_envp *env);
t_envp	*ft_copy_env(char **envp);
void	close_all_fd(void);

/* export.c */
t_envp	*ft_new_envp(char *name, char *value);
void	print_envp(t_shell *shell);
int		export_builtin_arg(char **argv, t_shell *shell);
void	ft_envp_add(t_envp *envp, char *s);
int		ft_envp_input_checker(char *s);

/* export2.c */
char	*ft_copy_envp_name(char *s);
char	*ft_copy_envp_value(char *s);
void	ft_free_envp(t_envp **envp);
t_envp	*ft_copy_envp(char **envp);
int		export_builtin(char **argv, t_shell *shell);

/* export3.c */
char	**envp_retro_convert(t_shell *shell);
void	envp_rc_filler(char **ret, t_envp *envp, const size_t n);
char	*envp_rc_merge(t_envp *envp, size_t i);
char	*envp_rc_join(char *s1, char *s2);
size_t	get_envp_rc_nbr(t_envp *envp);

/* export4.c */
void	envp_rc_display(char **s);
t_envp	*ft_sort_envp(t_shell *shell);
void	ft_msg_invalid_envp(char *s, size_t *i, int *rv);
t_envp	*ft_envp_modify(t_envp *envp, char *s);
int		ft_envp_existed(t_envp *envp, char *s);

/* unset.c */
int		unset_builtin(char **args, t_shell *shell);

/* utils.c */
size_t	ft_nbr_sec(char **s);
void	ft_free_pstr(char ***s);
char	**ft_sort_pstr(char **s);
char	*get_single_word(char *s);
char	*ft_strldup(char *s, size_t len);

/* exec.c */
int		check_and_exec(t_shell *shell);
int		get_allow_bin2(t_bin *cfg, char *command);

/* exec2.c */
int		find_infile_redir_filename(t_token **token, t_exec *exec);
void	ft_free_redir_filename(char **s);
int		redir_file_open_test(char **s, t_redir_type t);
int		find_outfile_redir_filename(t_token **token,
			t_exec *exec, t_redir_type rt);
char	*get_allow_bin(char *path, char *command);
char	*redir_filename_join(t_token **token, t_exec *e, char *name);

/* envp_expansion.c */
void	expand_envp_token(t_token *token, t_shell *shell);
char	*envp_expansion(t_shell *shell, t_token *token);
char	*envp_retrieve_value(t_envp *envp, char *s);

/* envp_expansion2.c */
void	expand_embedded_envp(t_token *token, t_shell *shell);
int		is_start(char c);
int		is_valid(char c);
char	*append_free(char *dst, char *src);
char	*expand_str(char *s, t_shell *shell);

/* envp_expansion3.c */
void	expand_str2(t_eee *cfg, char *s, t_shell *shell);

/* error_exec.c */
void	handle_no_exec_bin(t_exec *exec, t_shell *shell);

/* heredoc.c */
int		handle_heredoc(t_token *token, t_shell *shell);
void	signal_heredoc(int sig);
int		parse_cmd_redirections(t_exec *exec, t_shell *shell, size_t id);

/* heredoc2.c */
void	set_heredoc_signal(void);
int		read_heredoc(t_shell *shell, t_token **token);

/* heredoc3.c */
int		get_heredoc_delimiter(t_token **token, t_heredoc *doc);
int		print_delimiter(t_token **token);

/* heredoc4.c */
int		heredoc_envp_expansion(t_shell *shell, t_heredoc *doc);
char	*replace_eof_by_newline(char *s);

/* heredoc5.c*/
void	heredoc_try_expansion(t_shell *shell, t_heredoc_envp *cfg);
int		need_expansion(char *s);
void	build_delimiter_string2(t_bds *cfg, int *quoted);
int		parent_acquisition_heredoc(t_shell *shell, pid_t pid);
void	child_acquisition_heredoc(t_token **token, t_shell *shell);

/* exec_command1.c */
int		exec_command(t_exec *exec, t_shell *shell);
void	child_pipe_handle_builtin(t_exec *exec, t_shell *shell);
int		exec_command2(t_exec *exec, t_shell *shell);

/* exec_command2.c */
void	get_heredoc(t_exec *exec);
void	open_infile(t_exec *exec, t_shell *shell);
void	open_outfile(t_exec *exec, t_shell *shell);
void	exec_child_command(t_exec *exec, t_shell *shell);

/* exec_command3.c*/
int		handle_fork(t_shell *shell, t_exec *exec);
int		is_absolute_path(t_exec *exec, t_shell *shell);
void	child_pipe(t_exec *exec, t_shell *shell, const size_t id);
void	child_pipe2(t_exec *exec, t_shell *shell);

/* exec_command4.c */
int		exec_command3(t_cmd_bi *cfg, t_exec *exec, t_shell *shell);
void	prepare_command_and_pathname(t_exec *exec, t_shell *shell);
void	clean_exec(t_exec *e);
int		set_child_fd(t_exec *e, t_shell *shell, const size_t id);

/* exec_command6.c */
void	create_file_then_quit(t_exec *exec, t_shell *shell);

/* put_in_tab.c */
char	**put_in_tab(t_token *token);
void	append_with_placeholder(char *dst, char *src, size_t size,
			t_parse_state quoted);

/* put_in_tab2.c */
char	*fill_tab(t_token **token);
size_t	shortcut_condition(t_token_type elem);

/* utils2.c */
size_t	ft_strlen_total(t_token *token);
size_t	count_total_element(t_token *token);
char	*get_path(char **envp);
char	*ft_empty(void);
void	ft_free_pids(pid_t **s);

/* utils3.c */
int		is_fd_dir(t_token *t);

/* utils4.c */
void	ft_free_str(char **s);
void	close_fd_prev(int *fd);
void	close_fd(int *fd);
int		exit_overflow(char *s);

/* signal2.c */
void	print_child_sigmsg(int *status);

/* exec_command5.c */
void	builtin_fd_redir(t_cmd_bi *cfg, t_exec *e, t_shell *shell);
void	builtin_fd_reset(t_cmd_bi *cfg);
void	check_if_is_directory(t_exec *e, t_shell *shell);
void	select_close_fd(const size_t id, const size_t nbr_child);

/* ft_isspace.c */
int		ft_isspace(char c);

/* ft_strdup2.c */
char	**ft_strdup2(char **s);
/* int_putstr_fd.c */
int		int_putstr_fd(char *s, int fd);

/* int_putendl_fd.c */
int		int_putendl_fd(char *s, int fd);

#endif /* MINISHELL_H */
