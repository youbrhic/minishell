/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:24:14 by aait-bab          #+#    #+#             */
/*   Updated: 2024/05/20 15:52:44 by youbrhic         ###   ########.fr       */
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

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_exit(char **args)
{
	int		exit_state;

	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit (0);
	if (get_size_mat(args) > 2 && ft_isnumber(args[1]))
		return (ft_putstr_fd("minisehll : exit: numeric argument required\n", 2), 2);
	else if (ft_isnumber(args[1]))
	{
		exit_state = (unsigned char)ft_atoi(args[1]);
		exit (exit_state);
	}
	else
	{
		
		ft_putstr_fd("minisehll : exit: numeric argument required\n", 2);
		exit (255);
	}
}

