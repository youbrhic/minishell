/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:23:25 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/21 22:02:55 by aait-bab         ###   ########.fr       */
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

	(1) && (i = 0, j = 0, f_oc = 0);
	new = (char *)malloc(ft_strlen(c));
	if (!new)
		return (NULL);
	while (c[i])
	{
		if (c[i] == '+' && f_oc == 0)
		{
			f_oc = 1;
			i++;
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
	int		i;
	int		k;
	int		l;

	i = -1;
	k = 0;
	while (key[k] && key[k] != '=')
		k++;
	while (env[++i])
	{
		l = 0;
		while (env[i][l] && env[i][l] != '=')
			l++;
		if (!ft_strncmp(key, env[i], k) && l == k)
			return (i);
	}
	return (-1);
}
