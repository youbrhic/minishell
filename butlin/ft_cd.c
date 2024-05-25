/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:21:27 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/25 16:40:54 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_gete(char *key, char **env, int k_or_v)
{
	int	index;

	index = chr_key_env(key, env);
	if (index < 0)
		return (NULL);
	if (k_or_v == 0)
		return (env[index]);
	return (env[index] + ft_strlen(key) + 1);
}

int	ft_setoldpwd(char ***env)
{
	char	*oldpwd;
	char	*tmp;

	oldpwd = ft_gete("PWD", *env, 1);
	if (!oldpwd)
		return (1);
	tmp = ft_strjoin(ft_strdup("OLDPWD="), oldpwd);
	add_env_kv(tmp, env);
	return (free(tmp), 1);
}

int	update_env(char ***env, char *path)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd(ERROR_CD, 2);
		if (!ft_gete("PWD", *env, 0))
			return (1);
		if (ft_strcmp(path, "..") == 0)
			tmp = ft_strjoin(ft_strdup(ft_gete("PWD", *env, 0)), "/..");
		else
			tmp = ft_strjoin(ft_strdup(ft_gete("PWD", *env, 0)), "/.");
		add_env_kv(tmp, env);
		return (free(tmp), 1);
	}
	tmp = ft_strjoin(ft_strdup("PWD="), pwd);
	add_env_kv(tmp, env);
	return (free(tmp), free(pwd), 0);
}

int	ft_cd(char **path, char ***env)
{
	int		ret;

	ft_setoldpwd(env);
	if (path[1] && path[1][0] == '-' && path[1][1])
	{
		ft_putstr_fd("minishell: no option\n", 2);
		return (1);
	}
	if (!path[1])
		ret = chdir(ft_gete("HOME", *env, 1));
	else
		ret = chdir(path[1]);
	if (ret < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (update_env(env, path[1]));
}
