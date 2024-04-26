# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/04/26 20:04:55 by youbrhic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c execution/ft_exec_bultin.c execution/ft_hardoc.c      parsing/ft_create_list.c   parsing/ft_get_nodes.c     util/bultin_cmd.c          util/ft_split.c            util/libft_util.c \
		execution/ft_exec_cmd.c    execution/ft_open_file.c   parsing/ft_create_node.c   parsing/ft_parse_line.c    util/env_util.c            util/ft_split_cmd.c        util/libft_util2.c \
		execution/ft_exec_list.c   parsing/ft_add_space.c     parsing/ft_expand.c        parsing/ft_remove_quotes.c util/ft_itoa.c             util/ft_split_cmd_util.c   util/other_util.c \

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g -fsanitize=address

#CFLAGS = -Wall -Wextra -Werror -fsanitize=address

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
