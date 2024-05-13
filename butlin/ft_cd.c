/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:21:27 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/13 14:29:57 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_env(char ***env, char *oldpwd)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("Error: getcwd failed\n", 2);
		return (1);
	}
	add_env_kv(ft_strjoin(ft_strdup("OLDPWD="), oldpwd), env);
	add_env_kv(ft_strjoin(ft_strdup("PWD="), pwd), env);
	free(pwd);
	free(oldpwd);
	return (0);
}

int	ft_cd(char **path, char ***env)
{
	int		ret;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("Error: getcwd failed\n", 2);
		return (1);
	}
	if (path[1] && path[1][0] == '-' && path[1][1])
	{
		ft_putstr_fd("no option", 2);
		return (1);
	}
	if (!path[1] || !ft_strcmp(path[1], "~"))
		ret = chdir(getenv("HOME"));
	else if (!ft_strcmp(path[1], "-"))
		ret = chdir(getenv("OLDPWD"));
	else
	{
		printf("path[1] = %s\n", path[1]);
		ret = chdir(path[1]);
	}
	if (ret < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (update_env(env, oldpwd));
}
