/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:24 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/22 09:51:23 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
	{
		ft_putstr_fd("Error: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("' not a valid identifier\n", 2);
		return (0);
	}
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

void	remove_arg(char *arg, char ***env)
{
	int		j;
	int		i;

	i = -1;
	while ((*env)[++i])
	{
		j = 0;
		while ((*env)[i][j] && (*env)[i][j] != '=')
			j++;
		if (!ft_strncmp(arg, (*env)[i], j) && j == ft_strlen(arg))
		{
			free((*env)[i]);
			while ((*env)[i])
				(1) && ((*env)[i] = (*env)[i + 1], i++);
			(*env)[i] = NULL;
			break ;
		}
	}
}

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	exit_status;

	(1) && (i = -1, exit_status = 0);
	if (!args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1])
		return (ft_putstr_fd("minishell: no option\n", 2), 2);
	while (args[++i])
	{
		if (valid_arg(args[i]))
			remove_arg(args[i], env);
		else
			exit_status = 1;
	}
	return (exit_status);
}
