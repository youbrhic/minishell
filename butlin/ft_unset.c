/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:23:24 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/30 18:18:07 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1])
	{
		printf("Error: no option\n");
		return (2);
	}
	while (args[++i])
	{
		j = -1;
		len = ft_strlen(args[i]);
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			printf("Error: '%s' not a valid identifier\n", args[i]);
			return (1);
		}
		while ((*env)[++j])
		{
			if (!ft_strncmp(args[i], (*env)[j], len))
			{
				while ((*env)[j])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				(*env)[j] = NULL;
				break ;
			}
		}
	}
	return (0);
}
