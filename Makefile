# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:12:01 by youbrhic          #+#    #+#              #
#    Updated: 2024/04/24 02:09:18 by youbrhic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c execution/exec_bultin.c execution/open_file.c parsing/get_nodes.c util/ft_itoa.c util/libft_util.c \
		execution/exec_cmd.c  parsing/add_space.c parsing/parse_line.c util/ft_split.c util/libft_util2.c \
		execution/exec_list.c parsing/create_node.c parsing/remove_quotes.c util/ft_split_cmd.c util/other_util.c \
		execution/ft_hardoc.c  parsing/expand.c  util/bultin_cmd.c util/ft_split_cmd_util.c

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
