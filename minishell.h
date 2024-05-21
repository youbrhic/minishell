/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:19:16 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/21 00:41:32 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libc.h>
# include <errno.h>

# define ERROR_CD "cd: error retrieving current \
					directory: getcwd: cannot access parent \
					directories: No such file or directory\n"

int		g_cld_proc;

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
	int		exit_status;
}				t_argument;

/*--------------------utils--------------------------*/

void	free_mat(char **mtr);
void	ft_lstclear(t_node **lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_perror(char *str, int ex);
void	ft_setenv(char *par, char *val, char **env, int flag);
int    	ft_add_skiper(char **token);
char	**ft_split(char const *s, char c);
char	**ft_split_cmd(char const *s);
char	**free2d(char ***arr, int index);
char 	**get_matr_copy(char **env);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int n);
char	*ft_itoa(int n);
char	*ft_getenv(char *str, char **env);
int		count_words(char const *s);
int		ft_strchr(const char *s, int c);
int		ft_strlen(char *c);
int		ft_strcmp(const char *s1, const char *s2);
int		is_quot(char c);
int		is_space(char c);
int		get_size_mat(char **str);
int		ft_lstsize(t_node *lst);
int 	is_alphanum(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);

/*---------------------parsing--------------------------*/

int		ft_expand(char **token, int flag, int exit_status, char **env);
int		ft_remove_quotes(char **token);
void	init_node(t_node **node);
char	**ft_token_cmds(char *cmds, char **env, int exit_status);
char	*ft_add_space(char *input);
int		ft_parse_line(char **matr, int exit_status);
int		is_oper(char *str);
int		is_redirection(char	*str);
t_node	*ft_get_nodes(char **matr);
t_node	*ft_create_node(char **matr, int start, int end);
t_node	*ft_create_list(char *input, int *exit_status);

/*--------------------execution------------------------*/

void    ft_hardoc(char *limiter);
int		ft_exec_cmd(char *cmd, char ***env, int exit_status);
int		ft_exec_list(t_node *lst, char ***env, int exit_status);
int		ft_create_file(char *redirection, t_argument *arg, int exit_status, char **env);
int		ft_open_file(char *redirection, t_argument arg, int exit_status, char **env);
int		ft_execv_cmd(t_node *node, char ***env, int exit_status);

/*--------------------bultin--------------------*/

void	new_env(char **env, char ***n_env, int size);
int		size_env(char **env);
int		chr_key_env(char *key, char **env);
void	free_env(char ***env);
char	*ft_gete(char *key, char **env, int k_or_v);

int		ft_cd(char **args, char ***env);
int		ft_echo(char **args);
int		ft_env(char **args, char ***env);
void	ft_exit(char **args);
char	*ft_remove_plus(char *c);
int		ft_pwd(char **args, char ***env);
int		ft_unset(char **args, char ***env);

int		ft_export(char **args, char ***env);
void	add_env_kv(char *arg, char ***env);
int		parse_arg(char *arg);

int		ft_strexsit(char *s, char *str);
int		ft_isalpha(int c);

int		ft_exec_bultin(char **args, char ***env);
int		check_bultin(char *cmd);

#endif