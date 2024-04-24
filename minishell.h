/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:19:16 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/21 06:37:47 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libc.h>
# include <errno.h>

/*-----------------exit_state---------------*/
int		g_exit_state;
//------------------------------------------//

/*-----------------struct-of-node------------*/
//-------------------------------------------//

typedef struct s_node
{
	char			*cmd;
	char			*redirections;
	struct s_node	*next;
}				t_node;

/*------------------struct-of-argument-------------*/
//--------------------------------------------------//

typedef struct s_argument
{
	int		p_1[2];
	int		p_2[2];
	int		input;
	int		output;
}				t_argument;

/*-------------util functions -------------*/
//-----------------------------------------//

void	free_mat(char ***mtr);
void	ft_lstclear(t_node **lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_perror(char *str, int ex);
char	**ft_split(char const *s, char c);
char	**ft_split_cmd(char const *s);
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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*-----------------parsing-------------------*/
//-------------------------------------------//

void	expand(char **token);
void	init_node(t_node **node);
char	*add_space(char *input);
int		parse_line(char **matr);
int		is_oper(char *str);
int		is_redirection(char	*str);
t_node	*get_nodes(char **matr);
t_node	*create_node(char **matr, int start, int end);

/*--------------------execution--------------------*/
//-------------------------------------------------//

int		exec_cmd(char *cmd, char **env);
int		exec_list(t_node *lst, char **env);
int		open_file(char *redirection, int *input, int *output);
// bultin function
void 	exec_bultin(char **args, char **env);
int		check_bultin(char *cmd);


/*--------------------bultin--------------------*/
//-------------------------------------------------//

void	ft_echo(char **args);
void	ft_pwd(void);
void	ft_cd(char **path);
void	ft_env(char **env);
void	ft_exit(void);
void	ft_unset(char **args, char **env);
void	ft_export(char **args, char **env);
#endif