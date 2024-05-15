/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:22:18 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/08 19:02:27 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args, char ***env)
{
	int	i;

	i = -1;
	if (args[1] && args[1][0] == '-' && args[1][1])
	{
		write(2, "Error: no option\n", 17);
		return (127);
	}
	if (args[1])
	{
		write(2, "Error: no arguments\n", 20);
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
