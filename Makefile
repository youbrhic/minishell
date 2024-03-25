# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/03/24 11:11:04 by youbrhic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c execution/exec_cmd.c parsing/create_node.c util/ft_split.c util/libft_util.c \
		execution/exec_list.c parsing/get_nodes.c util/ft_split_cmd.c util/libft_util2.c \
		parsing/add_space.c parsing/parse_line.c util/ft_split_cmd_util.c util/other_util.c

OBJS = $(FILES:.c=.o)

RM = rm -f

INCLUDE = minishell.h

CC = gcc  -g 

CFLAGS = #-Wall -Wextra -Werror -fsanitize=address

READLINE_FLAG = -lreadline -lncurses 

all : $(NAME)

%.o : %.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAG) -o $(NAME) $(OBJS) 

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all 