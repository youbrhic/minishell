/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:19:20 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/28 04:49:03 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_multi_n(char *arg)
{
	int	i;

	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0' && arg[0] == '-')
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int		no_nl;
	int		i;
	int		j;

	no_nl = 0;
	i = 1;
	while (args[i] && (!ft_strcmp(args[i], "-n") || check_multi_n(args[i])))
	{
		no_nl = 1;
		i++;
	}
	while (args[i])
	{
		j = 0;
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_nl)
		printf("\n");
	return (0);
}
