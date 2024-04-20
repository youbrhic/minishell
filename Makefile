# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/04/19 01:00:24 by aait-bab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c execution/exec_cmd.c parsing/create_node.c util/ft_split.c  util/libft_util2.c \
		execution/exec_list.c  parsing/get_nodes.c util/ft_split_cmd.c util/other_util.c \
		execution/open_file.c parsing/parse_line.c  util/ft_split_cmd_util.c \
		parsing/add_space.c  parsing/pipe_redirection_fun.c  util/libft_util.c\
		execution/exec_bultin.c util/bultin_cmd.c

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
