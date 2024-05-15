/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:20:22 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/13 23:23:34 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printf_var_env(char ***env)
{
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
	{
		j = 0;
		if ((*env)[i][0] != '_')
		{
			ft_putstr_fd("declare -x ", 1);
			while ((*env)[i][j] && (*env)[i][j] != '=')
			{
				write(1, &(*env)[i][j++], 1);
			}
			if ((*env)[i][j] == '=')
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd((*env)[i] + j + 1, 1);
				ft_putstr_fd("\"", 1);
			}
			write(1, "\n", 1);
		}
		i++;
	}
}

void	add_env_kv(char *arg, char ***env)
{
	int		s_env;
	char	**n_env;
	int		index;

	index = chr_key_env(arg, *env);
	if (index == -1)
	{
		(1) && (s_env = size_env(*env)), (new_env(*env, &n_env, s_env + 2));
		if (!n_env)
			return ;
		free_mat(*env);
		n_env[s_env] = ft_strdup(arg);
		if (!n_env[s_env])
			return ;
		(1) && (n_env[s_env + 1] = NULL, *env = n_env);
	}
	else
	{
		if (ft_strchr(arg, '='))
		{
			(1) && (free((*env)[index]), (*env)[index] = ft_strdup(arg));
			if (!(*env)[index])
				return ;
		}
	}
}

void	update_env_kv(char *arg, char ***env)
{
	char	*value;
	int		index;
	int		i;

	(1) && (i = 0, index = chr_key_env(arg, *env));
	if (index == -1)
	{
		add_env_kv(arg, env);
		return ;
	}
	else
	{
		while ((*env)[index][i] && (*env)[index][i] != '=')
			i++;
		if ((*env)[index][i] == '=')
			value = ft_strdup(arg + i + 1);
		else
			value = ft_strdup(arg + i);
		if (!value)
			return ;
		(*env)[index] = ft_strjoin((*env)[index], value);
		if (!(*env)[index])
			return ;
		free(value);
	}
}

void	execute_export(char **args, char ***env, int i)
{
	if (ft_strexsit(args[i], "+="))
	{
		args[i] = ft_remove_plus(args[i]);
		update_env_kv(args[i], env);
	}
	else
		add_env_kv(args[i], env);
}

int	ft_export(char **args, char ***env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (args[1] && args[1][0] == '-')
	{
		write(2, "no options\n", 11);
		return (2);
	}
	if (!args[1])
		printf_var_env(env);
	else
	{
		while (args[i])
		{
			if (!parse_arg(args[i]))
				execute_export(args, env, i);
			else
				exit_status = 1;
			i++;
		}
	}
	return (exit_status);
}
