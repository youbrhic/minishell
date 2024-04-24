# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/04/24 08:33:36 by aait-bab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c butlin/ft_cd.c  execution/exec_bultin.c  parsing/get_nodes.c   util/ft_split_cmd_util.c \
		butlin/ft_echo.c    execution/exec_cmd.c     parsing/parse_line.c   util/libft_util.c \
		butlin/ft_env.c          execution/exec_list.c    parsing/remove_quotes.c  util/libft_util2.c \
		butlin/ft_exit.c         execution/open_file.c     util/other_util.c \
		butlin/ft_export.c       parsing/add_space.c      util/ft_itoa.c butlin/ft_pwd.c  parsing/create_node.c util/ft_split.c \
		butlin/ft_unset.c        parsing/expand.c         util/ft_split_cmd.c  

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g 

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
