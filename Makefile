# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/04/24 08:41:25 by aait-bab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c butlin/ft_cd.c           butlin/ft_export.c       execution/exec_list.c    parsing/remove_quotes.c \
butlin/ft_cd.o           butlin/ft_export.o       execution/ft_hardoc.c    util/ft_itoa.c \
butlin/ft_echo.c         butlin/ft_pwd.c          execution/open_file.c    util/ft_split.c \
butlin/ft_echo.o         butlin/ft_pwd.o          parsing/add_space.c      util/ft_split_cmd.c \
butlin/ft_env.c          butlin/ft_unset.c        parsing/create_node.c    util/ft_split_cmd_util.c \
butlin/ft_env.o          butlin/ft_unset.o        parsing/expand.c         util/libft_util.c \
butlin/ft_exit.c         execution/exec_bultin.c  parsing/get_nodes.c      util/libft_util2.c \
butlin/ft_exit.o         execution/exec_cmd.c     parsing/parse_line.c     util/other_util.c

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g -fsanitize=address

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
