/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:19:16 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/28 03:33:58 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libc.h>
# include <errno.h>

int		g_exit_status;

typedef struct s_node
{
	char			*cmd;
	char			*redirections;
	struct s_node	*next;
}				t_node;

typedef struct s_argument
{
	int		p_1[2];
	int		p_2[2];
	int		input;
	int		output;
}				t_argument;

void	free_mat(char ***mtr);
void	ft_lstclear(t_node **lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_perror(char *str, int ex);
void	ft_remove_quotes(char **token);
char	**ft_split(char const *s, char c);
char	**ft_split_cmd(char const *s);
char	**free2d(char ***arr, int index);
char 	**get_matr_copy(char **env);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strndup(const char *s1, int n);
char	*ft_itoa(int n);
int		count_words(char const *s);
int		ft_strlen(char *c);
int		ft_strcmp(const char *s1, const char *s2);
int		is_quot(char c);
int		is_space(char c);
int		get_size_mat(char **str);
int		ft_lstsize(t_node *lst);
int 	is_alphanum(char c);

void	ft_expand(char **token, int flag, int exit_status);
void	init_node(t_node **node);
char	*ft_add_space(char *input);
int		ft_parse_line(char **matr);
int		is_oper(char *str);
int		is_redirection(char	*str);
t_node	*ft_get_nodes(char **matr);
t_node	*ft_create_node(char **matr, int start, int end);
t_node	*ft_create_list(char *input, int *exit_status);


void    ft_hardoc(char *limiter);
int		ft_exec_cmd(char *cmd, char ***env);
int		ft_exec_list(t_node *lst, char ***env);
int		ft_open_file(char *redirection, int *input, int *output, int flag);
int		ft_execv_cmd(t_node *node, char ***env);

/*--------------------bultin--------------------*/
//-------------------------------------------------//

void 	ft_echo(char **args);
void	ft_pwd();
void	ft_cd(char **args);
void	ft_env(char **env);
void	ft_exec_bultin(char *cmd, char **env);
int		check_bultin(char *cmd);

#endif