/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:21:27 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/28 04:04:45 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **path, char ***env)
{
	int		ret;

	if (path[1] && path[1][0] == '-' && path[1][1])
	{
		printf("Error: no option\n");
		return (1);
	}
	if (!path[1] || !ft_strcmp(path[1], "~"))
		ret = chdir(getenv("HOME"));
	else if (!ft_strcmp(path[1], "-"))
		ret = chdir(getenv("OLDPWD"));
	else
		ret = chdir(path[1]);
	if (ret < 0)
	{
		printf("cd: %s: No such file or directory\n", path[1]);
		return (1);
	}
	// ft_setenv("OLDPWD", ft_getenv("PWD", *env), env);
	// ft_setenv("PWD", getcwd(NULL, 0), env);
	return (0);
}
