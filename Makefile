# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/04/21 16:46:38 by youbrhic         ###   ########.fr        #
=======
<<<<<<< HEAD
#    Updated: 2024/04/19 01:00:24 by aait-bab         ###   ########.fr        #
=======
#    Updated: 2024/04/20 05:07:27 by youbrhic         ###   ########.fr        #
>>>>>>> 59802f23c1eec128652d13fd0305fde8ea55e5d8
>>>>>>> 93120e4cc50f1e4e24a895bd8021f9c5f7df5175
#                                                                              #
# **************************************************************************** #

NAME = minishell

<<<<<<< HEAD
FILES = main.c execution/exec_cmd.c parsing/create_node.c util/ft_split.c  util/libft_util2.c \
		execution/exec_list.c  parsing/get_nodes.c util/ft_split_cmd.c util/other_util.c \
		execution/open_file.c parsing/parse_line.c  util/ft_split_cmd_util.c \
		parsing/add_space.c  parsing/pipe_redirection_fun.c  util/libft_util.c\
		execution/exec_bultin.c util/bultin_cmd.c
=======
FILES = main.c execution/exec_cmd.c     parsing/create_node.c    parsing/remove_quotes.c  util/ft_split_cmd_util.c \
		execution/exec_list.c    parsing/expand.c         util/ft_itoa.c           util/libft_util.c \
		execution/open_file.c    parsing/get_nodes.c      util/ft_split.c          util/libft_util2.c \
		parsing/add_space.c      parsing/parse_line.c     util/ft_split_cmd.c      util/other_util.c
>>>>>>> 59802f23c1eec128652d13fd0305fde8ea55e5d8

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g 

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
