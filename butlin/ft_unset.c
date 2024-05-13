/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:24 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/13 22:59:42 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_args(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1])
	{
		ft_putstr_fd("Error: no option\n", 2);
		return (2);
	}
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			ft_putstr_fd("Error: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("' not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (-1);
}


int	ft_unset(char **args, char ***env)
{
	int	i;
	int	j;
	int	len;
	int	ret;

	(1) && (i = 0, ret = valid_args(args));
	if (ret == 2 || ret == 1 || ret == 0)
		return (ret);
	while (args[++i])
	{
		j = -1;
		len = ft_strlen(args[i]);
		while ((*env)[++j])
		{
			if (!ft_strncmp(args[i], (*env)[j], len))
			{
				free((*env)[j]);
				while ((*env)[j])
					(1) && ((*env)[j] = (*env)[j + 1], j++);
				(*env)[j] = NULL;
				break ;
			}
		}
	}
	return (0);
}
