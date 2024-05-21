/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:03 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/21 00:42:22 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **args, char ***env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd(ft_gete("PWD", *env, 0), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (args[1] && (args[1][0] == '-' && args[1][1]))
	{
		ft_putstr_fd("Error: no option\n", 2);
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (0);
}
