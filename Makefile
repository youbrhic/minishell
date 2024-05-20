# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/05/20 04:25:24 by youbrhic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c butlin/ft_cd.c             execution/ft_create_file.c parsing/ft_create_list.c   signals/signals.c          util/libft_util2.c \
butlin/ft_echo.c           execution/ft_excev_cmd.c   parsing/ft_create_node.c   util/env_util.c            util/libft_util3.c\
butlin/ft_env.c            execution/ft_exec_bultin.c parsing/ft_expand.c        util/export_tools.c        util/other_util.c\
butlin/ft_exit.c           execution/ft_exec_cmd.c    parsing/ft_get_nodes.c     util/ft_itoa.c             util/other_util2.c\
butlin/ft_export.c         execution/ft_exec_list.c   parsing/ft_parse_line.c    util/ft_split.c\
butlin/ft_pwd.c            execution/ft_hardoc.c      parsing/ft_remove_quotes.c util/ft_split_cmd.c\
butlin/ft_unset.c          execution/ft_open_file.c   parsing/ft_token_cmds.c    util/ft_split_cmd_util.c\
execution/exec_fun.c       parsing/ft_add_space.c     parsing/parse_export.c     util/libft_util.c

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC =cc #-fsanitize=address

CFLAGS = -Wall -Wextra -Werror

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

