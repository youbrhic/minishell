/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:20:22 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/26 20:43:07 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_env(char ***env)
{
	char *v_qts;
	int	f_occu;
	int	i;
	int	j;
	int	k;

	i = -1;
	while ((*env)[++i])
	{
		j = 0;
		k = 0;
		f_occu = 0;
		v_qts = malloc(ft_strlen((*env)[i]) + 3);
		if (!v_qts)
			return ;
		while ((*env)[i][k])
		{
			v_qts[j] = (*env)[i][k];
			if (v_qts[j] == '=' && f_occu == 0)
			{
				v_qts[j + 1] = '\"';
				f_occu = 1;
				j += 2;
			}
			else
				j++;
			k++;
		}
		v_qts[j] = '\"';
		v_qts[j + 1] = '\0';
		printf("declare -x %s\n", v_qts);
		free(v_qts);
	}
}

int	get_env(char *key, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(key, env[i], j))
			return (i);
	}
	return (0);
}

void	add_env_kv(char *arg, char ***env)
{
	char	**new_env;
	int		j;

	printf("size = %d\n", get_size_mat(*env));
	new_env = (char **)malloc(sizeof(char *) * (get_size_mat(*env) + 2));
	if (!new_env)
		return ;
	j = -1;
	while ((*env)[++j])
		new_env[j] = ft_strndup((*env)[j], ft_strlen((*env)[j]));
	new_env[j] = arg;
	new_env[j + 1] = NULL;
	free_mat(env);
	*env = new_env;
}

// void	update_env(char *arg, char **env)
// {
// 	int		i;
// 	char	*key;
// 	char	*value;
// 	char	*tmp;

// 	i = 0;
// 	while (arg[i] && arg[i] != '+')
// 		i++;
// 	key = ft_strndup(arg, i);
// 	value = ft_strchr(arg, '=') + 1;
// 	tmp = ft_strjoin(key, "=");
// 	tmp = ft_strjoin(tmp, value);
// 	if (get_env(key, env))
// 	{
// 		free(get_env(key, env));
// 		set_env(key, tmp, env);
// 	}
// 	else
// 		add_env_kv(tmp, env);
// 	free(key);
// 	free(tmp);
// }

// void	add_env_k(char *arg, char **env)
// {
// 	char	*key;
// 	char	*value;
// 	char	*tmp;

// 	key = ft_strjoin(arg, "=");
// 	value = ft_strchr(arg, '=') + 1;
// 	tmp = ft_strjoin(key, value);
// 	add_env_k(tmp, env);
// 	free(key);
// 	free(tmp);
// }

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
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return 0;
	}
	return 1;
}


void	ft_export(char **args, char ***env)
{
	int	i;

	i = 1;
	if (!args[1])
		print_export_env(env);
	else
	{
		while (args[i])
		{
			if (!parse_arg(args[i]))
				return ;
			// if (ft_strchr(args[i], '+='))
			// 	update_env(args[i], env);
			// else if (ft_strchr(args[i], '='))
			// 	add_env_kv(args[i], env);
			// else
			// for (int j = 0; env[j]; j++)
			// 	printf("env[%d] = %s\n", j, env[j]);
			// printf("------------------------\n");
			add_env_kv(args[i], env);
			for (int j = 0; (*env)[j]; j++)
				printf("env[%d] = %s\n", j, (*env)[j]);
			i++;
		}
	}
}
