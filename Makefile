# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/05/17 02:10:54 by youbrhic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c butlin/ft_cd.c                  parsing/ft_create_list.c \
		butlin/ft_echo.c                parsing/ft_create_node.c \
		butlin/ft_env.c                 parsing/ft_expand.c parsing/parse_export.c\
		butlin/ft_exit.c                parsing/ft_get_nodes.c \
 		butlin/ft_export.c              parsing/ft_parse_line.c \
		butlin/ft_pwd.c                 parsing/ft_remove_quotes.c \
 		butlin/ft_unset.c               util/env_util.c \
		execution/ft_create_file.c      util/export_tools.c \
		execution/ft_excev_cmd.c        util/ft_itoa.c \
		execution/ft_exec_bultin.c      util/ft_split.c \
		execution/ft_exec_cmd.c         util/ft_split_cmd.c \
		execution/ft_exec_list.c        util/ft_split_cmd_util.c \
		execution/ft_hardoc.c           util/libft_util.c \
		execution/ft_open_file.c        util/libft_util2.c \
		parsing/ft_add_space.c          util/other_util.c parsing/ft_token_cmds.c util/util5.c

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g -fsanitize=address

CFLAGS =# -Wall -Wextra -Werror #-fsanitize=address

READLINE_FLAGS = -lreadline -lncurses 

all : $(NAME)

%.o : %.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) -o $(NAME) $(OBJS) 

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all 
