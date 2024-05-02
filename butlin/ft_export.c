/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:20:22 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/02 01:45:21 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_env(char ***env)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[i][j] && (*env)[i][j] != '=')
			j++;
		key = ft_strndup((*env)[i], j);
		if ((*env)[i][j] == '=')
		{
			value = ft_strdup((*env)[i] + j + 1);
			printf("declare -x %s=\"%s\"\n", key, value);
			free(value);
		}
		else
			printf("declare -x %s\n", key);
		free(key);
		i++;
	}
}

int	add_env_kv(char *arg, char ***env)
{
	char	**n_env;
	int		s_env;
	int		index;

	index = chr_key_env(arg, *env);
	if (index == -1)
	{
		s_env = size_env(*env);
		// n_env = new_env(*env, s_env + 2);
		// if (!n_env)
		// 	return (1);
		printf("s_env = %d\n", s_env);
		printf("arg = %s\n", arg);
		(*env)[s_env] = arg;
		(*env)[s_env + 1] = NULL;
		// problem here of freeing the old env
		// free_env(env);
		// *env = n_env;
	}
	else
	{
		(*env)[index] = arg;
		return (0);
	}
	return (0);
}

int	update_env_kv(char *arg, char ***env)
{
	int	index;
	int	i;

	i = 0;

	ft_remove_plus(&arg);
	index = chr_key_env(arg, *env);
	if (index == -1)
	{
		add_env_kv(arg, env);
		return (0);
	}
	else
	{
		while ((*env)[index][i] && (*env)[index][i] != '=')
			i++;
		if ((*env)[index][i] == '=')
			(*env)[index] = ft_strjoin((*env)[index], arg + i + 1);
		else
			(*env)[index] = ft_strjoin((*env)[index], arg + i);
	}
	return (0);
}

int add_env_k(char *arg, char ***env)
{
	char	**n_env;
	int		s_env;
	int		index;

	index = chr_key_env(arg, *env);
	if (index == -1)
	{
		s_env = size_env(*env);
		n_env = new_env(*env, s_env + 2);
		if (!n_env)
			return (1);
		n_env[s_env] = arg;
		n_env[s_env + 1] = NULL;
		// problem here of freeing the old env
		// free_env(env);
		*env = n_env;
	}
	else
	{
		return (0);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int parse_arg(char *arg)
{
	char	*key;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_strndup(arg, i);
	if (key[0] != '_' && !ft_isalpha(key[0]))
	{
		printf("minishell: export: `%s': not a valid identifier 1\n", arg);
		return (1);
	}
	i = 0;
	while (key[i])
	{
		if (!is_alphanum(key[i]) && key[i] != '_' && key[i] != '+')
		{
			printf("minishell: export: `%s': not a valid identifier 2\n", arg);
			return (1);		
		}
		i++;
	}
	free(key);
	return (0);
}

int	ft_export(char **args, char ***env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (args[1] && args[1][0] == '-')
	{
		printf("no options\n");
		return (2);
	}
	if (!args[1])
		print_export_env(env);
	else
	{
		while (args[i])
		{
			if (!parse_arg(args[i]))
			{
				if (ft_strexsit(args[i], "+="))
					update_env_kv(args[i], env);
				else if (ft_strchr(args[i], '='))
					add_env_kv(args[i], env);
				else
					add_env_k(args[i], env);
			}
			else
				exit_status = 1;
			i++;
		}
	}
	return (exit_status);
}
