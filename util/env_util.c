/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:51:35 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/28 00:29:13 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **get_newenv()
{
    char    **new_env;
    int     i;

    new_env = malloc(sizeof(char *) * 4);
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
    if (!new_env)
        return (free2d(&new_env, i), NULL);
    new_env[++i] = NULL;
    return (new_env);
}

char **get_matr_copy(char **env)
{
	int		i;
	char	**new_env;

    if (!env || !env[0])
        return (get_newenv());
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