/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:24 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/16 11:23:54 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!is_alphanum(arg[i]) && arg[i] != '_')
		{
			ft_putstr_fd("Error: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("' not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	j;
	int exit_status;

	(1) && (i = -1, exit_status = 0);
	if (!args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1])
	{
		ft_putstr_fd("Error: no option\n", 2);
		return (2);
	}
	while (args[++i])
	{
		if (valid_arg(args[i]))
		{
			j = -1;
			while ((*env)[++j])
			{
				if (!ft_strncmp(args[i], (*env)[j], ft_strlen(args[i])))
				{
					free((*env)[j]);
					while ((*env)[j])
						(1) && ((*env)[j] = (*env)[j + 1], j++);
					(*env)[j] = NULL;
					break ;
				}
			}
		}
		else
			exit_status = 1;
	}
	return (exit_status);
}
