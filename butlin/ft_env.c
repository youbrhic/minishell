/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:22:18 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/22 08:44:07 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args, char ***env)
{
	int	i;

	i = -1;
	if (!ft_getenv("PATH", *env))
		return (ft_putstr_fd("minishell:", 2),
			ft_putstr_fd("env: No such file or directory\n", 2), 127);
	if (args[1] && args[1][0] == '-' && args[1][1])
	{
		ft_putstr_fd("minishell: no option\n", 2);
		return (127);
	}
	if (args[1])
	{
		ft_putstr_fd("minishell: no arguemnts\n", 2);
		return (1);
	}
	while ((*env)[++i])
	{
		if (ft_strchr((*env)[i], '='))
		{
			ft_putstr_fd((*env)[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
