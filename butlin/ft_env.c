/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:22:18 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/30 18:16:41 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args, char ***env)
{
	int	i;

	i = -1;
	if (args[1] && args[1][0] == '-' && args[1][1])
	{
		printf("Error: no option\n");
		return (127);
	}
	if (args[1])
	{
		printf("Error: no argument\n");
		return (1);
	}
	while ((*env)[++i])
	{
		if (ft_strchr((*env)[i], '='))
			printf("%s\n", (*env)[i]);
	}
	return (0);
}
