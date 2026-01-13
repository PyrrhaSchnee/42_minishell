# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanli <yanli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 11:40:02 by yanli             #+#    #+#              #
#    Updated: 2025/07/13 21:14:00by yanli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAG	= -Wall -Werror -Wextra #\
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
			-Wno-unused-result 
AR		= ar rcs
RM		= rm -f

SRCS 	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_printf.c ft_printf_hex.c ft_printf_nbr.c get_next_line.c \
		ft_strcmp.c ft_strcpy.c ft_strcat.c

OBJS	= $(SRCS:.c=.o)

DEPS	= $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

-include $(DEPS)

%.o:%.c
	$(CC) $(CFLAG) -MMD -I. -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

z:
	$(MAKE) re
	$(MAKE) clean

.PHONY: clean fclean re all
