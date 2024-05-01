# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/04/29 19:12:25 by aait-bab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c butlin/ft_cd.c                  butlin/ft_unset.c               execution/ft_open_file.c        parsing/ft_parse_line.c         util/ft_split_cmd.c \
butlin/ft_echo.c                execution/ft_excev_cmd.c        parsing/ft_add_space.c          parsing/ft_remove_quotes.c      util/ft_split_cmd_util.c\
butlin/ft_env.c                 execution/ft_exec_bultin.c      parsing/ft_create_list.c                      util/libft_util.c\
butlin/ft_exit.c                execution/ft_exec_cmd.c         parsing/ft_create_node.c        util/env_util.c                 util/libft_util2.c\
butlin/ft_export.c              execution/ft_exec_list.c        parsing/ft_expand.c             util/ft_itoa.c                  util/other_util.c\
butlin/ft_pwd.c                 execution/ft_hardoc.c           parsing/ft_get_nodes.c          util/ft_split.c  util/export_tools.c

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g #-fsanitize=address

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
