/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:24:14 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/21 09:01:39 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isnumber(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

static void	free_data(char **args, char **env, int exit_status)
{
	free_mat(args);
	free_mat(env);
	exit(exit_status);
}

// 9223372036854775807

int	ft_exit(char **args, char **env, int flag)
{
	int		exit_state;

	if (flag)
		ft_putstr_fd("exit\n", 2);
	if (!args[1])
		exit (0);
	if (get_size_mat(args) > 2 && ft_isnumber(args[1]))
		return (ft_putstr_fd("minisehll : exit: too many arguments\n", 2), 1);
	else if (ft_isnumber(args[1]))
	{
		exit_state = (unsigned char)ft_atoi(args[1]);
		free_data(args, env, exit_state);
	}
	else
	{
		ft_putstr_fd("minishell: exit: numeric argument required", 2);
		free_data(args, env, 255);
	}
	return (0);
}
