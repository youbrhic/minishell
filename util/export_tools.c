/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:23:25 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/20 03:48:47 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_env(char **env, char ***n_env, int size)
{
	int		i;

	(void)size;
	*n_env = (char **)malloc(sizeof(char *) * (size));
	if (!*n_env)
		return ;
	i = -1;
	while (env[++i])
	{
		(*n_env)[i] = ft_strndup(env[i], ft_strlen(env[i]));
		if (!(*n_env)[i])
			return ;
	}
	(*n_env)[i] = NULL;
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

char	*ft_remove_plus(char *c)
{
	int		i;
	int		j;
	char	*new;
	int		f_oc;

	(1) && (f_oc = 0, i = 0, j = 0);
	new = (char *) malloc(ft_strlen(c) + 1);
	if (!new)
		return (NULL);
	while (c[i])
	{
		if (c[i] == '+' && f_oc == 0)
		{
			i++;
			f_oc = 1;
		}
		new[j] = c[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(c);
	return (new);
}

int	chr_key_env(char *key, char **env)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (key[k] && key[k] != '=')
		k++;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (!ft_strncmp(key, env[i], k))
			return (i);
	}
	return (-1);
}
