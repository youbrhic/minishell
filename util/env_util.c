/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:51:35 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 03:39:17 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_newenv(void)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * 5);
	if (!new_env)
		return (NULL);
	i = -1;
	new_env[++i] = ft_strndup("PWD=/Users/youbrhic/Desktop/mini", 33);
	if (!new_env[i])
		return (free(&new_env), NULL);
	new_env[++i] = ft_strndup("SHLVL=1", 8);
	if (!new_env[i])
		return (free2d(&new_env, i));
	new_env[++i] = ft_strndup("_=/usr/bin/env", 15);
	if (!new_env[i])
		return (free2d(&new_env, i), NULL);
	new_env[++i]
		= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if (!new_env[i])
		return (free2d(&new_env, i), NULL);
	new_env[++i] = NULL;
	return (new_env);
}

char	**get_env(char **env)
{
	if (!env || !env[0])
		return (get_newenv());
	return (get_matr_copy(env));
}

char	**get_matr_copy(char **env)
{
	int		i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (get_size_mat(env) + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i] && i < get_size_mat(env))
	{
		new_env[i] = ft_strndup(env[i], ft_strlen(env[i]));
		if (!new_env[i])
			return (free2d(&new_env, i));
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*ft_getenv(char *str, char **env)
{
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str))
			&& env[i][ft_strlen(str)] == '=')
		{
			return (&env[i][ft_strlen(str) + 1]);
		}
	}
	return (NULL);
}

void	ft_setenv(char *par, char *val, char ***env, int flag)
{
	int		i;
	char	*tmp;

	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], par, ft_strlen(par))
			&& (*env)[i][ft_strlen(par)] == '=')
		{
			if (flag)
				tmp = ft_strdup((*env)[i]);
			else
				(1) && (tmp = ft_strdup(par), tmp = ft_strjoin(tmp, "="));
			tmp = ft_strjoin(tmp, val);
			if (tmp)
			{
				free((*env)[i]);
				(*env)[i] = tmp;
			}
			break ;
		}
	}
}
