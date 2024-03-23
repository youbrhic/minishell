/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:19:16 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/23 10:58:47 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libc.h>
# include <errno.h>

/*-----------------struct-of-node------------*/
//-------------------------------------------//

typedef struct s_node
{
	int				input;
	int				output;
	char			*cmd;
	char			*list_files_redirections;
	struct s_node	*next;
}				t_node;

/*-------------util functions -------------*/
//-----------------------------------------//

void	init_node(t_node **node);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstclear(t_node **lst);
void	free_mat(char ***mtr);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split_cmd(char const *s);
char	*ft_strndup(const char *s1, int n);
char	**ft_split(char const *s, char c);
int		count_words(char const *s);
int		ft_strlen(char *c);
int		ft_strcmp(const char *s1, const char *s2);
int		is_quot(char c);
int		is_space(char c);
int		get_size_mat(char **str);

/*-----------------parsing-------------------*/
//-------------------------------------------//

void	check_fd(t_node *node, char *redirection);
char	*add_space(char *input);
int		parse_line(char **matr);
int		is_oper(char *str);
int		is_redirection(char	*str);
int		open_file(char *file, char *redirection);
int		check_cmd_line(char **matr, int start, int end);
t_node	*get_nodes(char **matr);
t_node	*create_node(char **matr, int start, int end);

/*--------------------execution--------------------*/
//-------------------------------------------------//

int		exec_cmd(char *cmd, char **env);
void	exec_node(t_node *node, char **env);
#endif