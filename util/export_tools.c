/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:23:25 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/29 19:57:06 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**new_env(char **env, int size)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(sizeof(char *) * (size));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strndup(env[i], ft_strlen(env[i]));
	new_env[i] = NULL;
	return (new_env);
}

int	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	free_env(char ***env)
{
	int	i;

	i = -1;
	while ((*env)[++i])
		free((*env)[i]);
	free(*env);
	*env = NULL;
}

void	ft_remove_plus(char **c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(ft_strlen(*c) + 1);
	if (!new)
		return ;
	while ((*c)[i])
	{
		if ((*c)[i] == '+')
			i++;
		new[j] = (*c)[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(*c);
	*c = new;
}

int	chr_key_env(char *key, char **env)
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
	return (-1);
}

