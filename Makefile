# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanli <yanli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 16:54:30 by yanli             #+#    #+#              #
#    Updated: 2025/07/20 12:28:04 by yanli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra \
			-ggdb3 -Og -fno-omit-frame-pointer \
			-Wsign-conversion -Wformat-security -Wshadow -Wnull-dereference \
			-Wundef \
			-Wformat=2 -Wredundant-decls -Wstrict-prototypes \
			-march=native -mtune=native \
			-Wno-analyzer-fd-leak \
			-Wno-analyzer-use-of-uninitialized-value \
			-Wuninitialized -Wno-maybe-uninitialized \
			-fanalyzer -fvar-tracking-assignments -Wduplicated-cond \
			-Wduplicated-branches -fvar-tracking-uninit \
			-Wno-unused-result \
			#-fsanitize=undefined,address,leak -fno-sanitize-recover=all

SRCS		= init.c error.c signal.c token.c token2.c \
				token3.c main.c exit.c clean_all.c \
				token4.c token5.c utils.c \
				ft_isspace.c ft_strdup2.c int_putendl_fd.c \
				int_putstr_fd.c export.c export2.c export3.c export4.c \
				unset.c envp_expansion.c pwd.c cd.c env.c ft_strsecdup.c \
				token6.c token7.c error_exec.c \
				exec_command1.c exec_command2.c \
				utils2.c put_in_tab.c exec.c redir_sanitizer.c \
				redir_sanitizer2.c is_built_in.c echo.c exec_command3.c \
				heredoc.c heredoc2.c token8.c exec2.c heredoc3.c \
				split_spaceholder.c put_in_tab2.c exec_command4.c \
				utils3.c exec3.c signal2.c exec_command5.c heredoc4.c \
				heredoc5.c utils4.c debug.c exec_command6.c envp_expansion2.c \
				envp_expansion3.c

LDFLAGS		= -lreadline

OBJS		= $(SRCS:.c=.o)

DEPS		= $(OBJS:.o=.d)

LIBFT_DIR	= ./libft

LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME) 

-include $(DEPS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -I. $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -MMD -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(DEPS) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

z:
	$(MAKE) fclean
	$(MAKE) -j$(nproc)
	$(MAKE) clean

.PHONY: all re z clean fclean
