/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:20:22 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/04 08:37:32 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printf_var_env(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    write(1, str, i);
    if (str[i])
    {
		write(1, &str[i++], 1);
        write(1, "\"", 1);
        while (str[i])
		{
            write(1, &str[i], 1);
			i++;
		}
        write(1, "\"", 1);
    }
    write(1, "\n", 1);
}

static void    affiche_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		printf_var_env(env[i]); 
}

static void    print_error(char *str)
{
    write(2, "minishell: ", 11);
    write(2, str, ft_strlen(str));
    write(2, ": not a valid identifier", 25);
	write(2, "\n", 1);
}

static int parse_export(char *str, char **env)
{
    int        i;
    char    **token_exp;
	int		size;
	char	*tmp;

    token_exp = ft_split(str, '=');
	if (!token_exp)
		return (write(2, "malloc problem \n", 17), 1);
    if (token_exp[0][0] >= '0' && token_exp[0][0] <= '9'
		|| (!is_alphanum(token_exp[0][0])))
        return (print_error(token_exp[0]), 1);
	size = ft_strlen(token_exp[0]);
    i = 0;
	if (token_exp[0][size - 1] == '+')
	{
		tmp = ft_strndup(token_exp[0], ft_strlen(token_exp[0]) - 1);
		if (!tmp)
			return (write(2, "malloc problem \n", 17), 1);
		if (ft_getenv(tmp, env))
			size--;
		free(tmp);
	}
    while (token_exp[0][++i] && i < size)
	{
        if (!is_alphanum(token_exp[0][i]))
            return (print_error(token_exp[i]), free_mat(token_exp), 1);
	}
    return (free_mat(token_exp), 0);
}

static int get_index_equl(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

static char **get_new_env(char *var, char **env)
{
	char	**new_env;
	int		i;
	char	*tmp;

	i = -1;
	// if (ft_getenv(var, env))
	// 	new_env = get_matr_copy(env), ft_setenv()
	return (NULL);
}

static char	**ft_add_var_env(char *var, char **env)
{
	char	*arg;
	char	*val;
	char	**new_env;

	// if (get_index_equl(var) == -1)
	// 	return ()'
	return (NULL);
}

int		ft_export(char **token_cmd, char ***env)
{
	int        i;
	int		state;

	state = 0;
	if (get_size_mat(token_cmd) == 1)
		return (affiche_env(*env), state);
	if (token_cmd[0][0] == '-')
		return (write(2, "minishell : export invalid option\n", 35), 2);
	i = 0;
	while (token_cmd[++i])
	{
		if (parse_export(token_cmd[i], *env))
			state = 1;
		// else
		// 	*env = ft_add_var_env(token_cmd[i], *env);
	}
	return (state);
}
